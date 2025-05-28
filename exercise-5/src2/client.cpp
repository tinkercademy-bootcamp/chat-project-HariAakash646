#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "client.h"

void Client::check_error(bool test, std::string error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}


Client::Client(const std::string &server_ip, int port) {
  _port = port;
  _sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(_sock < 0, "Socket creation error\n");

  address.sin_family = AF_INET;
  address.sin_port = htons(_port);

  auto err_code = inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr);
  check_error(err_code <= 0, "Invalid address/ Address not supported.\n");
}

void Client::connect_to_server() {
  auto err_code =
      connect(_sock, (sockaddr *)&address, sizeof(address));
  check_error(err_code < 0, "Connection Failed.\n");
}

void Client::send_and_receive_message(const std::string &message) {
  const int kBufferSize = 1024;
  char recv_buffer[kBufferSize] = {0};

  // Send the message to the server
  send(_sock, message.c_str(), message.size(), 0);
  std::cout << "Sent: " << message << "\n";

  // Receive response from the server
  ssize_t read_size = read(_sock, recv_buffer, kBufferSize);
  check_error(read_size < 0, "Read error.\n");
  if (read_size > 0) {
    std::cout << "Received: " << recv_buffer << "\n";
  } else if (read_size == 0) {
    std::cout << "Server closed connection.\n";
  }
}

void Client::close_socket() {
  close(_sock);
}