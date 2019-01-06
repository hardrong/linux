#include <iostream>

//不能被继承的类
//c++98 的方法
class func 
{
 private:
   func()
 {
 
 }
 public:
   static  func  getfunc()
   {
     return func();
   }
};
class student:public func 
{
 
//c++11
};
class fun final
{
  
};
int main()
{
  student s;
  return 0;
}
