#ifndef SIMPLE_CODE_H
#define SIMPLE_CODE_H
#include <iostream>
#include <string>
using namespace std;

class Sales_data
{
  friend Sales_data add(const Sales_data&, const Sales_data&);
  friend istream &read(istream&,Sales_data&);
  friend ostream &print(ostream&,Sales_data&);
  friend istream& operator>>(istream&,Sales_data&);
  friend ostream& operator<<(ostream&,const Sales_data&);
  friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
   // Sales_data(const string &s) : bookNo(s) {}
  Sales_data& operator+=(const Sales_data&);
  Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
  Sales_data():Sales_data("#####",0,0){};
  // Sales_data(istream &is):Sales_data(){read(is,*this);};
  string isbn() const { return this->bookNo; };
  Sales_data &combine(const Sales_data &);
  explicit Sales_data(const string &s):bookNo(s){}
  explicit Sales_data(istream&);
private:
  double avg_price() const { return units_sold ? revenue / units_sold : 0; };
  unsigned units_sold = 10;
  double revenue = 0.0;
  string bookNo;
};
Sales_data &Sales_data::combine(const Sales_data &rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}
istream &read(istream &is, Sales_data &item){
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;
  return is;
}

ostream &print(ostream &os, Sales_data &item){
  os << item.isbn() << "print" << item.units_sold << "print" << item.revenue << " " << item.avg_price();
  return os;
}
ostream &operator<<(ostream &os,const Sales_data &item){
  os << item.isbn() << "ostream" << item.units_sold << "ostream" << item.revenue << "ostream" << item.avg_price();
  return os;
}

istream &operator>>(istream &is,Sales_data &item){
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  if(is)
      item.revenue = item.units_sold * price;
  else
      item = Sales_data();
  return is;
}

Sales_data operator+(const Sales_data &rhs, const Sales_data &lhs){
  Sales_data sum = rhs;
  sum += lhs;
  return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs){
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}
#endif
