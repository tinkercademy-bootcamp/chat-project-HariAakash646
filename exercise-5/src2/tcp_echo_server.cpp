#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

int main() {
  const int kPort = 8080;
  Server server(kPort);

  server.start_listening_on_socket();
  std::cout << "Server listening on port " << kPort << "\n";
  server.handle_connections();
  server.close_socket();

  return 0;
}