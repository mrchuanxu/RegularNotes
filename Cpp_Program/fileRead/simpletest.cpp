#include <iostream>
#include <string>
#include "simpleCode.h"

using namespace std;

int main(){
  Sales_data rhs,lhs;
  read(cin,rhs);
  read(cin,lhs);
  rhs.operator+=(lhs);
  print(cout,rhs);
  operator<<(cout,lhs);
  return 0;
}
