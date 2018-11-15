#include<iostream>
#include <unistd.h>
#include <signal.h>
void handler(int signo)
{

}
int  mysleep(int sec)
{
  struct sigaction act,oact;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM,&act,&oact);
  alarm(sec);
  pause();
  int ret = alarm(0);
  sigaction(SIGALRM,&oact,NULL);

  return ret;
}
int main()
{
  mysleep(2);
  return 0;
}
