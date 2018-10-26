#include <iostream>
#include <memory>
#include <list>
#include <string>
#include <vector>
using namespace std;
#define vc 100
static double pie = 3.14;

shared_ptr<string> p1;
shared_ptr<list<int>> p2;

shared_ptr<int> p3 = make_shared<int>(42);

shared_ptr<string> p4 = make_shared<string>(10,'h');
shared_ptr<int> p5 = make_shared<int>();
auto p6 = make_shared<vector<string>>();

shared_ptr<int> factory(const string &s){
  return make_shared<int>(s.size());
}

int* ifactory(const string &s){
  return new int(s.size());
};

int* use_factory(const string &s){
  int *p = ifactory(s);
  delete p;
  return p;
  // p = nullptr;
}

unique_ptr<double> pu(new double(3.14159));
int main(){
//auto q(p3);
auto q = factory("woshiyigedapingguo");
cout << *q << endl;
int *pi = new int(1024);
string *ps = new string;
int *pt = new int;
vector<int> *pv = new vector<int> {1,2,3,4,5,6};
auto pj = new auto("306624700");
const int* pci = new const int(2048);
const string *pcs = new const string("3000");
delete pi;
cout << *pi << endl;
delete pci; // pci仍然存放着之前的对象的值，但是所指向的内存已经被释放了，不存在了，pci现在是一个不确定指针（悬垂指针）
cout << *pci << endl;
pci = nullptr; // 可以将pci的值明确指出已经不再指向任何指针！
shared_ptr<int> p1(new int(1024));
cout << *p1 << endl;

int* puse = use_factory("take you here?");
cout << *puse << endl;
p1.reset(new int(3023));
cout << *p1 << endl;
// unique_ptr<double> pu2(pu.release());
// cout << *pu << endl;
//auto pw = make_shared<int>(42);
// weak_ptr<int> wd(p1);
// cout << *wd.lock() << endl;

int *pia = new int[10];
int *pia2 = new int[10]();
cout << *pia2 << endl;
delete [] pia2;
cout << *pia2 << endl;

// unique_ptr<int[]> up(new int[10]);
// up[0] = 10;
// cout << up << endl;
// up.release();
allocator<string> alloc;
auto const pal = alloc.allocate(10);
auto qal = pal;
//alloc.construct(qal++);
alloc.construct(qal++,10,'c');
cout << *qal << endl;
//alloc.construct(q++,"hi");
cout << *(*pv).begin() << endl;
auto pvu = alloc.allocate((*pv).size()*2);
auto qvu = uninitialized_copy((*pv).begin(),(*pv).end(),pvu);
uninitialized_fill_n(qvu,(*pv).size(),42);//??????
cout << qvu <<endl;
return 0;
}
