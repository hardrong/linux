#include"myadd.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <wait.h>
#include <stdio.h>
using namespace std;
union semun 
{
  int val;
};
int main()
{
  int fd;
again:
   fd = open("./tmp",O_RDONLY);
  if(fd == -1)
  {
    if(errno == EINTR)
    {
      goto again;
    }
    perror("open");
    exit(1);
  
  }
 char buf[100];
  memset(buf,0,sizeof(buf));
  int r = read(fd,buf,sizeof(buf));
  if(r == -1)
  {
    perror("read");
    exit(1);
  }
  close(fd);
  int left = 0;
  int right = 0;
  //从buf中提取加数和被加数
  sscanf(buf,"%d+%d",&left,&right);
  int result = myadd(left,right);
    sprintf(buf,"%d+%d=%d\n",left,right,result);
    //创建共享内存，创建信号量
   int shmid =  shmget(1234,strlen(buf),IPC_CREAT|0666);
   if(shmid == -1)
   {
     perror("shmid");
     exit(1);
   }
  char *p =(char *) shmat(shmid,NULL,0);//挂载共享内存
  int semid = semget(1234,1,IPC_CREAT|0666);
  if(semid == -1)
  {
    perror("semid");
    exit(1);
  }
   union semun su;
    su.val = 1;
    semctl(semid,0,SETVAL,su);
    struct sembuf sb[1] = {{0,-1,0}};
    semop(semid,sb,1);
    strcpy(p,buf);
    struct sembuf sb1[1] = { {0,1,0} };
    semop(semid,sb1,1);
    shmdt(p);
    pid_t pid ;
    if((pid = fork()) == 0)
    {
      char ret[] = "./write";
      char *argv[] = {ret,NULL};
     execvp(argv[0],argv);
     perror("execp");
     exit(0);
    }
    waitpid(pid,NULL,0);
}

