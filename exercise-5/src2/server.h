#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <netinet/in.h>

class Server {
  public:
    Server(int port);

    void start_listening_on_socket();

    void handle_connections();
    
    void close_socket();

  private:
    sockaddr_in address;
    int _sock;
    int _port;

    void check_error(bool test, std::string error_message);

    void set_socket_options(int opt);

    void bind_address_to_socket();

    void listen_on_socket();

    void handle_accept();
};

#endif