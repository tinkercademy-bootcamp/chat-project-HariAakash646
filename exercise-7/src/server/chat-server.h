#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <netinet/in.h>
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <string>

#define MAX_CONN        16
#define MAX_EVENTS      32
#define BUF_SIZE        128
#define MAX_LINE        256

namespace tt::chat::server {

class Server {
  /**
   * @brief Creates the server interface, accepts connections from different clients and 
   * allows communication through multiple channels.
   * 
   * Accepts specific commands like /goto or /create and moves clients between channels
   * or creates new channels.
   * 
   */
public:
  Server(int port);
  ~Server();
  void handle_clients();

private:
  int socket_;
  sockaddr_in server_address_;
  sockaddr_in client_address_;
  int epfd_;
  int connection_socket_;
  socklen_t socklen_;   // TODO: Define
  char buffer_[BUF_SIZE];
  epoll_event events_[MAX_EVENTS];
  std::vector<std::string> channels;
  std::vector<std::vector<int>> channels_sockets;
  std::map<int, std::string> socket_username_map;
  std::map<int, int> socket_channel_map;

  static constexpr int kBufferSize = 1024;

  void connect_to_client();
  void handle_accept(epoll_event &event);
  void close_connection(epoll_event &event);
  static int setnonblocking(int sock);
  static void epoll_ctl_add(int epfd, int fd, uint32_t events);
  void route_function(int socket, const std::string &command);
  void switch_channel(int socket, int channel);
  void create_channel(int socket, const std::string &channel_name);
};
} // namespace tt::chat::server

#endif // CHAT_SERVER_H
