all: tcp_svr tcp_cli
tcp_cli:cli.cpp
	g++ $^ -o $@ -g -pthread
tcp_svr:svr.cpp
	g++ $^ -o $@ -g
