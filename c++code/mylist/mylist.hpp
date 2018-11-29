#ifndef __MY_LIST__
#define __MY_LIST__ 

#include <iostream>
namespace my
{
  template <class T>
    struct ListNode
    {
        ListNode(const T& value = T())
          :_prev(nullptr) 
           ,_next(nullptr) 
           ,_data(value) 
      {}

      ListNode<T> *_prev;
        ListNode<T> *_next;
        T _data;
    };
  template < class T,class Ref,class Ptr>
  struct __ListIterator
  {
    typedef ListNode<T> Node;
    typedef __ListIterator<T, Ref, Ptr> Self;
      Node *_node;
    __ListIterator( Node *node )
      :_node(node)
    {
      
    }
    Ref operator*()
    {
      return _node>_data;
    }
    Ptr operator->()
    {
       return &_node->_data;
    }
    Self &operator++()
    {
       _node = _node->_next;
       return *this; 
    }
    Self &operator--()
    {
      _node = _node->_prev;
      return *this;
    }
    Self operator++(int)
    {
      Self tmp(*this);
      _node = _node->_next;
      return tmp;
    }
   Self operator--(int)
   {
     Self tmp(*this);
     _node = _node->_prev;
     return tmp;
   }
   bool operator!=(const Self &it)
   {
     return *this != it;     
   }
   bool operator==(const Self &it)
   {
     return *this == it;
   }
  };
  template <class T>
    class List 
    {
      typedef ListNode<T> Node;
      public:
      typedef __ListIterator<T,T&,T*> iterator;
      typedef __ListIterator<T,const T&,const T*> const_iterator;
      List()
       :_head(new Node)
      {
        _head->_next = _head;
        _head->_prev = _head;
      }
      iterator begin()
      {
        return iterator(_head->_next);
      }
      iterator end()
      {
        return iterator(_head);
      }
      const_iterator begin() const
      {
         return const_iterator(_head->__next);
      }
      const_iterator end() const 
      {
        return const_iterator(_head);
      }

      List(const List<T> &l)
      {
          _head = new Node;
          _head->_next = _head;
          _head->_prev = _head;
          const_iterator it = l.begin();
          while(it != l.end())
          {
            Push_back(*it);
            it++;
          }
      }
      ~List()
      {
        clear();
        delete _head;
        _head = NULL;
      }
      void clear()
      {
        iterator it = begin();
        while(it != end())
        {
            iterator del = it;
            it++;
            delete del._node;
        }
        _head->_next = _head;
        _head->_prev = _head;
      }
      void Push_back(const T & x )
      {
             insert(end(),x);
      }
      void Pop_back()
      {
         erase(--end());
      }
      void Push_front(const T&x)
      {
        insert(begin(),x);
      }
      void Pop_front()
      {
         erase(begin());
      }
      bool empty()
      {
        return _head == _head->_next;
      }
      size_t Size()
      {
        iterator it = begin();
        size_t count = 0;
        while(it != end())
        {
          count++;
          it++;
        }
        return count;
      }
      void Insert(iterator pos, const T& x)
      {

      }
      iterator Erase(iterator pos)
      {

      }
  private:
     Node *_head;

    };
}
#endif 
