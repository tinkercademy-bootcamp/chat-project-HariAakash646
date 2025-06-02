#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <netinet/in.h>
namespace tt::chat::server {

class Server {
public:
  Server(int port, int max_connections);
  ~Server();
  void handle_connections();

private:
  int socket_;
  sockaddr_in address_;

  static constexpr int kBufferSize = 1024;

  void handle_accept(int sock);
  static int setnonblocking(int sock);
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
