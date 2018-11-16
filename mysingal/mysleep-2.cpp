#include<iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
void handler(int signo)
{

}
int  mysleep(int sec)
{
  sigset_t newmask,oldmask,suspmask;
  struct sigaction act,oact;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM,&act,&oact);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGALRM);
  sigprocmask(SIG_BLOCK,&newmask,&oldmask);
  alarm(sec);
  suspmask = oldmask;
  sigdelset(&suspmask,SIGALRM);
  sigsuspend(&suspmask);
  int ret = alarm(0);
  sigaction(SIGALRM,&oact,NULL);

  return ret;
}
int main()
{
  mysleep(2);
  cout << "good"<<endl;
  return 0;
}
