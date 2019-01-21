/***
 * bind使用
 * ***/
#include <iostream>
#include <string>
#include <functional>
#include <map>

using namespace std;
using namespace placeholders;

bool lengthCompare(const string& a,const string& b){
    cout << "yes!" << endl;
    return a.size()>b.size();
}

bool (*pf)(const string&,const string&);
using PF = bool(*) (const string&,const string&);

PF f1(const int& a){
    //点用？
    cout << a << endl;
    return lengthCompare;
}

auto f11(const int& a)->bool(*)(const string&,const string&){
    cout << a << endl;
    return lengthCompare;
}
class IntReturn{
    public:
    IntReturn() = default;
    int operator()(){
        return 42;
    }
};
void print(){
    int i = 42;
    int ir = 43;
    int ie = 44;
    auto f = [=,&ir](){ return i;};
    f();
    cout << i << endl;
}
class Request{
    function<int(double &)> oper;
    int results;
    double values;
    public:
        Request(const string& s);
        void execute(){
            [this](){ results = oper(values);};//根据结果执行相应的操作
        }
};
// int f(double){
//     cout << "sss" << endl;
//     return 0;
// }
// function<int(double)> fct{f};
void funcc(int a,int b,int c){
    cout << a << endl;
    cout << c << endl;
}
int main(void){
    // pf = lengthCompare;
    // if(pf("rrrs","sss")){
    //     cout << "yes"<<endl;
    // };
    // IntReturn inr;
    // cout << inr() << endl;
    // bool (*pf1)(const string&,const string&);
    // pf1 = f1(9);
    // pf1("sss","ddd");
    // pf1 = f11(10);
    // pf1("eeee","sssssss");

    // auto f = []{return 42;};
    // cout << f() << endl;
    auto g = bind(funcc,_2,3,_1);
    g(1,3);
    print();
    int iu = 9;
    int &ru = iu;
    ++ru;
    cout << iu << endl;
    // fct(4.5);
    function<int(double)> f;
    f = [](double x){ return x>0?x+0.5:x;};
    f(4.6);
    return 0;
}