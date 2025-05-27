make all: build build/client build/server

build:
	mkdir build

CXX = g++

build/client: tcp_echo_client.cc
	$(CXX) -fsanitize=address -o build/client.out tcp_echo_client.cc

build/server: tcp_echo_server.cc
	$(CXX) -fsanitize=address -o build/server.out tcp_echo_server.cc

clean:
	rm -rf build
