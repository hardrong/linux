.PHONY:all
all:client server 
client:tcpClient.cc
	g++ -o $@ $^
server:tcpServer.cc 
	g++ -o $@ $^ -std=c++11 -lpthread
.PHONY:clean
clean:
	rm -f client server
