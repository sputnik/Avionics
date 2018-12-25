#include "Connection.h"
#include <experimental/random>
#include <iostream>

union U {
  int16_t s;
  char c[2];
};

int main() {
  int portnum = 8090;
  char *ip = "127.0.0.1";
  Connection c(portnum, ip);
  if (c.con()) {
    std::cout << "Connected." << std::endl;
    int i = 1;
    U u;
    u.s = i;
    c.sen(u.c, 2);
    while (true) {
      sleep(1);
      i++;
      int random_number = std::experimental::randint(30, 1225);
      u.s += random_number;
      std::cout << "Sending: " << u.s << std::endl;
      c.sen(u.c, 2);
      if (i > 15) {
        break;
      }
    }
  } else {
    std::cout << "Could not connect to socket." << std::endl;
  }

  return 0;
}
