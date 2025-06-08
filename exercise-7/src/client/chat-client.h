#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <netinet/in.h>
#include <string>

#define MAX_LINE        256

namespace tt::chat::client {
class Client {
  /**
   * @brief Runs the Client, connects it to the server, sends and receives messages.
   * 
   * Inputs the messages and displays them through an ncurses window.
   * Can use specifics commands like /goto and /create to switch between
   * or create channels.
   * 
   */
public:
  std::string username;
  Client(int port, const std::string &client_username);
  std::string send_and_receive_messages();
  ~Client();

private:
  int socket_;
  int sockfd_;
  char buffer_[MAX_LINE];
  sockaddr_in server_address_;
  void connect_to_server(int sock, sockaddr_in &server_address);

  static constexpr int kBufferSize = 1024;
};
} // namespace tt::chat::client

#endif // CHAT_CLIENT_H
