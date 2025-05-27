make all: build build/client build/server

build:
	mkdir build

CXX = g++
CXX_FLAGS = -fsanitize=address
LD_FLAGS = -fsanitize=address

build/client: tcp_echo_client.cc
	$(CXX) $(CXX_FLAGS) -o build/client.out tcp_echo_client.cc

build/server: tcp_echo_server.cc
	$(CXX) $(CXX_FLAGS) -o build/server.out tcp_echo_server.cc

clean:
	rm -rf build
