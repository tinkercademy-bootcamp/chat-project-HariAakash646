#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>

namespace tt::chat::client {
class Client {
public:
  Client(int port);
  std::string send_and_receive_message(const std::string &message);
  ~Client();

private:
  int socket_;
  int sockfd_;
  sockaddr_in server_address_;
  void connect_to_server(int sock, sockaddr_in &server_address);

  static constexpr int kBufferSize = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
