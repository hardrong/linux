.PHONY:all
all:client server 

client:client.hpp socket.hpp 
	g++ -o $@ $^ -std=c++11
server:server.hpp socket.hpp  
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm - f client server
