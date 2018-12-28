/***
 * 复合类型与const形参与实参
 * 两部分可结合做笔记
 * ***/
#include <iostream>
#include <string>
#include <initializer_list>
using namespace std;
/***
 * 复合类型
 * 引用与指针
 * 引用必须是一个对象
 * 引用初始化类型要一致
 * 
 * 指针
 * void* 不能直接操作
 * 指针本身就是一个对象，又可以指向另外一个对象
 * 所以指针是不是常量以及指针所指的对象是不是一个常量是两个独立的问题
 * 顶层 指针本身是一个常量
 * 底层 指针所指的对象是一个常量
 * 再升级一下，顶层，对象本身就是一个常量 底层 对象所指向或者所对的就是一个常量
 * const限定符
 * const 的引用 对常量的引用
 * 
 * constexpr常量表达式 指不会改变并且在编译过程就能得到计算结果的表达式
 * 
 * const的形参与实参 const int &i;
 * 
 * 可变形参
 * initializer_list<T> lst;
 * lst.size() lst.begin() lst.end();
 * 
 * ... 省略符形参
 * 
 * ***/
int get_size(){
    return 13;
}

void fcn(const int i){
    cout << i << endl;
}

void error_msg(initializer_list<string> il){
     for(auto beg = il.begin();beg != il.end();++beg){
         cout << *beg << endl;
     }
}
int reviewA(){
    int ival = 1024;
    int &refVal = ival;
    int ival2;
    int &refVal2 = ival2;
    cout << refVal2 << endl;
    void *p = &ival;
    ival = 4;
    cout << refVal << endl;
    const int i = get_size();
    cout << i << endl;
    const int j = i;
    const int cival = 42;
    ival = cival;
    const int &r1 = j;
    const int *const p1 = &ival;
    cout << *p1 << endl;
    const int *p3 = &ival;
    cout << *p3 << endl;

    const int max_files = 24;
    const int limits = max_files+1;

    constexpr int sz = limits+1; 
    cout << sz << endl;
    constexpr int q = 20;
    cout << q << endl;
    int *const cp = &ival;
    fcn(13);
    //cout << argv[1] << endl;
    error_msg({"functionX","expected","actual"});
}

/***
 * try-catch
 * 
 * 尾置返回类型
 * 
 * ***/

auto func(int i) -> int(*)[10]{
    int array[10]{1,2,3,4,5,56,6,7,8};
    int (*arr)[10] = &array;
    #ifndef NDBUG
    cout << __func__<<endl;
    #endif
    return arr;
} // 返回一个指针，该指针指向含有10个整数的数组

constexpr int new_sz() {
    return 42;
}
int main(int argc,char *argv[]){
    // if(true){
    //     throw runtime_error("no it is true");
    // }
    try{
        char ch;
        cin >> ch;
        cout << ch << endl;
        int (*arr)[10] = func(10);
        cout << *arr[2] << endl;
        constexpr int foo = new_sz();
    }catch(runtime_error e){
        cout << e.what() << endl;
        throw runtime_error("no it is not type");
    }
    return 0;
}