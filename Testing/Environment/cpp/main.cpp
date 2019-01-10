#include "Connection.cpp"
#include <iostream>

union U {
  int8_t s;
  unsigned char c;
};

#define BNO055_ADDRESS_A 0x28
#define BNO055_ADDRESS_B 0x29
#define MPL115A2_ADDRESS 0x60
int16_t convert(char *c);
int16_t convert(unsigned char *c);

int main() {
  int portnum = 8090;
  char *ip = "127.0.0.1";
  Connection c(portnum, ip);
  std::cout << "Starting socket connection" << std::endl;
  sleep(2);
  if (c.con()) {
    std::cout << "Connected." << std::endl;
    int i = 1;
    U u;
    u.s = i;
    while (true) {
      sleep(1);
      i++;
      uint8_t addr;
      if (i % 3 == 0) {
        addr = BNO055_ADDRESS_A;
      } else if (i % 3 == 1) {
        addr = BNO055_ADDRESS_B;
      } else if (i % 3 == 2) {
        addr = MPL115A2_ADDRESS;
      }
      unsigned char cc = addr;
      std::cout << "Sending: " << cc << " ," << addr << std::endl;
      c.sen(&cc, 1);

      if (i > 10) {
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
