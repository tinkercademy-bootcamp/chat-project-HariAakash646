#include <unistd.h>
#include <sys/epoll.h>

// #include "spdlog/spdlog.h"

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "chat-server.h"


#define MAX_CONN        16
#define MAX_EVENTS      32
#define BUF_SIZE        16
#define MAX_LINE        256

tt::chat::server::Server::Server(int port)
    : socket_(tt::chat::net::create_socket()),
      server_address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;

  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  set_sockaddr(&server_address_, port);

  bind(socket_, (struct sockaddr *)&server_address_, sizeof(server_address_));

  setnonblocking(socket_);
	listen(socket_, MAX_CONN);

  std::cout << "Server listening on port " << port << "\n";

  epfd_ = epoll_create(1);
	epoll_ctl_add(epfd_, socket_, EPOLLIN | EPOLLOUT | EPOLLET);
}

tt::chat::server::Server::~Server() { 
  close(socket_); 
}

void tt::chat::server::Server::handle_clients() {
  socklen_t address_size = sizeof(server_address_);

  while (true) {
    int nfds = epoll_wait(epfd_, events_, MAX_EVENTS, -1);
    for (int i = 0; i < nfds; i++) {
			if (events_[i].data.fd == socket_) {
				/* handle new connection */
				connect_to_client();
			} else if (events_[i].events & EPOLLIN) {
				/* handle EPOLLIN event */
				handle_accept(events_[i]);
			} else {
				printf("[+] unexpected\n");
			}
			/* check if the connection is closing */
			if (events_[i].events & (EPOLLRDHUP | EPOLLHUP)) {
				close_connection(events_[i]);
				continue;
			}
		}
  }
}

void tt::chat::server::Server::close_connection(epoll_event &event) {
  printf("[+] connection closed\n");
  epoll_ctl(epfd_, EPOLL_CTL_DEL,
      event.data.fd, NULL);
  close(event.data.fd);
}

int tt::chat::server::Server::setnonblocking(int sock)
{
	if (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK) ==
	    -1) {
		return -1;
	}
	return 0;
}

void tt::chat::server::Server::epoll_ctl_add(int epfd, int fd, uint32_t events)
{
	struct epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		perror("epoll_ctl()\n");
		exit(1);
	}
}

void tt::chat::server::Server::connect_to_client() {
  connection_socket_ =
      accept(socket_,
        (struct sockaddr *)&client_address_,
        &socklen_);
  connected_sockets.push_back(connection_socket_);

  inet_ntop(AF_INET, (char *)&(client_address_.sin_addr),
      buffer_, sizeof(client_address_));

  // printf("[+] connected with %s:%d\n", buffer_,
  //         ntohs(client_address_.sin_port));

  setnonblocking(connection_socket_);
  epoll_ctl_add(epfd_, connection_socket_,
          EPOLLIN | EPOLLET | EPOLLRDHUP |
          EPOLLHUP);

  bzero(buffer_, sizeof(buffer_));
  int n = read(connection_socket_, buffer_,
      sizeof(buffer_));
  socket_username_map[connection_socket_] = buffer_;
  printf("[+] connected with %s\n", buffer_);
}

void tt::chat::server::Server::handle_accept(epoll_event &event) {
  using namespace tt::chat;

  while(true) {
    bzero(buffer_, sizeof(buffer_));
    int n = read(event.data.fd, buffer_,
        sizeof(buffer_));
    if (n <= 0 /* || errno == EAGAIN */ ) {
      break;
    } else {
      printf("[+] %s: %s\n", socket_username_map[event.data.fd].c_str(), buffer_);
      for(auto curr_sock : connected_sockets) {
        std::string output = socket_username_map[event.data.fd] + ": ";
        output += buffer_;
        write(curr_sock, output.c_str(), output.size());
      }
    }
  }
}