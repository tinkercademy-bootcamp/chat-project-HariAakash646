#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"

tt::chat::client::Client::Client(int port)
    : socket_(tt::chat::net::create_socket()) {
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
	set_sockaddr(&server_address_, port);
  connect_to_server(socket_, server_address_);
}

std::string tt::chat::client::Client::send_and_receive_message(
    const std::string &message) {
  using namespace tt::chat;
  char recv_buffer[kBufferSize] = {0};

  // Send the message to the server
  send(socket_, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  ssize_t read_size = read(socket_, recv_buffer, kBufferSize);
  if (read_size > 0) {
    return std::string(recv_buffer);
  } else if (read_size == 0) {
    return "Server closed connection.\n";
  } else {
    return "Read error.\n";
  }
}

tt::chat::client::Client::~Client() { close(socket_); }

void tt::chat::client::Client::connect_to_server(
    int sock, sockaddr_in &server_address) {
  using namespace tt::chat;
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}
