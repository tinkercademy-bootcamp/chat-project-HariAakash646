#include <unistd.h>
#include <sys/epoll.h>

#include "spdlog/spdlog.h"

#include "../net/chat-sockets.h"
#include "../utils.h"
#include "chat-server.h"

tt::chat::server::Server::Server(int port, int max_connections)
    : socket_(tt::chat::net::create_socket()),
      address_(tt::chat::net::create_address(port)) {
  using namespace tt::chat;

  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  set_sockaddr(&address_, port);

  bind(socket_, (struct sockaddr *)&address_, sizeof(address_));

  setnonblocking(socket_);
	listen(socket_, max_connections);

  std::cout << "Server listening on port " << port << "\n";

  epfd_ = epoll_create(1);
	epoll_ctl_add(epfd_, socket_, EPOLLIN | EPOLLOUT | EPOLLET);
}

tt::chat::server::Server::~Server() { close(socket_); }

void tt::chat::server::Server::handle_connections() {
  socklen_t address_size = sizeof(address_);

  while (true) {
    int accepted_socket = accept(socket_, (sockaddr *)&address_, &address_size);
    tt::chat::check_error(accepted_socket < 0, "Accept error n ");
    handle_accept(accepted_socket);
  }
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

void tt::chat::server::Server::handle_accept(int sock) {
  using namespace tt::chat;

  char buffer[kBufferSize] = {0};
  ssize_t read_size = read(sock, buffer, kBufferSize);

  if (read_size > 0) {
    SPDLOG_INFO("Received: {}", buffer);
    send(sock, buffer, read_size, 0);
    SPDLOG_INFO("Echo message sent");
  } else if (read_size == 0) {
    SPDLOG_INFO("Client disconnected.");
  } else {
    SPDLOG_ERROR("Read error on client socket {}", socket_);
  }
  close(sock);
}