#include"comm.h"
int main()
{
  int semid = createSemSet(1);
  initSem(semid,0,1);
  pid_t id = fork();
  if(id == 0)
  {
    //int  _semid = getSemSet(0);
    while(1)
    {
      P(semid,0);
      cout << "我是子进程，我正在用显示器";
      fflush(stdout);
      cout <<endl;
      sleep(2);
      cout << "我已经用完了";
      fflush(stdout);
      cout << endl;
      V(semid,0);
 
    }
  } else 
    {
      while(1)
      {
      P(semid,0);
      cout << "我是父进程，我正在用显示器";
      fflush(stdout);
      cout << endl;
      sleep(3);
      cout << "我已经用完了";
      fflush(stdout);
      cout << endl;
       V(semid,0);
    }
      wait(NULL);
  }
        destroySemSet(semid);
         return 0;

}
