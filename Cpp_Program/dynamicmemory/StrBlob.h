#ifndef STRBLOB_H
#define STRBLOB_H
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
using namespace std;
class StrBlobPtr; // 引用需要前向声明方可使用
class StrBlob{
  public:
      friend class StrBlobPtr;
      typedef vector<string>::size_type s_t;
      StrBlobPtr begin();
      StrBlobPtr end();
      StrBlob(initializer_list<string> li);
      StrBlob():data(make_shared<vector<string> >()){}
      StrBlob& operator=(const StrBlob& sb);
      s_t size() const { return data->size(); }
      bool empty() const { return data->empty();}
      void push_back(const string &t){ data->push_back(t);}
      void pop_back();
      string &front();
      string &back();
  private:
      shared_ptr<vector<string>> data;
      void check(s_t i,const string &msg) const;
};

// StrBlob::StrBlob():data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
void StrBlob::check(s_t i,const string &msg) const{
  if(i >= data->size())
      throw out_of_range(msg);
}
StrBlob& StrBlob::operator=(const StrBlob& sb){
  data = make_shared<vector<string> >(*sb.data);
  return *this;
}

string &StrBlob::front(){
  check(0,"front on empty StrBlob");
  return data->front();
}

string &StrBlob::back(){
  check(0,"back on empty StrBlob");
  return data->back();
}
void StrBlob::pop_back(){
  check(0,"pop_back on empty StrBlob");
  return data->pop_back();
}
#endif
