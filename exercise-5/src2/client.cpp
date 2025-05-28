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
