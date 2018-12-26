#include<iostream>
#include<deque>
using namespace std;
template <class T, class Con = deque<T> >
class myqueue
{
 private:
   Con _c;
 public:
   myqueue()
   {

   }
   void push(const T &x)
   {
     _c.push_back(x);

   }
   void pop()
   {
     _c.pop_back();
   }
   T& front ()
   {
     return _c.front();
   }
   const T& front () const 
   {
        return _c.front();
   }
   size_t size()
   {
     return _c.size();
   }
   bool empty()
   {
     return _c.empty();
   }
};

int main()
{
  myqueue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.pop();
  cout << q.front() << endl;
  cout << q.size() <<endl;
  cout << q.empty() << endl;
  return 0;
}
