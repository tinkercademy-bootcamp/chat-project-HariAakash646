#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <string>

void check_error(bool test, std::string error_message);

int create_socket();

#endif