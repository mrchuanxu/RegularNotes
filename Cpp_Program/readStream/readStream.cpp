#include <iostream>
#include "readStream.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

istream& process_input(istream &is){
  string buf;
  while(is>>buf)
    cout<< buf <<endl;
  auto old_state = is.rdstate();
  is.clear();
  return is;
};

int main(){
   // ofstream out1,out2;
   // auto old_state = cin.rdstate();
   // cin.clear();
  // fstream fstrm("./storyQuery.txt");
  vector<string> vecstr;
  ifstream in("storyQuery.txt");
  // ofstream out;
  if(in){
    string buf;
    while(in>>buf){
      vecstr.push_back(buf);
    }
  }
  for(auto ivec = vecstr.begin(); ivec != vecstr.end();++ivec){
     cout << *ivec <<endl;
  }
  cout << endl;
  in.close();
   //process_input(cin);

   return 0;
}
