#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

template <typename T, typename S> void check_error(T test, S error_message);

int create_socket();

#endif