/***
 * 对于异常
 * 要知道三点
 * 1. 当抛出异常时发生了什么
 * 2. 捕获异常时发生了什么
 * 3. 用来传递错误的对象的意义是什么
 * throw之后的语句不会被执行，一旦程序开始执行异常处理代码，则沿着调用链创建的对象将被销毁
 * namespace
 * union 任意时刻只有一个值
 * ***/
#include <exception>
#include <stdexcept>
#include <utility>
#include <memory>
#include <iostream>
#include <typeinfo>
using namespace std;

// template<typename T> Blob<T>::Blob(initializer_list<T> il)try:data(make_shared<vector<T>>(il)){

// }catch(const bad_alloc &e){
//     handle_out_of_memory(e);
// }

namespace A{
    int i,j;
    namespace B{
        int i;
        int j;
    }
}


int main(){
    // range_error r("error");
    // throw r;
    // exception *p = &r;
    // throw p;
    int *a = new int[10];
    cout << typeid(a).name()<<endl;
    using namespace A;
    cout << i*j << endl;
    union{
        char cval;
        int val;
        double dval;
    };
    cval = 'a';
    cout << cval << endl;
    volatile int iax[100];
    return 0;
}