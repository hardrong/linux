#include "myvector.hpp"

int main()
{
   my::Vector<int> first(3,0);
   first.Push_back(1);
   for(size_t i = 0; i < first.size(); ++i)
   {
     cout << first[i] << " ";
   }
   cout << endl;
   first.insert(first.begin(),9);
   for(const auto& e : first)
   {
     cout << e << " ";
   }
   cout << endl;
   my::Vector<int>::iterator it = first.begin();
   while(it  != first.end())
   {
     cout << *it << " ";
     it++;
   }
  cout << endl;

  return 0;
}
