#include "chat-client.h"
#include "../net/chat-sockets.h"
#include "../utils.h"
#include <thread>
#include <ncurses.h>

using namespace tt::chat::client;

Client::Client(int port, const std::string &client_username)
    : socket_(tt::chat::net::create_socket()), username(client_username) {
  initscr();
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
	set_sockaddr(&server_address_, port);
  connect_to_server(sockfd_, server_address_);
  write(sockfd_, client_username.c_str(), client_username.size());
}

std::string Client::send_and_receive_messages() {
  using namespace tt::chat;
  
  std::thread reader([this]() {
    while(true) {
      int n = read(sockfd_, buffer_, sizeof(buffer_));
      std::fflush(stdout);
      printw("%s\n", buffer_);
      refresh();
      bzero(buffer_, sizeof(buffer_));
    }
  });

  while(true) {
    std::fflush(stdout);
    getnstr(buffer_, sizeof(buffer_));
    int c = strlen(buffer_);
    buffer_[c] = '\0';
    write(sockfd_, buffer_, c + 1);
    bzero(buffer_, sizeof(buffer_));
  }

  reader.join();
  // writer.detach();
 
}

Client::~Client() { endwin(); close(socket_); }

void Client::connect_to_server(
    int sock, sockaddr_in &server_address) {
  using namespace tt::chat;
  auto err_code =
      connect(sock, (sockaddr *)&server_address, sizeof(server_address));
  check_error(err_code < 0, "Connection Failed.\n");
}
