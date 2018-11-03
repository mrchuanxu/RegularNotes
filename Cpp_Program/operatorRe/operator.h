#include <iostream>
#include <string>

using namespace std;

class Sales_data{
  friend istream& operator>>(istream&,Sales_data&);
  friend ostream& operator<<(ostream&,const Sales_data&);
  friend Sales_data operator+(const Sales_data&, const Sales_data&);
  public:
      Sales_data& operator+=(const Sales_data&);
};

ostream &operator<<(ostream &os,const Sales_data &item){

}
