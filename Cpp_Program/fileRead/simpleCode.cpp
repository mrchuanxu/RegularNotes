#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include "simpleCode.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace std;

extern int i; // 仅声明
const int j = 90;
int getNumber(const string &s);
// struct Sales_data
// {
//   string isbn() const { return bookNo; };
//   Sales_data& combine(const Sales_data&);
//   double avg_price() const;
//   unsigned units_sold = 10;
//   double revenue = 0.0;
//   string bookNo;
// };
size_t count_calls()
{
  static size_t ctr = 0;
  return ++ctr;
}
void reset(int *ip)
{
  *ip = 0;
  cout << ip << endl;
}
void resetRef(int &i)
{
  i = 111;
}
void print(const int *arr)
{
  cout << arr[5] << endl;
}
void error_msg(initializer_list<std::string> li)
{
  for (auto beg = li.begin(); beg != li.end(); ++beg)
  {
    cout << *beg << " ";
  }
  cout << endl;
}

constexpr int new_size() { return 42; }
bool lengthCompare(const string &s1,const string &s2){
  return s1.size() > s2.size();
}
bool (*pf)(const string &s1,const string &s2);
void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &));
int main()
{
  pf = lengthCompare;
  bool b1 = pf("helloooo","googbye");
  cout << "b1" << b1 << endl;
  const string s1 = "hi";
  const string s2 = "bo";
  // useBigger(s1,s2,lengthCompare);
  for (size_t i = 0; i != 10; ++i)
  {
    cout << count_calls() << endl;
  }
  int i = 42;
  reset(&i);
  cout << "i=" << i << endl;
  resetRef(i);
  cout << "i=" << i << endl;
  int a[9] = {9};
  print(a);
  try
  {
    print(&i);
  }
  catch (std::runtime_error err)
  {
    cout << err.what() << endl;
  }
  // int (*func(int i))[10];
  // cout << func(10) << endl;

  // cout << attPtr(4)(4) << endl;
  cout << new_size() <<endl;
  error_msg({"funcationx", "okey", "yes"});
  int arr[10];
  int(*p2)[10] = &arr;
  Sales_data deleConstr;
  cout << deleConstr.bookNo << endl;
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
  // int iaa[3][4];
  // string s1("wearetheworld!");
  // for(auto &c : s1){
  //   c = toupper(c);
  // }
  // char ca[] = {'a','b','c','\0'};
  // char cb[] = {'c','g','f'};
  // int ia[] = {1,2,3,4,5,6,7,8};
  // auto ia2(ia);
  // *ia2 = 42;
  // string s4(10,'f');
  // Sales_data accum, trans, *salesptr;
  // // cin >> accum.bookNo >> accum.units_sold >> accum.revenue;
  // cout << accum.units_sold << endl;
  // cout << std::strlen(ca) << endl;
  // cout << std::strcmp(ca,cb) << endl;
  // cout << sizeof ca << endl;
  // // cin >> accum.units_sold >> trans.units_sold;
  // // if(accum.units_sold != trans.units_sold){
  // //   throw std::runtime_error("Data not equal");
  // // }
  // try{
  //   cin >> accum.revenue;
  //   cout << accum.revenue <<endl;
  // }catch(std::runtime_error err){
  //   cout << err.what()
  //        << "try again?" <<endl;
  // }
  // string line;
  // while(getline(cin,line))
  //    cout << line << endl;
  // cout << salesptr->units_sold << endl;
  // cout << item << endl;
  // char ch;
  // while (cin>>ch){
  //   switch(ch){
  //     case 'a': cout<<"please print b" <<endl;break;
  //     case 'b': cout<<"please print c" <<endl;break;
  //     case 'c': cout<<"please print d" <<endl;break;
  //     case 'r': cout<<"dont print" <<endl;break;
  //     default:
  //         cout << "fuck" <<endl;break;
  //   }
  // }
  // string str;
  // cin >> str;
  // begin:
  //    int sz = getNumber(str);
  //    if(sz <= 10){
  //      cout << str;
  //      goto begin;
  //    }else{
  //      cout << str;
  //    }
  // cout<<endl;
  // std::cerr << "Data must refer to same ISBN" << endl;
  return 0;
}

// int getNumber(const string &s){
//     return s.size();
// }
