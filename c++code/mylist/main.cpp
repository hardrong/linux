#include "mylist.hpp"

int main()
{
          my::List<int> l;
          l.Push_back(2);
          l.Push_back(2);
          l.Push_back(3);
          l.Push_back(4);
          l.Push_back(7);
          l.Push_back(5);
  my::List<int>::iterator it = l.begin();
      while (it != l.end())
      {
        std::cout << *it << " ";
                    ++it;                        
      }
      std:: cout <<std:: endl;
  return 0;
}
