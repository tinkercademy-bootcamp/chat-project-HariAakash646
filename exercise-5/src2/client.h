#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <netinet/in.h>

class Client {
  public:
    Client(const std::string &server_ip, int port);

    void connect_to_server();

    void send_and_receive_message(const std::string &message);
    
    void close_socket();

  private:
    sockaddr_in address;
    int _sock;
    int _port;

    void check_error(bool test, std::string error_message);

};

#endif