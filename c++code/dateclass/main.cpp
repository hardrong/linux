#include"date.h"
using std::cout;
using std::cin;
int main()
{
  Date s(2022,1,6);
  Date now(2018,11,5);
  
 s.print();   
 now.print();   
 cout << (s-now)<< endl;
 s.print();   
  return 0;
}
