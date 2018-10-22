#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <forward_list>
#include <array>
#include<stack>
#define pie 3.14

using namespace std;

int main(){
  list<string> lstr = {"we","are","not","the","one"};
  lstr.assign(10,"hey!");
  forward_list<string> words(lstr.begin(),lstr.end());
  auto pre = words.before_begin();
  array<int,10> ia1 = {1,2,3,4,5,6,7,8,9,9};
  list<string> names;
  vector<const char*> oldstyle = {"i","am","not","a","man"};
  list<const char*> lst(10,"ccc");
  names.assign(oldstyle.cbegin(),oldstyle.cend());
  // for(auto iter = lst.begin();iter!=lst.end(); ++iter){
  //    cout << *iter <<endl;
  // }
  list<string>::iterator iter;
  vector<int>::difference_type count;

  const char *cp = "hello,Trans!";
  char noNull[] = {'H','i'};
  string s1(cp);
  string s2(noNull,2);
  string s3 = s1.substr(0,3);
  cout << s3 <<endl;
  s1.insert(6,"Mr.");
  s1.erase(0);
  cout << s1 << endl;
  string numbers("01234567"),name("r2d2");
  auto pos = name.find_first_of(numbers);
  int i = 42;
  string s = to_string(i);
  // double d = stod(s1);
  //cout << d << endl;
  stack<string> sta;
  sta.push("we");
  sta.push("are");
  cout << sta.top() << endl;
  return 0;
}
