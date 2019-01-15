#include <memory>
#include <iostream>
#include <initializer_list>
#include <exception>

using namespace std;

// 用于内置函数
unique_ptr<int[]> make_sequence(int n){
    unique_ptr<int[]> p{new int[n]};
    for(int i = 0;i<n;++i)
        p[i] = i;
    return p; // 返回局部对象
}
// 不能拷贝的一个例外
unique_ptr<int> clone(int p){
    return unique_ptr<int>(new int(p)); // 返回一个unique_ptr 将要被销毁的unique_ptr
}

// 列表参数
template <class T>
void f1(initializer_list<T>);

void err_msg(initializer_list<string> il){ // 这是形参列表
    for(auto beg = il.begin();beg!=il.end();++beg){
        cout << *beg << " ";
        cout << endl;
    }
}
// 同时拥有其他形参
void error_msg(int e,initializer_list<string> il){
    cout << e << endl;
    for(const auto &elem:il){
        cout << elem << " ";
    }
    cout << endl;
}
// ...省略符形参 只能出现在形参列表最后的一个位置 printf就是使用省略符号参数的典型例子。
// printf("%d%s%f",int,char*,float);


int main(){
    err_msg({"hahah","str","hhh"});
    // unique_ptr<int []> ptr(make_sequence(9).release());
    // cout << ptr[2] << endl;
    // // cout << *(ptr[3]) << endl;
    // // 先看一下简单的unique_ptr操作
    // // 初始化unique_ptr必须采用直接初始化形式。
    // // 先用一下内置类型
    // unique_ptr<double> p1(new double(12.3));
    // unique_ptr<double> p2(p1.release());
    // if(p2 == p1)
    //     cout << "true" << endl;
    // cout << *p2 << endl; // 所以其实读取都是一样的指针操作。
    // p1.reset(p2.release());
    // cout << *p1 << endl;
    // unique_ptr<int> pc(clone(9));
    // cout << *pc << endl; // 可以这样使用。
    return 0;
}