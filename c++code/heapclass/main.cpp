#include"main.h"
class heaponly
{
 public:
   static heaponly*CreatObject()
   {
     return new heaponly;
   }
 private:
   heaponly(){

   }
   heaponly(const heaponly&) = delete;
};
// 直接把拷贝构造函数和构造函数变为私有，给个接口，但是这不一定全在堆上，比如友元函数可以访问数据，所以再加一个
// delete,这是C++11的语法，不能使用了。
int main()
{
  return 0;
}
