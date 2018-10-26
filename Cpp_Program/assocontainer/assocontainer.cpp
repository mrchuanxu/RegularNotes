#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <set>
#include <vector>

using namespace std;
pair<string,int> process(vector<string> &v){
    if(!v.empty()){
      return {v.back(),v.back().size()};
    }else{
      return pair<string,int>();
    }
}


int main(){
  map<string,size_t> word_count;
  set<int> iset = {1,2,3,4,5,66,7,7,8,9};
  set<int>::iterator set_it = iset.begin();
    cout << *set_it<<endl;
  string word;
  // while(cin >> word){
  //   ++word_count[word];
  // for(const auto &w : word_count){
  //   cout << w.first << "courrs" << w.second << endl;
  // }
  // }
  word = "fuckoff";
  word_count.insert(make_pair(word,1));
  word_count.insert(pair<string,size_t>(word,2));
  word_count.insert(map<string,size_t>::value_type(word,3));
  auto map_it = word_count.begin();
  cout << map_it->first << map_it->second << endl;


  return 0;
}
