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
  int epfd_;

  static constexpr int kBufferSize = 1024;

  void handle_accept(int sock);
  static int setnonblocking(int sock);
  static void epoll_ctl_add(int epfd, int fd, uint32_t events);
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
