#include "server.h"
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Server::Server(int port) {
  _port = port;
  _sock = socket(AF_INET, SOCK_STREAM, 0);
  check_error(_sock < 0, "Socket creation error\n");

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(_port);
}

void Server::check_error(bool test, std::string error_message) {
  if (test) {
    std::cerr << error_message << "\n";
    exit(EXIT_FAILURE);
  }
}

void Server::set_socket_options(int opt) {
  auto err_code = setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                             &opt, sizeof(opt));
  check_error(err_code < 0, "setsockopt() error\n");
}

void Server::bind_address_to_socket() {
  auto err_code = bind(_sock, (sockaddr *)&address, sizeof(address));
  check_error(err_code < 0, "bind failed\n");
}

void Server::listen_on_socket() {
  auto err_code = listen(_sock, 3);
  check_error(err_code < 0, "listen failed\n");
}

void Server::start_listening_on_socket() {
  const int kSocketOptions = 1;
  set_socket_options(kSocketOptions);

  bind_address_to_socket();
  listen_on_socket();
}

void Server::handle_accept(int sock) {
  const int kBufferSize = 1024;
  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(sock, buffer, kBufferSize);

  check_error(read_size < 0,
              "Read error on client socket " + std::to_string(sock));
  if (read_size > 0) {
    std::cout << "Received:" << buffer << "\n";
    send(sock, buffer, read_size, 0);
    std::cout << "Echo message sent\n";
  } else if (read_size == 0) {
    std::cout << "Client disconnected.\n";
  } else {
    std::cerr << "Read error on client socket " << sock << "\n";
  }
  close(sock);
}

void Server::handle_connections() {
  socklen_t address_size = sizeof(address);

  while (true) {
    int accepted_socket = accept(_sock, (sockaddr *)&address, &address_size);
    check_error(accepted_socket < 0, "Accept error n ");
    handle_accept(accepted_socket);
  }
}

void Server::close_socket() {
  close(_sock);
}