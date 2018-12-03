#include "cp.hpp"

const int  num  = 5;
using namespace std;
void *consume_routine(void *arg)
{
   BlockQueue *bpq = (BlockQueue*)arg;
   int data;
   for(;;)
   {
     bpq->PopData(data);
     cout << "consume done ,data is:" << data << endl;
   }
    
}
void *product_routine(void *arg)
{
  BlockQueue *bpq = (BlockQueue*)arg;
  srand((unsigned long)time(NULL));
  for(;;)
  {
    int data = rand()%100+1;
    bpq->PushData(data);
    cout << "product done,data is:" << data << endl;
    usleep(100000);
  }

}
int main()
{
   pthread_t c,p;
   BlockQueue *bpq = new BlockQueue(num);

  pthread_create(&c,NULL,consume_routine,(void*)bpq);
  pthread_create(&p,NULL,product_routine,(void*)bpq);

     pthread_join(c,NULL);
     pthread_join(p,NULL);
     delete bpq;
     return 0;
}
