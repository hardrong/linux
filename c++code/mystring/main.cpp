#include "mystring.h"

int main()
{
  my::string s1;
 my::string s2("hello world");
 my::string s3(s2);
 cout << s1 << endl;
 cout << s2 << endl;
 cout << s3 << endl;
 s1.PushBack('2');
 s2.PushBack('!');
 cout << s1.size() << endl;
 cout << s2.capcity() << endl;
 cout << s3[2] << endl;
 string num("1234");
  // 迭代器给出统一方式去访问容器，屏蔽掉底层复杂的结构细节
   string::iterator it = num.begin();
      int value = 0;
        while (it != num.end())
          {
              value *= 10;
                  value += *it - '0';
                      ++it;
                        }
                          cout << value <<endl;
  
  return 0;
}
