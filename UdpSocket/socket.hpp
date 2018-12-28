#pragma once 
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket
{
 private:
   std::string _ip;
   int _port;
   int _fd;
 public:
   UdpSocket()
     :_fd(-1)
   {
   }
   bool Socket()
   {
     _fd = socket(AF_INET ,SOCK_DGRAM,0);
     if(_fd < 0)
     {
      perror("socket");
      return false;
     }
     return true;
   }
   bool Bind(std::string &ip,int port)
   {
     struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port  = htons(port);
     addr.sin_addr.s_addr = inet_addr(ip.c_str());
    
     int ret = bind(_fd,(struct sockaddr*)&addr,sizeof(addr));
     if(ret < 0)
     {
       perror("bind");
       return  false;
     }
     return true;
   }
   ~UdpSocket()
   {

   }

};
