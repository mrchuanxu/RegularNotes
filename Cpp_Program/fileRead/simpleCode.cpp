#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

extern int i = 45; // 仅声明
const int j = 90;

struct Sales_data{
  string bookNo;
  unsigned units_sold = 10;
  double revenue = 0.0;
};
int main(){
  // int sum,value = 0;
  // int i = 42;
  // int *p;
  // int *&e = p;
  // e = &i;
  // // unsigned c = -100;
  // signed c2 = -100;
  // int &r = i;
  // int &s = r;
  // int *ip1, *ip2;
  // int* ip3;
  // ip1 = &c2;
  // ip3 = &c2;
  // void* pv = &c2;

  // const int bufSize = 512;
  // const int &r1 = bufSize;
  // const int *ptr = &bufSize;
  // int *const ptr1 = &i;
  // constexpr int mf = 20;
  // auto item = i+1;

  // while(cin>>value){
  //   sum += value;
  // }
  // cout << "sum:"<< c+sum << c2+sum << endl;
  // cout << '\7'<<endl;
  // const int ci = j;
  int iaa[3][4];
  string s1("wearetheworld!");
  for(auto &c : s1){
    c = toupper(c);
  }
  char ca[] = {'a','b','c','\0'};
  char cb[] = {'c','g','f'};
  int ia[] = {1,2,3,4,5,6,7,8};
  auto ia2(ia);
  *ia2 = 42;
  string s4(10,'f');
  Sales_data accum, trans, *salesptr;
  // cin >> accum.bookNo >> accum.units_sold >> accum.revenue;
  cout << accum.units_sold << endl;
  cout << std::strlen(ca) << endl;
  cout << std::strcmp(ca,cb) << endl;
  cout << sizeof ca << endl;
  // string line;
  // while(getline(cin,line))
  //    cout << line << endl;
  // cout << salesptr->units_sold << endl;
  // cout << item << endl;
  return 0;
}


