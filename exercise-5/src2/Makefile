make all: build build/client build/server

build:
	mkdir build

CXX = g++
CXX_FLAGS = -fsanitize=address -std=c++17
LD_FLAGS = -fsanitize=address -std=c++17

build/client: tcp_echo_client.cpp
	$(CXX) $(CXX_FLAGS) -o build/client.out tcp_echo_client.cpp client.cpp

build/server: tcp_echo_server.cpp
	$(CXX) $(CXX_FLAGS) -o build/server.out tcp_echo_server.cpp server.cpp

clean:
	rm -rf build
