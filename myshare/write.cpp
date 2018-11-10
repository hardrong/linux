#include "myadd.h"
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
int main()
{
  int shmid = shmget(1234,0,0);
  if(shmid == -1)
  {
    
    perror("shmid");
    exit(1);
  }
  int semid = semget(1234,1,0);
  char *p = (char *)shmat(shmid,NULL,0);
    struct sembuf sb[1] = {{ 0,-1,0 }};
    char buf[1024] = {};
    strcpy(buf,p);
    semop(semid,sb,1);
    struct sembuf sb1[1] = { {0,1,0} };
    semop(semid,sb1,1);
    shmdt(p);
   int fd = open("./tmp",O_RDWR|O_TRUNC);
   write(fd,buf,strlen(buf));
  return 0;
}
