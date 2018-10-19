#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
using namespace std;

int main(){

  list<string> lstr = {"we","are","not","be"};
  auto result = find(lstr.cbegin(),lstr.cend(),"h");
  cout << *result <<endl;
  auto sumstr = accumulate(lstr.cbegin(),lstr.cend(),string(""));
  cout << sumstr <<endl;
  return 0;
}
