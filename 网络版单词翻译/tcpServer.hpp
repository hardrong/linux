#pragma once 

#include <unordered_map>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
class Sock
{
  private:
//    std::string _ip;
    int _listensock;
    int _port;
  public:
    Sock(int port)
      :_listensock(-1)
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
//      local.sin_addr.s_addr = inet_addr(_ip.c_str());
      local.sin_addr.s_addr = htonl(INADDR_ANY);

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
struct data_t 
{
   int sock;
   void* sp;
};
class Server
{
 private:
   Sock sock;
   std::unordered_map<std::string,std::string> dict;
 public:
   Server(const int& port)
     :sock(port)
   {
        dict.insert(std::make_pair("郭兴荣","gxr"));
        dict.insert(std::make_pair("付彬","fubin"));
        dict.insert(std::make_pair("爱你","love you"));
        dict.insert(std::make_pair("西安科技大学","xust"));
        dict.insert(std::make_pair("我","I"));
   }
   void InitServer()
   {
     signal(SIGCHLD,SIG_IGN);
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
         std::string key = buf;
         std::string val = dict[key];
         if(val.empty())
         {
           val = "没有这个词的翻译哦";
         }
         write(sock,val.c_str(),val.size());
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
   static void *ThreadRun(void *arg)
   {
     //线程分离后，父进程就不用回收了
     pthread_detach(pthread_self());
     data_t* d = (data_t*)arg;
     Server *sp =(Server*) d->sp;
     int sock = d->sock;
     sp->Service(sock);
     delete d;
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
         data_t *d = new data_t;
           d->sp = this;
          d->sock = newsock;
            pthread_t tid;
            pthread_create(&tid,NULL,ThreadRun,(void*)d);

      //  pid_t id = fork();
      //  if(id == 0)
      //  {
      //  Service(newsock);
      //    exit(0);
          //子进程退出，会自己关文件描述符
       // }
       // close(newsock);
      }
   }
   ~Server()
   {
    
   }

};
