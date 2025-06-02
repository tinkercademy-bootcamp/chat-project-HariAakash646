#ifndef UTILS_H
#define UTILS_H

#include <concepts>
#include <stdexcept>
#include <string_view>

#include "spdlog/spdlog.h"

#define MAX_EVENTS      32
#define BUF_SIZE        16
#define MAX_LINE        256

namespace tt::chat {

template <std::same_as<bool> T, std::convertible_to<std::string_view> S>
void check_error(T test, S error_message) {
  if (test) {
    SPDLOG_ERROR("{}", error_message);
    throw std::runtime_error(error_message);
  }
}

} // namespace tt::chat

static void set_sockaddr(struct sockaddr_in *addr, int port)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);
}


#endif // UTILS_H
