#include "Connection.cpp"
#include <experimental/random>
#include <iostream>

union U {
  int16_t s;
  char c[2];
};

int16_t convert(char *c);
int16_t convert(unsigned char *c);

int main() {
  int portnum = 8090;
  char *ip = "127.0.0.1";
  Connection c(portnum, ip);
  std::cout << "Starting socket connection" << std::endl;
  if (c.con()) {
    std::cout << "Connected." << std::endl;
    int i = 1;
    U u;
    u.s = i;
    while (true) {
      sleep(1);
      i++;
      int random_number = std::experimental::randint(-2225, 2225);
      u.s += random_number;
      std::cout << "Sending: " << (int16_t)u.c[0] << " " << (int16_t)u.c[1]
                << " ," << u.s;
      c.sen(u.c, 2);
      unsigned char ch[2];
      c.receive(ch, 2);
      int16_t it = convert(ch);
      std::cout << ", rec: " << (int16_t)ch[0] << " " << (int16_t)ch[1] << " ,"
                << it << std::endl;

      if (it != u.s || i > 35) {
        break;
      }
    }
  } else {
    std::cout << "Could not connect to socket." << std::endl;
  }

  return 0;
}

int16_t convert(unsigned char *c) {
  return ((int16_t)c[0]) << 8 | ((int16_t)c[1]);
}
