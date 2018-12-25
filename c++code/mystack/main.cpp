#include <iostream>
#include <deque>
using namespace std;
template < class T,class Con = deque<T> >

class mystack
{
  private:
    Con _c;
  public:
    mystack()
    {

    }
    void push(const T&s)
    {
        _c.push_back(s);
    }
    void pop()
    {
     _c.pop_back();
    }
    T& Top()
    {
      return _c.back();
    }
    const T &Top()const 
    {
      return _c.back();
    }
   size_t Size()
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
  mystack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);

  cout << s.Size()<< endl;
  cout << s.empty() << endl;
  return 0;
}
