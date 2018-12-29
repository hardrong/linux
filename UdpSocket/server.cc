#include "server.hpp"

void Usage(std::string proc)
{
  std::cout << "Usage" << proc << "ip port" << std::endl;
}
int main(int argc,char *argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  UdpServer *sp = new UdpServer(argv[1],atoi(argv[2]));
  sp->Initserver();
  sp->Start();
  delete sp;
  
   return 0;

}
