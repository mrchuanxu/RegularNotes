#include <iostream>
#include <string>

using namespace std;

class Foo{
  public:
      Foo() = default;
      Foo(const Foo&); // 拷贝构造
      Foo& operator=(const Foo&);
      ~Foo();
};

class Sales_data{
  public:
      Sales_data() = default; // 显式要求生成合成版本！！！
      Sales_data(const Sales_data&) = default;
      Sales_data& operator=(const Sales_data& rhs){
          bookNo = rhs.bookNo;
          units_sold = rhs.units_sold;
          revenue = rhs.revenue;
          return *this;
      }
      ~Sales_data() = default;
  private:
      string bookNo;
      int units_sold;
      double revenue = 0.0;
};
Sales_data::Sales_data(const Sales_data &orig):bookNo(orig.bookNo),units_sold(orig.units_sold),revenue(orig.revenue){}

string null_p("0000000");


struct noCopy{
  noCopy() = default;
  noCopy(const noCopy&) = delete;
  noCopy& operator=(const noCopy&) = delete;
  ~noCopy() = default;
};

// 类值
class HasPtr{
  friend void swap(HasPtr&,HasPtr&);
  public:
      HasPtr(const string &s = string()):ps(new string(s)),i(0){}
      HasPtr(const HasPtr &p):ps(new string(*p.ps)),i(p.i){}
      HasPtr& operator=(const HasPtr&); // 类值行为
      ~HasPtr(){
        delete ps;
      }
  private:
      string *ps;
      int i;
};
inline void swap(HasPtr &rhs,HasPtr &lhs){
  using swap;
  swap(lhs.ps,rhs.ps);
  swap(lhs.i,rhs.i);
}
// HasPtr::HasPtr(const HasPtr &ptr):ps(new string(*(ptr.ps))),i(ptr.i){}
HasPtr& HasPtr::operator=(const HasPtr &rhs){
  auto newp = new string(*rhs.ps);
  delete ps;
  ps = newp; // 从右侧运算对象拷贝数据到本对象
  i = rhs.i;
  return *this;
}

// 类指针
class HasPtrPointer{
  public:
      HasPtrPointer(const string &s = string()):ps(new string(s)),i(0),use(new size_t(1)){}
      HasPtrPointer(const HasPtrPointer &p):ps(p.ps),i(p.i),use(p.use){++*use;} // 指针复制
      HasPtrPointer& operator=(const HasPtrPointer&);
      ~HasPtrPointer();
  private:
      string *ps;
      int i;
      size_t *use;
};
HasPtrPointer::~HasPtrPointer(){
  if(--*use == 0){
    delete ps;
    delete use;
  }
}
HasPtrPointer& HasPtrPointer::operator=(const HasPtrPointer &rhs){
  ++*rhs.use;
  if(--*use == 0){
    delete ps;
    delete use;
  }
  ps = rhs.ps;
  i = rhs.i;
  use = rhs.use;
  return *this;
}

