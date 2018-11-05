#include"date.h"
void Date::print()
{
 cout<<_year<<"-" <<_month <<"-"<< _day <<endl;
}
int Date::GetMonthDay(int year,int month )
{
 static const int monthDay[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

 if((month == 2) && ((year%4 == 0&&year%100 != 0)||(year%400 == 0)))
 {
   return 29;
 }
   return monthDay[month];
}
 Date & Date::operator=(const Date &d)
{
 
   if(*this != d)
   {
     _year = d._year;
     _month = d._month;
     _day = d._day;
   }
   return *this;
}
  Date:: Date(int year,int month,int day)
{

   if(year > 0 && month < 13 && month > 0 && day <= GetMonthDay(year,month))
   {
     _year = year;
     _month = month ;
     _day = day;
   }
   else 
   {
     cout << "Date error"<< endl;
   }
}
  Date::Date(const Date &d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
}
   Date  Date:: operator+(int days)
{
  Date ret(*this);
  ret += days;
  return ret;
    
}
Date& Date::operator+=(int day)
{  
 if(day < 0)
 {
   day = -day;
   _day -= day;
   return *this;
 }
 _day += day;
 while(_day > GetMonthDay(_year,_month))
 {
   _day -= GetMonthDay(_year,_month);
   if(_month == 12)
   {
     _month = 1;
     _year++;
   }
   else
   {
     _month++;
   }
 }
  return *this;
}
Date& Date::operator-=(int day)
{
 _day -= day;
 while(_day <= 0)
 {
   if(_month == 1)
   {
     _year--;
    _month = 12;

   }
   else 
   {
       _month--;
   }
   _day += GetMonthDay(_year,_month);
 }
 return *this;
}
Date Date:: operator-(int days){

  Date ret(*this);
  ret -= days;
  return ret;
}
    int Date::operator-(const Date& d)
{
   Date maxDay(*this);
   Date minDay(d);
   while(maxDay < minDay)
   {
     maxDay =d;
     minDay = *this;
   }
   int days = 0;
   while(maxDay != minDay)
   {
     ++minDay;
     days++;
     
   }
   return days;
}
    Date& Date::operator++()
{
   (*this) = (*this) +1;
   return *this;

}
    Date& Date::operator--()
{
   (*this) -= 1;
 return *this;
}
    Date Date::operator++(int)
{
     Date ret(*this);
      ret += 1;
     *this = ret;
      return *this;
}
    Date Date::operator--(int)
{
  Date ret(*this);
  ret -= 1;
     *this = ret;
  return *this;
}
    bool Date::operator>(const Date&d)
{
  if(_year > d._year || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day))
    return true;
  return false;
}
    bool Date::operator<(const Date& d)
{
 return !(*this > d || (*this == d));
}
   bool Date::operator!=(const Date& d)   
{
 return !(_year == d._year && _month == d._month && _day == d._day);
}
    bool Date:: operator<=(const Date& d)
{
   return !(*this > d);

}
    bool Date:: operator==(const Date& d)
{
 return (_year == d._year && _month == d._month && _day == d._day);

}
  
