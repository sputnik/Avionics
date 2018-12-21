
#include "Connection.h"
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
    std::cout << "Connected. Enter 0 to close connection." << std::endl;
    U u;
    u.s = 5;
    c.sen(u.c, 2);
    while (true) {
      std::cout << "Enter a 16 bit int: ";
      std::cin >> u.s;
      if (u.s == 0) {
        std::cout << "closing connection";
        break;
      }
      int16_t c1 = (int16_t)u.c[0];
      int16_t c2 = (int16_t)u.c[1];
      printf("sending %i %x %x\n", u.s, c1, c2);
      c.sen(u.c, 2);
    }
  } else {
    std::cout << "Could not connect to socket." << std::endl;
  }

  return 0;
}
