/**
 * 看到一篇好文章
 * 关于指针与引用以及const
 * 在这里分享一下
 * 先来看一段编译没有错误的代码
 * 
 * **/

#include <iostream>
using namespace std;

int main(){
    int a = 5;
    int *const& p = &a;
    *p = 6;
    // int *&p = &a; 错误
    // int& ra = 5;

    cout << p << endl; // 输出a的内存地址
    cout << *p << endl; // 6
    cout << a << endl; // 6
    // int& ra = 5;
    return 0;
}
/**
 * 两个问题
 * 一个是 int*&p = &a是什么意思
 * 一个是 为什么要加const才是合法的书写
 * 正常定义一个指针，要么分配新内存，要么指向已有的内存，包括指向一个已有的变量的地址
 * 
 * 这里的p是一个指针的引用
 * 
 * 引用需源，有源才有引 
 * 
 * 对一个立即数取引用是不行的，5会占用内存，没办法对没有名字的东西取地址。
 * 
 * 为什么加const就可以了？
 * 
 * 续命机制，一个立即数不可更改，通过const续命 内存不让出 定义为常量
 * 
 * p不能改自己，但是可以改指向的内容
 * 
 * 原文引用:https://www.zhihu.com/question/314024679/answer/612647084?utm_source=wechat_session&utm_medium=social&utm_oi=950291780785123328
 * **/