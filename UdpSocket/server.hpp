#pragma once 
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

class UdpSocket
{
 private:
   std::string _ip;
   int _port;
   int _fd;
 public:
   UdpSocket(std::string &ip,int &port)
      :_ip(ip)
      ,_port(port)
      ,_fd(-1)
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
   bool Bind()
   {
     struct sockaddr_in addr;
     addr.sin_family = AF_INET;
     addr.sin_port  = htons(_port);
     addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    
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
       close(_fd);
   }
   void Recv(std::string &str,\
       struct sockaddr_in &peer,socklen_t &len)
   {
     char buf[1024] = {0};
     len = sizeof(sockaddr_in);
     ssize_t s = recvfrom(_fd,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
      if(s > 0)
      {
        buf[s] = 0;
        str = buf;
      }

   }
   void Send(std::string &str_,\
       struct sockaddr_in &peer ,socklen_t &len)
   {
     sendto(_fd,str_.c_str(),str_.size(),0,(struct sockaddr*)&peer,len);
   }
}; 
class UdpServer 
{
  private:
    UdpSocket sock;
  public:
    UdpServer(std::string ip,int port )
      :sock(ip,port)
    {
    }
    void Initserver()
    {
      sock.Socket();
      sock.Bind();
    }
    void Start()
    {
      struct sockaddr_in peer;
      socklen_t len;
      std::string message;
      for(;;)
      {
        sock.Recv(message,peer,len);
        std::cout << "["<< inet_ntoa(peer.sin_addr) << ":"<< ntohs(peer.sin_port) << "]#" << message << std::endl;
        message += "server";
       sock.Send(message,peer,len);
       std::cout << "server echo sucess !" <<std:: endl;
      }
    }
    ~UdpServer()
    {

    }
      
};

