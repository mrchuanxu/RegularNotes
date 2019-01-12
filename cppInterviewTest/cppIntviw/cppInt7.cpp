#include <iostream>

using namespace std;

template<class T>
void swap(T& a,T& b){
    T tmp(move(a)); // a中移出值
    a = move(b); // b中移出值
    b = move(tmp); // tmp中移出值
}

int main(){
    // int *ptr;
    // int val = 42;
    // void *pi;
    // void *pi1;
    // ptr = &val; // 将val地址的值赋值给ptr
    // pi = ptr; // 这里发生了隐式转换
    // int *piv = static_cast<int*>(pi);
    // cout << *piv << endl;
    int *ptr;
    char carr[] = {'a','b','c'};
    // carr = static_cast<char[]>(ptr);
    int i = 23;
    int &r = i;
    ++r;
    cout << i << endl;
    int u = 34;
    const double& cdr(1);
    int *const p = &i;
    r = u;
    cout << r << endl;
    cout << i << endl;
    return 0;
}