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
public:
   // Sales_data(const string &s) : bookNo(s) {}
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
Sales_data add(const Sales_data&, const Sales_data&);
istream &read(istream&,Sales_data&);
ostream &print(ostream&,const Sales_data&);
#endif
