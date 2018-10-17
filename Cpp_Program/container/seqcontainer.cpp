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
  forward_list<string> words(lstr.begin(),lstr.end());
  array<int,10> ia1 = {1,2,3,4,5,6,7,8,9,9};
  return 0;
}
