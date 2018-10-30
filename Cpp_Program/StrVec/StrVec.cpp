#include <iostream>
#include <string>
#include <utility>
using namespace std;

int main(){
  int  i = 42;
  const int &r = i * 42;
  int &&rv = i*42;
  cout << rv << endl;
  int &&rr1 = 42;
  int &&rr2 = std::move(rr1);
  cout << rr1 << endl;

  return 0;
}
