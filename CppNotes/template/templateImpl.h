#ifndef TEMPLATEIMPL_H
#define TEMPLATEIMPL_H
#include <iostream>
#include <memory>

using namespace std;

/***
 * 这里的typename F = less<T> 是为模版添加了第二个类型参数，名为F 表示可调用对象
 * 并且定义了一个新的函数参数f
 * 所以说为了这个模版参数提供了默认实参
 * 当用户调用这个版本的compare 
 * 第三个参数可以是用户自定的比较参数，但是这只是一个默认实参，类型要一致
 * ***/
template <typename T,typename F = less<T>> int compare(const T &v1,const T& v2,F f = F()){
    if(f(v1,v2)) return -1;
    if(f(v2,v1)) return 1;
    return 0;
}

/***
 * 类也可以指定默认实参
 * ***/
template <class T = int> class Numbers{
    public:
        Numbers(T v=0):val(v){}
    private:
        T val;
};
/***
 * 成员模版
 * ***/
class DebugDelete{
    public:
        DebugDelete(ostream& s = cerr):os(s){}
        template<typename T> void operator()(T *p) const{
            os<<"deleting unique_ptr"<<endl;
            delete p;
        }
    private:
        ostream &os;
};
#endif

/***
 * unique_ptr的使用
 * ***/
// int main(){
//     Numbers<> arvage_pre; // 空的<>表示我们使用默认实参
//     cout << compare(13,42) <<endl;
//     double *p = new double;
//     DebugDelete d;
//     d(p); // 调用operator()(double*)
//     int *ip = new int;
//     DebugDelete()(ip);
//     unique_ptr<string,DebugDelete> sp(new string,DebugDelete());
//     return 0;
// }

