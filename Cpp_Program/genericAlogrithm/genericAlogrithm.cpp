#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
using namespace std;

bool isShorter(const string &s1,const string &s2){
  return s1.size() < s2.size();
}

int main(){
  list<string> lstr = {"we","are","not","be"};
  auto result = find(lstr.cbegin(),lstr.cend(),"h");
  // cout << *result <<endl;
  auto sumstr = accumulate(lstr.cbegin(),lstr.cend(),string(""));
  // cout << sumstr <<endl;
  int a1[] = {1,2,3,4,5,6,7,8,9};
  int a2[sizeof(a1)/sizeof(*a1)];
  cout << sizeof(a2) << endl;
  auto ret = copy(begin(a1),end(a1),a2);
  cout << a2[3] << endl;
  #ifndef NDDEBUG
  sort(lstr.begin(),lstr.end(),isShorter);
  for(auto iter = lstr.begin();iter != lstr.end();++iter){
    cout << *iter << endl;
  }
  #endif
  return 0;
}
