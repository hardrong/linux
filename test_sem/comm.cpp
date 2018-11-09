#include"comm.h"
using namespace std;
static int commSemSet(int nums,int flags)
{
  key_t key = ftok(PATHNAME,PROJ_ID);
  if(key < 0)
  {
    perror("ftok");
    exit(-1);
  }
  int semid  = semget(key,nums,flags);
  if(semid < 0)
  {
    perror("semget");
    exit(-1);
  }
  return semid;
}
int createSemSet(int nums)
{
  int semmid = commSemSet(nums,IPC_CREAT|IPC_EXCL|06666);
  return semmid;
}
int initSem(int semid,int nums,int initVal)
{
 union semun _un;
 _un.val = initVal;
 if(semctl(semid,nums,SETVAL,_un)< 0)
 {
    perror("semctl");
    return -3;
 } 
     return 0;
}
int getSemSet(int nums)
{
  return commSemSet(nums,IPC_CREAT);
}
static int commPV(int semid,int who,int op)
{
  struct sembuf _sf;
  _sf.sem_num = who;
  _sf.sem_op = op;
  _sf.sem_flg = 0;
  if(semop(semid,&_sf,1) < 0)
  {
    perror("semop");
    return -1;
  }
  return 0;
}
int P(int semid,int who)
{
   return commPV(semid,who,-1);
}
int V(int semid ,int who)
{
 return commPV(semid,who,1);
}
int destroySemSet(int semid)
{

  if(semctl(semid,0,IPC_RMID) < 0)
  {
    perror("semctl");
    exit(-1);
  }
  return 0;
}
