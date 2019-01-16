#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <vector>

using namespace std;

class StrBlob{
    public:
        typedef vector<string>::size_type size_type;
       StrBlob():data(make_shared<vector<string> >()){}
        StrBlob(initializer_list<string> il):data(make_shared<vector<string> >(il)){} // 使用参数列表初始化vector
        size_type size() const { return data->size();}
        bool empty() const { return data->empty();}
        void push_back(const string &t){return data->push_back(t);}
        void pop_back();
        string &front();
        string &back();
    private:
        shared_ptr<vector<string> > data; // 共享同一个数据？
        void check(size_type i,const string &msg) const;
};

void StrBlob::check(size_type i,const string &msg) const{
    if(i>=data->size())
        throw out_of_range(msg);
}

string& StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front();
}

string& StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back(){
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}
int main(){
//    const char *pi = "hello";
//    shared_ptr<string> pstr = make_shared<string>("hi llo");
//    cout << *pstr << endl;
   StrBlob b1({"i am not","who are you","what?"});
   StrBlob b2 = b1;
   cout << b2.back() <<endl;
   shared_ptr<int> p(new int(42));
   int *q = p.get(); // 将指针的访问权限传递给代码
   {
       shared_ptr<int>(q);
       // cout << *q << endl;
   }
   cout << *p << endl;
   return 0; 
}