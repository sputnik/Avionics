#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int length(char *c, int maxLen);
uint32_t convert(unsigned char *c);
int16_t convert2(unsigned char *c);

int main(int argc, char *argv[]) {
  int client;
  int portnum = 8091;
  int bufsize = 1024;
  char buffer[bufsize];
  char *ip = "127.0.0.1";

  struct sockaddr_in serv_addr;

  client = socket(AF_INET, SOCK_STREAM, 0);
  if (client < 0) {
    cout << "ERROR establishing socket\n" << endl;
    exit(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portnum);
  inet_pton(AF_INET, ip, &serv_addr.sin_addr);

  cout << "\n--> Socket client created...\n";

  if (connect(client, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) ==
      0) {
    cout << "--> Connection to the server " << inet_ntoa(serv_addr.sin_addr)
         << " with port number: " << portnum << endl;
  }
  unsigned char *c = (unsigned char *)malloc(sizeof(char) * 2);

  while (true) {

    if (recv(client, c, 2, 0) == 0) {
      break;
    }
    uint32_t lengt = convert2(c);
    printf("len = %i", lengt);
    unsigned char *c2 = (unsigned char *)malloc(sizeof(char) * lengt);
    if (recv(client, c2, lengt, 0) == 0) {
      break;
    }
    int16_t x1 = (int16_t)c2[0];
    int16_t x2 = (int16_t)c2[1];
    int16_t x = convert2(c2);
    c2 += 2;
    int16_t y1 = (int16_t)c2[0];
    int16_t y2 = (int16_t)c2[1];
    int16_t y = convert2(c2);
    c2 += 2;
    int16_t z1 = (int16_t)c2[0];
    int16_t z2 = (int16_t)c2[1];
    int16_t z = convert2(c2);
    printf(", %3x %3x %6i, %3x %3x %6i, %3x %3x %6i\n", x1, x2, x, y1, y2, y,
           z1, z2, z);
  }
  delete c;

  close(client);
  cout << "\nDisconnected..." << endl;
  return 0;
}

int length(char *c, int maxLen) {
  int ret;
  for (ret = 0; ret < maxLen; ret++) {
    if (c[ret] == '\0') {
      break;
    }
  }
  return ret;
}

uint32_t convert(unsigned char *c) {
  uint32_t arr[4];
  arr[0] = (uint32_t)c[0];
  arr[1] = (uint32_t)c[1];
  arr[2] = (uint32_t)c[2];
  arr[3] = (uint32_t)c[3];
  for (int i = 0; i < 4; i++) {
    if (arr[i] == 0xffffff80) {
      arr[i] = 0x80;
    }
  }
  int32_t num = (uint32_t)c[0] << 24 | (uint32_t)c[1] << 16 |
                (uint32_t)c[2] << 8 | (uint32_t)c[3];
  num = arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3];

  return num;
}

int16_t convert2(unsigned char *c) {
  return (int16_t)c[0] << 8 | (int16_t)c[1];
}
