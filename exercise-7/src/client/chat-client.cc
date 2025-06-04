#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"
#include <thread>

tt::chat::client::Client::Client(int port, std::string client_username)
    : socket_(tt::chat::net::create_socket()), username(client_username) {
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
	set_sockaddr(&server_address_, port);
  connect_to_server(sockfd_, server_address_);
  write(sockfd_, client_username.c_str(), client_username.size());
}

std::string tt::chat::client::Client::send_and_receive_messages() {
  using namespace tt::chat;
  
  std::thread reader([this]() {
    while(true) {
      int n = read(sockfd_, buffer_, sizeof(buffer_));
      printf("%s\n", buffer_);
      std::fflush(stdout);
      bzero(buffer_, sizeof(buffer_));
    }
  });

  while(true) {
    std::fflush(stdout);
    fgets(buffer_, sizeof(buffer_), stdin);
    int c = strlen(buffer_) - 1;
    buffer_[c] = '\0';
    write(sockfd_, buffer_, c + 1);
    bzero(buffer_, sizeof(buffer_));
  }

  reader.join();
  // writer.detach();
 
}

tt::chat::client::Client::~Client() { close(socket_); }

void tt::chat::client::Client::connect_to_server(
    int sock, sockaddr_in &server_address) {
  using namespace tt::chat;
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}
