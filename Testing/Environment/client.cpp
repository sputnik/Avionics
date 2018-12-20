#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int length(char *c, int maxLen);
uint32_t convert(unsigned char *c);
int16_t convert2(unsigned char *c);

union U {
  int16_t s;

  struct Byte {
    char c[2];
  } byte;
};

int main(int argc, char *argv[]) {
  int client;
  int portnum = 8090;
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
  U u;
  u.s = 5;

  send(client, u.byte.c, 2, 0);
  while (true) {
    cout << "Enter a 16 bit int: ";
    cin >> u.s;
    if (u.s == 0) {
      cout << "closing connection";
      break;
    }
    int16_t c1 = (int16_t)u.byte.c[0];
    int16_t c2 = (int16_t)u.byte.c[1];
    printf("sending %i %x %x\n", u.s, c1, c2);
    send(client, u.byte.c, 2, 0);
  }

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
