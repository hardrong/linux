#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;
 int book = 0;
 pthread_rwlock_t rwlock;

 void *Reader(void *arg)
{
  for(;;)
  {
    pthread_rwlock_rdlock(&rwlock);
    cout << "read book:" << book <<  endl;
    pthread_rwlock_unlock(&rwlock);
    usleep(300000);
  }
}
void* Writer(void *arg)
{
  for(;;)
  {
     pthread_rwlock_wrlock(&rwlock);
     cout << " write book:" << book <<  endl;
     book++;
     pthread_rwlock_unlock(&rwlock);
     sleep(2);
  }
}
int main()
{
  pthread_t r,w;
  pthread_rwlock_init(&rwlock,NULL);
  pthread_create(&r,NULL,Reader,(void*)NULL);
  pthread_create(&w,NULL,Writer,(void*)NULL);

  pthread_join(r,NULL);
  pthread_join(w,NULL);
 
  pthread_rwlock_destroy (&rwlock);

  return 0;
}
