#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Usage(char *proc)
{
  std::cout << "Usage:" << proc << "ip port" << std::endl;
}
int main (int argc , char *argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  //SOCK_DGRAM 用户数据报
  int sock = socket(AF_INET,SOCK_DGRAM,0);
  if(sock < 0)
  {
    std::cerr << "socket error" << std::endl;
    exit(2);
  }
  std::string message;
  struct sockaddr_in server;
  bzero(&server,sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons(atoi(argv[2]));
  for(;;)
  {
    char buf[1024] = {0};
    socklen_t len = sizeof(server);
    std::cout << "please Enter:";
    std::cin >> message;
   sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&server,len);
   ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
   buf[s] = 0;
   std::cout << "server echo#" << buf << std::endl;
  }
  return 0;
}
