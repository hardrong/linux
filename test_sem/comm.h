#pragma once 
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

#define PATHNAME "."
#define PROJ_ID 0x6666
union semun
{
  int val; //value for SERVAL
  struct semid_ds *but; //Buffer for IPC_STAT,IPC_SET
  unsigned short *array;  //Array for GETALL,SERALL
  struct seminfo *_buf; //Buffer for IPC_INFO
};
int createSemSet(int nums);
int initSem(int semid,int nums,int initVal);
int getSemSet(int nums);
int P(int semid,int who);
int V(int semid ,int who);
int destroySemSet(int semid);

