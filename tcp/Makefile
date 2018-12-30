.PHONY:all
all:client server 
client:tcpClient.cc
	g++ -o $@ $^
server:tcpServer.cc 
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f client server
