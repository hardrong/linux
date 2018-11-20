#pragma once 

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using std::cout;
using std::ostream;
using std::iostream;
using std::cin;
using std::endl;
using namespace std;
namespace my 
{
class string
{
  public:
  typedef char*Iterator;
  public:
  string(const char* str = "");
  string(const string& s);
  string & operator=(const string&s);
  ~string();
  Iterator Begin();
  Iterator end();
  void PushBack(char c);
  void Append(size_t n,char c);
  string &operator+=(char c);
  void Swap(string &s);
  const char *C_Str()const;
  size_t size()const;
  size_t capcity()const;
  bool empty()const;
  void resize(size_t newsize,char c);
  void reserve(size_t newcapacity);
  char &operator[](size_t index);
  const char& operator[](size_t index)const;
  bool operator<(const string &s);
  bool operator<=(const string &s);
  bool operator>(const string &s);
  bool operator>=(const string &s);
  bool operator==(const string &s);
  bool operator!=(const string &s);
  size_t find (char c,size_t pos = 0) const;
  string substr(size_t pos,size_t n);
  string &insert(size_t pos,char c);
  string &insert(size_t pos,const char *str);
  string &erase(size_t pos,size_t len);
  
 private:
  friend ostream & operator<<(ostream&_cout,const my::string &s);
 private:
     char *_str;
     size_t _capacity;
     size_t _size;
  };
 
 ostream & operator<<(ostream&_cout,const my::string &s);
};
