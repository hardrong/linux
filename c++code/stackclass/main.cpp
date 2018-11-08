#include"main.h"
//class onlystack
//{
//  public:
//static onlystack Get()
// {
//         onlystack obj;
//         return obj;
//  }
//  private:
//    onlystack();
//};
// 第一种方法，直接把构造函数屏蔽，只给一个公有的成员函数，这样就这能在栈上了 
class onlystack
{
 public:
  onlystack()
  {

  }

  private:
  void *operator new(size_t size);
  void operator delete(void *p);
};
// second  way  把new 和delete屏蔽，这样就不能再堆上创建对象了。但是在全局和static创建的对象并没有禁用。
 int main()
{
  return 0;
}
