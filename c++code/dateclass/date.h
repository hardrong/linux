#ifndef __DATE_H__
#define __DATE_H__
#include<iostream>
using namespace std;
class Date
{
  public:
    Date(int year = 2018,int month = 10,int day = 31);
    Date(const Date &d);
  Date& operator=(const Date& d);
    Date operator+(int days);
    Date operator-(int days);
    int operator-(const Date& d);
    Date& operator++();
    Date& operator--();
    Date operator++(int);
    Date& operator+=(int day);
    Date& operator-=(int day);
    Date operator--(int);
    bool operator>(const Date& d);
    bool operator<(const Date& d);
    bool operator>=(const Date& d);
    bool operator<=(const Date& d);
    bool operator==(const Date& d);
    bool operator!=(const Date& d);
    void print();
    int GetMonthDay(int year,int month);
 private:
    int _year;
    int _month;
    int _day;
};
#endif 
