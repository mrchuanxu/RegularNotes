#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "StrBlob.h" // 引入之后不用前向声明
using namespace std;
class StrBlobPtr{
  public:
      StrBlobPtr():curr(0){}
      StrBlobPtr(StrBlob &a,size_t sz = 0):wptr(a.data),curr(sz){}
      bool operator != (const StrBlobPtr& p){ return p.curr != curr;}
      string& deref() const{
        auto p = check(curr,"deference past end");
        return (*p)[curr];
      }
      StrBlobPtr& incr(){
        check(curr,"increment past end of StrBlobPtr");
        ++curr;
        return *this;
      }
      StrBlobPtr& operator++(int);
      StrBlobPtr& operator--(int);
  private:
      weak_ptr<vector<string> > wptr;
      shared_ptr<vector<string> > check(size_t i, const string &msg) const{
        auto ret = wptr.lock();
        if(!ret)
            throw runtime_error("unbound StrBlobPtr");
        if(i>=ret->size())
            throw out_of_range(msg);
        return ret;
      }
      size_t curr;
};
StrBlobPtr StrBlob::begin(){ return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end(){ return StrBlobPtr(*this,data->size()); }
StrBlobPtr& StrBlobPtr::operator++(int){
  check(curr,"increment past end of StrBlobPtr");
  ++curr;
  return *this;
};
#endif
