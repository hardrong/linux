#include "mystring.h"
  const size_t npos = -1;
my::string::string(const char* str)
{
   if(str == NULL)
   {
     assert(str != NULL);
     return ;
   }
   _size = strlen(str);
   _capacity = _size;
   _str = new char[_capacity+1];
   strcpy(_str,str);
   

}
my::string::string(const my::string& s)
   :_str(new char[s._capacity+1])
    ,_capacity(s._capacity)
    ,_size(s._size)
{
     strcpy(_str,s._str);
}
my:: string &my::string::operator=(const my::string&s)
{
  //传统写法
  if(this != &s)
  {

     _size = s._size;
     _capacity = s._capacity;
     delete[] _str;
     _str = new char[s._capacity+1];
     strcpy(_str,s._str);
  }
  //现代写法
  // 传值而不是引用对象s
  // swap(_str,s._str);
  // return *this;
   return *this;
}
my::string::~string()
{
  if(_str)
  {
    delete[] _str;
    _str = NULL;
  }
}
my::string::Iterator my::string:: Begin()
{
   return _str;  
}
my::string::Iterator my::string:: end()
{
   return _str+_size;  
}

void my::string:: PushBack(char c)
{
  if(_size == _capacity)
  {
    reserve(_capacity*2);
  }
  _str[_size++] = c;
  _str[_size] = '\0';

}
  void my::string::Append(size_t n,char c)
{
   if(_size+n >= _capacity)
   {
     reserve(_capacity+n);
   }
   while(n--)
   {
     _str[_size++] = c;
   }
   _str[_size] = '\0';
   //while(n--)
   // *this.PushBack(c);
}
my:: string &my::string::operator+=(char c)
{
    PushBack(c);
    return *this;
} 
  void my::string::Swap(string &s)
{
  std::swap(_str, s._str);
    std:: swap(_size , s._size);
   _capacity = s._capacity;

}
  const char *my::string::C_Str()const 
{
   return _str; 
}
  size_t my::string::size()const
{
   return _size;
}
size_t my::string::capcity()const
{
 return _capacity;

}
bool my::string::empty()const
{
  return 0 == _size;
}
  void my::string::resize(size_t newsize,char c)
{
         if(newsize > _size)
         {
            if(newsize > _capacity)
            {
              reserve(newsize);
            }
            memset(_str+_size,c,newsize-_size);
         }
         _size = newsize;
         _str[_size] = '\0';
}
  void my::string::reserve(size_t newcapacity)
{
  
  if(newcapacity > _capacity)
  {
   char *str = new char[newcapacity+1];
    strcpy(str,_str);
  delete[] _str;
  _str = str;
  _capacity = newcapacity;

}
}
  char &my::string:: operator[](size_t index)
{
  assert(index < _size);
   return _str[index];
}
  const char&my::string:: operator[](size_t index)const 
{
  assert(index < _size);
    return _str[index];
}
bool my::string:: operator<(const string &s)
{
  size_t index = 0;
  size_t tmp = 0;
   while(index < _size && tmp < s._size)
   {
     if(_str[index] > s._str[tmp])
     {
       return false;
     }
     tmp++;
     index++;
   }
   if(index == _size || tmp != s._size)
     return true;
   return false;

}
bool my::string:: operator<=(const string &s)
{
  if(*this < s || *this == s)
  return true;
  return false;
}
bool my::string:: operator>(const string &s)
{
   return !(*this <= s);
}
  bool my::string::operator>=(const string &s)
{
  return !(*this < s);
}
  bool my::string:: operator==(const string &s)
{
  if(_size == s._size)
  {
    size_t tmp = 0;
    while(tmp < _size)
    {
      if(_str[tmp] != s._str[tmp])
        return false;
      tmp++;
    }
  }
  return false;
}
  bool my::string::operator!=(const string &s)
{
  return !(*this == s);
}
size_t my::string::find (char c,size_t pos) const
{

     for(size_t i = pos; i < _size; ++i)
     {
       if(_str[i] == c)
         return i;
     }
     return -1;
}
my:: string my::string::substr(size_t pos,size_t n)
{
   assert(pos < n && n < _size);
  string tmp;
  for(size_t i = pos ; i < n; ++i)
  {
    tmp += _str[i];
  }
  return tmp;
}
my:: string &my::string::insert(size_t pos,char c)
{
    assert(pos <= _size&& pos >0);
    if(_size == _capacity)
    {
      reserve(_capacity*2);
    }
    _size++;
    for(size_t i = _size; i > pos; --i)
    {
      _str[i] = _str[i-1];
    }
    _str[pos] = c;
    return *this;


}
my:: string &my::string::insert(size_t pos,const char *str)
{
   assert(pos >= 0 && pos < _size);
    int len = strlen(str);
   if(_size+len > _capacity)
   {
     reserve(_size+len);
   }
   for(int i =(int) pos; i < len; i++)
   {
         insert(i,str[i]);
   }
   _size += len;
   return *this;
}
my:: string &my::string::erase(size_t pos,size_t len)
{
   assert(pos < _size );
   if(len == npos|| pos+len > _size )
   {
     _str[pos] = '\0';
     _size = pos;
   }
   else 
   {
     for(size_t i = 0; i < len; i++)
     {
       _str[pos] = _str[pos+len];
       pos++;
     }
     _size -= len;
     _str[pos] = '\0';
   }
   return *this;
}
ostream & my::operator<<(ostream&_cout,const my::string &s)
{
  cout << s._str;
  return _cout;
}
