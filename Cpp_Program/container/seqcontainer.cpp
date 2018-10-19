#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <forward_list>
#include <array>
#define pie 3.14

using namespace std;

int main(){
  list<string> lstr = {"we","are","not","the","one"};
  lstr.assign(10,"hey!");
  forward_list<string> words(lstr.begin(),lstr.end());
  auto pre = words.before_begin();
  array<int,10> ia1 = {1,2,3,4,5,6,7,8,9,9};
  list<string> names;
  vector<const char*> oldstyle = {"i","am","not","a","man"};;
  names.assign(oldstyle.cbegin(),oldstyle.cend());
  for(auto iter = words.begin();iter!=words.end(); ++iter){
     cout << *iter <<endl;
  }
  list<string>::iterator iter;
  vector<int>::difference_type count;

  return 0;
}
