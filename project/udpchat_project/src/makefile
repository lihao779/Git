SVR_BIN = ChatServer
CLI_BIN = ChatClient

all:ChatServer ChatClient

$(SVR_BIN):ChatServer.cpp
		g++ $^ -o $@ -pthread
	
$(CLI_BIN):ChatClient.cpp
	g++ $^ -o $@ -pthread

.PHONY:clean
clean:
	 rm $(SVR_BIN) $(CLI_BIN)

