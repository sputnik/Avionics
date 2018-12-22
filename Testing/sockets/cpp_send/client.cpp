#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int length(char *c, int maxLen);

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

  cout << "--> Connection confirmed..\n";

  string temp;
  uint32_t ii = 1;
  uint32_t start = 1;
  uint32_t prev = ii;
  while (true) {
    cout << "Send: ";

    ii *= 3;
    if (ii < prev) {
      start++;
      ii = start;
      prev = ii;
    } else {
      prev = ii;
    }
    if (ii == 0) {
      start++;
      ii = start;
    }
    uint32_t len = 4; // length(buffer,bufsize);
    char c[4];
    char *cp = c;
    char *c2 = (char *)&(ii);
    cp = (char *)&(len);
    send(client, cp, 4, 0);
    char s[(int)len];
    cout << ii;
    cout << ", length = ";
    cout << len;
    for (int i = 0; i < len; i++) {
      s[i] = buffer[i];
    }
    send(client, c2, len, 0);
    cout << endl;
    sleep(1);
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
