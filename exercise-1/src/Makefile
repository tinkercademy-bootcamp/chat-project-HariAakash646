make all: build build/client build/server

build:
	mkdir build

CXX = g++

build/client: tcp_echo_client.cc
	$(CXX) -o build/client.o tcp_echo_client.cc

build/server: tcp_echo_server.cc
	$(CXX) -o build/server.o tcp_echo_server.cc

clean:
	rm -rf build
