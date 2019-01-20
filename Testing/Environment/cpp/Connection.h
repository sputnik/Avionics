#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

#ifndef Connection_H
#define Connection_H

class Connection {
public:
  Connection(int portnum, char *ip);
  ~Connection(void);
  bool con(void);
  void sen(char *c, int length);
  void receive(char *c, int length);
  void sen(unsigned char *c, int length);
  void receive(unsigned char *c, int length);
  inline bool connected(void) { return m_connected; };

private:
  int m_client;
  struct sockaddr_in m_serv_addr;
  bool m_connected;
};

#endif
