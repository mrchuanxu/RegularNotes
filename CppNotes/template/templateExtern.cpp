#include <iostream>
#include <utility>
#include <exception>
#include "templateImpl.h"

/***
 * 使用尾置返回类型
 * 使用函数的参数、
 * 这样可以返回任意类型
 * 右值引用 特例化 实例化 类型转换 模版参数 可变参数模版 
 * ***/
template<typename T> auto fcn(T beg,T end)-> decltype(*beg){
    return *beg;
} 

/***
 * remove_reference::type 脱去引用，剩下元素类型本身
 * 要使用typename告知编译器这是一个type
 * ***/
template<typename T> auto fcn(T beg,T end)-> typename remove_reference<decltype(*beg)>::type{
    return *beg;
} 

template <typename T> int compare(const T&,const T&);

int (*pf)(const int &,const int&) = compare;

void func(int(*)(const string&,const string&));

template<typename T>
void f3(T&& val){
    T t = val;
}

struct My_error:runtime_error{
    My_error(const string&);
};


int main(){
   // func(compare<string>);
    int &&rr1 = 42;
    int &&rr4 = std::move(rr1);
    cout  << rr4 << endl;
    try{
        int a = 12;
    }catch(exception e){
        cout << e.what() << endl;
    }
    return 0;
}