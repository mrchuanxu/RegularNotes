#ifndef STRVEC_H
#define STRVEC_H
#include <string>
#include <memory>
using namespace std;
// 主要是allocator的使用，一块申请到的内存，怎么去使用
class StrVec{
  public:
      StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
      StrVec(const StrVec&);
      StrVec &operator=(const StrVec&);
      ~StrVec();
      void push_back(const string&);
      size_t size() const{ return first_free - elements;}
      size_t capacity() const { return cap-elements;}
      string *begin() const { return elements; }
      string *end() const { return first_free;}
  private:
      static allocator<string> alloc; // 让这个声明在整个程序是有用的！
      void chk_n_alloc() { if(size() == capacity()) reallocate();}
      pair<string*, string*> alloc_n_copy(const string*,const string*);
      void free();
      void reallocate();
      string *elements;
      string *first_free;
      string *cap;

};
void StrVec::push_back(const string& s){
  chk_n_alloc();
  alloc.construct(first_free++,s); // 创建对象
}

pair<string*,string*> StrVec::alloc_n_copy(const string *b, const string *e){
  auto data = alloc.allocate(e-b);
  return {data,uninitialized_copy(b,e,data)};
}

void StrVec::free(){
  if(elements){
    for(auto p = first_free; p!=elements;){
      alloc.destroy(--p);
      alloc.deallocate(elements,cap-elements);
    }
  }
}
StrVec::StrVec(const StrVec &s){
  auto newdata = alloc_n_copy(s.begin(),s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}
StrVec::~StrVec() { free(); }
StrVec &StrVec::operator=(const StrVec &rhs){
  auto data = alloc_n_copy(rhs.begin(),rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::reallocate(){
  auto newcapacity = size()?2*size():1;
  auto newdata = alloc.allocate(newcapacity);
  // auto last = uninitialized_copy(make_move_iterator(begin()),make_move_iterator(end()),newdata);
  // free();
  // elements = newdata;
  // first_free = last;
  // cap = elements+newcapacity;
  auto dest = newdata;
  auto elem = elements;
  for(size_t i = 0;i!=size();++i)
      alloc.construct(dest++,move(*elem++));
  free();
  elements = newdata;
  first_free = dest;
  cap = elements+newcapacity;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept{
  if(this != &rhs){
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

#endif STRVEC_H
