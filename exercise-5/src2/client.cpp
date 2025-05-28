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

