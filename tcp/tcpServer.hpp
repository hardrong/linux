#pragma once 

#include <iostream>
#include <string>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
class Sock
{
  private:
    std::string _ip;
    int _listensock;
    int _port;
  public:
    Sock(const std::string ip,int port)
      :_ip(ip)
       ,_listensock(-1)
       ,_port(port)
  {

  }
    void Socket()
    {
             _listensock = socket(AF_INET,SOCK_STREAM,0);
             if(_listensock < 0)
             {
               std::cerr << "socket error " << std::endl;
               exit(2);
             }
    }
    void Bind()
    {
      struct sockaddr_in local;
      bzero(&local,sizeof(local));
      local.sin_family = AF_INET;
      local.sin_port = htons(_port);
      local.sin_addr.s_addr = inet_addr(_ip.c_str());

      if(bind(_listensock,(struct sockaddr *)&local,sizeof(local)) < 0)
      {
        std::cerr << "bind error" << std::endl;
        exit(3);
      }
    }
    void Listen()
    {
      if(listen(_listensock , 5) < 0)
      {
        std::cerr << "listen error" << std::endl;
        exit(3);
      }
    }
    int  Accept()
    {
      struct sockaddr peer;
      socklen_t len = sizeof(peer);
      int sock = accept(_listensock,(struct sockaddr*)&peer,&len);
            if(sock < 0)
            {
              std::cerr << "accept error" << std::endl;
              return -1;
            }
            return sock;
    }
    ~Sock()
    {
      close(_listensock);
    }

};
class Server
{
 private:
   Sock sock;
 public:
   Server(const std::string &ip,const int& port)
     :sock(ip,port)
   {

   }
   void InitServer()
   {
     sock.Socket();
     sock.Bind();
     sock.Listen();
   }
   void Service(int sock)
   {
     char buf[1024] = {0};
      for(;;)
      {
       ssize_t s =  read(sock,buf,sizeof(buf)-1);
       //返回0时表示对方关闭链接
       if(s > 0)
       {
         buf[s] = 0;
         std::cout <<  buf << std::endl;
         write(sock,buf,strlen(buf));
       }
       else if(s == 0)
       {
         std::cout << "client is quit ..." << std::endl;
         break;
       }
       else 
       {
         std::cerr << "read error! " << std::endl;
         break;
       }
  
    
   }
      close(sock);
   }
   void Run()
   {
      for(; ;)
      {
        int newsock = sock.Accept();
        if(newsock < 0)
        {
          continue;
        }
        std::cout << "A client connect..." << std::endl;
        Service(newsock);
      }
   }
   ~Server()
   {
    
   }

};
