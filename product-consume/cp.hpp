#ifndef __CP_HPP__
#define __CP_HPP__ 

#include <iostream>
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <mutex>
#include <time.h>
#include <stdlib.h>
using namespace std;
class BlockQueue
{
  private:
    void lockqueue()
    {
       pthread_mutex_lock(&lock);
    }
    void unlockqueue()
    {
      pthread_mutex_unlock(&lock);
    }
    bool QIsEmpty()
    {
       return bq.empty();
    }
    bool QIsfull()
    {
        return bq.size() == cap;
    }
    bool QIsHighWater_line()
    {
        return bq.size() == water_line;
    }
    void ProductWait()
    {
      pthread_cond_wait(&cond_p,&lock);    
      
    }
    void ConsumeWait()
    {
      pthread_cond_wait(&cond_c,&lock);    

    }
   void SingalConsume()
   {
    pthread_cond_signal(&cond_c);
   }
   void SingalProduct()
   {
    pthread_cond_signal(&cond_p);
   }
  
  public:
    BlockQueue(int num)
      :cap(num)
       ,water_line(num*2/3)
    {
      pthread_mutex_init(&lock,NULL);
      pthread_cond_init(&cond_p,NULL);
      pthread_cond_init(&cond_c,NULL);
    }
    ~BlockQueue()
    {
     pthread_cond_destroy(&cond_p);
     pthread_cond_destroy(&cond_c);
     pthread_mutex_destroy(&lock);
    }
    void PushData(int data)
    {
      lockqueue();
      while(QIsfull())
        ProductWait();
      bq.push(data);
      if(QIsHighWater_line())
        SingalConsume();
      unlockqueue();

    }
    void PopData(int &data)
    {
      lockqueue();
      while(QIsEmpty())
      {
        SingalProduct();
        ConsumeWait();
      }
      data = bq.front();
      bq.pop();
      unlockqueue();
   
    }

  private:
    queue<int> bq;
    size_t cap;
    size_t water_line;

   pthread_mutex_t lock;
   pthread_cond_t cond_c;// queue full
   pthread_cond_t cond_p;// queue empty
};
#endif
