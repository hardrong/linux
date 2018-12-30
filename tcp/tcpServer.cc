#include "tcpServer.hpp"
void Usage(char *proc)
{
  std::cout << "Usage :" << proc << " ip  port" << std::endl;
}
int main(int argc,char *argv[])
{
   if(argc != 3)
   {
     Usage(argv[0]);
     exit(1);
   }
   std::string ip = argv[1];
   int port = atoi(argv[2]);

   Server * sp = new Server(ip,port);
   sp->InitServer();
   sp->Run();
   delete sp;
  return 0;

}
