#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
#include <iterator>
#include <string>
#include <fstream>
#include <functional>
using namespace std;
using namespace std::placeholders;

bool isShorter(const string &s1,const string &s2){
  return s1.size() < s2.size();
}
// auto fun = [](const string &s1,const string &s2){
//   return a.size() < b.size();
// }

void bigges(vector<string> &words,ostream &os = cout, char c = '*'){
  for_each(words.begin(),words.end(),[&os,c](const string &s){os << s << c;});
}

void fcn3(){
  size_t v1 = 42;
  auto f = [v1]() mutable { return ++v1;};
  v1 = 0;
  auto j = f();
}



int main(){
  // vector<string> lstr = {"we","are","not","be"};
  // string words("Mr trans is my friend!");
  // auto result = find(lstr.cbegin(),lstr.cend(),"h");
  // // cout << *result <<endl;
  // auto sumstr = accumulate(lstr.cbegin(),lstr.cend(),string(""));
  // // cout << sumstr <<endl;
  // int a1[] = {1,2,3,4,5,6,7,8,9};
  // int a2[sizeof(a1)/sizeof(*a1)];
  // cout << sizeof(a2) << endl;
  // auto ret = copy(begin(a1),end(a1),a2);
  // cout << a2[3] << endl;
  // assert(1>2);
  // sort(lstr.begin(),lstr.end(),isShorter);  谓词

  // auto f = []{return 42;};

  // cout << f() << endl;
  // stable_sort(lstr.begin(),lstr.end(),[](const string &s1,const string &s2){return s1.size() < s2.size();});
  //   for(auto iter = lstr.begin();iter != lstr.end();++iter){
  //   cout << *iter << endl;
  // }
  // int sz = 3;
  // auto wc = find_if(lstr.begin(),lstr.end(),[sz](const string &a){return a.size() >= sz;});

  // cout << *wc << endl;
  // for_each(wc,lstr.end(),[](const string &s){cout << s <<endl;});
  vector<int> vi = {1,-2,3,4,-5,6,7};
  transform(vi.begin(),vi.end(),vi.begin(),[](int i){return i<0?-i:i;});
  for(auto iter = vi.begin();iter != vi.end();++iter){
     cout << *iter << endl;
  }
  vector<string> words = {"i","am","not","good"};
  vector<string> insewords = {"no","no","way"};
 //  sort(words.begin(),words.end(),bind(isShorter,_2,_1));
  // for(auto iter = words.begin();iter != words.end();++iter){
  //    cout << *iter << endl;
  // }
  // bigges(words);
  copy(words.cbegin(),words.cend(),inserter(insewords,insewords.begin()));
    for(auto iter = insewords.begin();iter != insewords.end();++iter){
     cout << *iter << endl;
  }
  istream_iterator<int> int_it(cin);
  istream_iterator<int> int_eof;
  ifstream in("./a.txt");
  istream_iterator<string> str_in(in);
  while(int_it != int_eof){
    vi.push_back(*int_it++);
  }


  return 0;
}
