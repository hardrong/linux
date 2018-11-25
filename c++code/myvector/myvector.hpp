#pragma once 

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;

namespace  my
{

  template< class T>
  class Vector
  {
     public:
         typedef T* iterator;
         typedef const T* const_iterator;
        size_t size() const
        {
          return _finish-_start;
        }
        size_t capacity() const
        {
          return _endOfStorage-_start;
        }
        iterator begin()
        {
          return _start;
        }
        iterator cbegin()
        {
              return _finish;
        }
        iterator cend()
        {
              return _start;
        }
        iterator end()
        {
          return _finish;
        }
           Vector()
             :_start(nullptr)
              ,_finish(nullptr)
              ,_endOfStorage(nullptr)
    {

    }
      Vector(int n,const T & value = T())
        :_start(nullptr)
         ,_finish(nullptr)
         ,_endOfStorage(nullptr)
      {
          reserve(n);
          while(n--)
          {
            Push_back(value);
          }
      }
      Vector(const Vector<T>& v)
        :_start(nullptr)
        ,_finish(nullptr)
         ,_endOfStorage(nullptr)
    {
          Reserve(v.Capacity());
            iterator it = begin(); 
            const_iterator vit = v.cbegin();   
            while (vit != v.cend())
            {      
              *it++ = *vit++;    
            }
                       
          _finish = _start + v.size();    
         _endOfStorage = _start + v.capacity();

    }
      void swap( Vector<T> &v)
      {
        swap(_start,v._start);
        swap(_finish,v._finish);
        swap(_endOfStorage,v._endOfStorage);
      }
          void  Push_back(const T &x)
          {
            insert(_finish,x);
          }
          void Pop_back()
          {
            erase(--end());
          }
          void reserve(size_t  n)
          {
              if(n > capacity())
              {
                //不能用memcpy，浅拷贝会出现多次释放空间。
                size_t sz = size();
                T * tmp =  new T[n];
                if(_start)
                {
                for(size_t i = 0; i < sz; ++i)
                 {
                   tmp[i] = _start[i];
                 }
                }
                _start = tmp;
                _finish = _start+sz;
                _endOfStorage = _start+n;
              }
          }
        iterator insert(iterator pos,const T& x)
        {
           assert(pos <= _finish && pos >= _start );
           if(_finish == _endOfStorage)
           {
             size_t sz = size();
             size_t newcapacity = capacity() == 0?2:capacity()*2;
             reserve(newcapacity);
             pos = _start+sz;
           }
           iterator it = _finish-1;
           while(it >= pos)
           {
             *(it+1) = *it;
             it--;
           }
          *pos = x;
          _finish++;
         return pos;
        }
        iterator erase(iterator pos)
        {
          assert(pos >= _start);
          for(size_t i = pos; i < size()-1; ++i)
          {
               _start[pos] = _start[pos+1];
          }
          --_finish;
          return pos;
        }
       T& operator[](size_t pos)
       {
           return _start[pos];
       }
       Vector<T>& operator=(Vector<T> & v)
       {
         swap(v);
         return *this;
       }
       template <class InputIterato>
         Vector( InputIterato first,InputIterato last)
         {
           reserve(last -first);
           while(first != last)
           {
             Push_back(*first);
             first++;
           }
         }
        void resize(size_t n,const T& value = T())
        {
          if(n <= size())
         {
            _finish = n;
            return;
         }
          if(n > capacity())
          {
          reserve(n);
          }
          iterator index = _finish;
          _finish = _finish+n;
          while(index != _finish)
          {
             *index = value;
             index++;
          }
        }
       ~Vector()
       {
         if(_start)
           delete[] _start;
         _start = _finish = _endOfStorage = nullptr;
       }
    private:
          iterator _start;
          iterator _finish;
          iterator _endOfStorage;
  };
}
