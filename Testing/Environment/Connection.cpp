#include "Connection.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

Connection::Connection(int portnum, char *ip)
    : m_client(-1), m_connected(false) {
  m_client = socket(AF_INET, SOCK_STREAM, 0);
  if (m_client < 0) {
    cout << "ERROR establishing socket\n" << endl;
  }
  m_serv_addr.sin_family = AF_INET;
  m_serv_addr.sin_port = htons(portnum);
  inet_pton(AF_INET, ip, &m_serv_addr.sin_addr);
}

bool Connection::con(void) {
  if (connect(m_client, (const struct sockaddr *)&m_serv_addr,
              sizeof(m_serv_addr)) == 0) {
    m_connected = true;
    cout << "--> Connection to the server " << inet_ntoa(m_serv_addr.sin_addr)
         << " with port number: " << ntohs(m_serv_addr.sin_port) << endl;
  }
  return m_connected;
}

void Connection::sen(char *c, int length) { send(m_client, c, length, 0); }
void Connection::receive(char *c, int length) { recv(m_client, c, length, 0); }
