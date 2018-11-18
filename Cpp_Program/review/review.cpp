#include <iostream>
#include <string>

using namespace std;

extern int i;
int ival = 1024;
int &refVal = ival;
int *p = &ival;
int *&r = p;
const int ci = 42;
const int &r1 = ival;

int main(){
  cout << refVal << endl;
  cout << r1 << endl;
  return 0;
}
