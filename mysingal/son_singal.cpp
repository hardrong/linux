#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
using namespace std;
void handler(int sig)
{
  pid_t id;
  while((id = waitpid(-1,NULL,WNOHANG)) > 0) 
  {
    cout << "wait child sucess:" << id <<endl;

  }
  cout << "child quit" << endl;
}
int main()
{
  signal(SIGCHLD,handler);
  pid_t id;
  if((id = fork()) == 0)
  {
     cout << "child :" << getpid() << endl;
     sleep(2);
     exit(1);
  }
     while(1)
     {
    cout<<"father proc is doing some thing\n"<<endl;
    sleep(1);
  
     }
      return 0;
}
