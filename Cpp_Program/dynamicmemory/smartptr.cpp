#include <iostream>
#include "StrBlobPtr.h"
#include "StrBlob.h"
#include <fstream>
using namespace std;

int main(){
  ifstream ifs("./phone.txt");
  StrBlob sb;
  string s;
  while(getline(ifs,s)){
    sb.push_back(s);
  }
  for(StrBlobPtr sbp = sb.begin();sbp != sb.end();sbp.incr()){
    cout << sbp.deref() << endl;
  }
  return 0;
}
