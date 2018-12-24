#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include <utility>
#include <random>
#include <array>
#include <string>

using namespace std;
using namespace std::chrono;
/***
 * tcpl
 * 1. constexpr 在编译时求值
 * 2. const 我承诺不改变这个值
 * 3. 一个引用在初始化之后就不能再引用其他对象了
 * 4. 使用命名空间namespace
 * 5. 处理异常，throw out_of_range();
 * 6. 静态断言 static_assert 很多用途
 * 7. 函数返回一个指向自由存储上的对象的指针是非常危险的，一种解决方案是使用unique_ptr
 * 8. 资源的拷贝不是默认逐成员复制，而是通过拷贝构造函数和copy assignment完成，要先分配空间，在进行拷贝
 * 9. 移动容器，移动构造和移动赋值可以减少资源损耗 标准库函数move()复制返回实参的右值引用 
 * 10. lambda表达式提供简单便捷的操作，但是更晦涩难懂
 * 11. 可变参数 会先处理第一个，然后继续处理下一个的第一个，不停滴递归调用
 * 12. ostream_iterator流输出，输入，一个输入流可以产生一个值的序列
 * 13. 优先考虑使用标准库算法，容器，谓词使用等
 * 14. 根据迭代器类型itertor_traits可以选择不同的类型，调用不同的模版 技术叫标签分发
 * 15. 学会使用pair<int,int>和元组tuple<string,int,double>  make_pair  make_tuple
 * 16. 学会考虑struct 成员在底层按声明顺序依次存放，所以存在对齐问题
 * 17. union是一种特殊的struct，它的所有成员都分配在同一个地址空间上。因此，一个union实际占用的空间大小与其最大的成员一样。
 * 18. 学会使用移动操作，提高性能&& 使用std::move(a)
 * ***/
//14 
template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // iter 类别

constexpr double square(double x){return x*x;}


namespace My_code{
    int main();
}
class Vector{
    public:
        Vector(int s):elem(new double[s]),sz(s){}
        double& operator[](int i){
            if(i<0||size()<=i) throw out_of_range("Out of range"); 
            return elem[i];
            }
        int size(){return sz;}
        Vector(Vector&& a);
        Vector& operator=(Vector&& a);
    private:
        double *elem;
        int sz;
};
Vector::Vector(Vector &&a):elem(a.elem),sz(a.sz){
    a.elem = nullptr; //从a中夺取元素，并且置空
    a.sz = 0;
}
int My_code::main(){
    cout << "to the sky" << endl;
    return 0;
}

unique_ptr<Vector> readVector(istream &s){
    return unique_ptr<Vector> (new Vector(10));
};

mutex m;
static int sh = 1;
void func(){
    unique_lock<mutex> lck(m);
    sh+=7;
};

void func_thread(){
    cout<<"func_Thread" << endl;
    return;
}
void func_thread2(){
    cout << "func_Thread2" << endl;
    return;
}
struct Func_Thread{
    void operator()();
};
void user(){
    thread t1(func_thread);
    thread t2(func_thread2);
    t1.join();
    t2.join();
}

enum enumType{str,num};
union Value{char* s;int i;};
struct Entry{
    char *name;
    enumType t;
    Value v;
};

// double accum(double* beg,double *end,double init){
//     return accumulate(beg,end,init);
// }
// // async
// double comp(vector<double>&v){
//     if(v.size()<10000) return 
// }
//extern int xbase;
// 18
template<class T>
class Martix{
    std::array<int,2> dim;
    T *elem;
    public:
    //Martix(int d1,int d2):dim(d1,d2),elem(new T[d1*d2]){}
    int size() const {return dim[0]*dim[1];}

    Martix(const Martix&);
    Martix(Martix&&); // 移动构造函数
    
    Martix& operator=(const Martix&);
    Martix& operator=(Martix&&); // 移动赋值运算符

};

int main(){
    //cout << xbase << endl;
    static_assert(4<=sizeof(int),"integers are too small"); // 不满足，就会在编译期间报错！
    double sqCal = square(2.5);
    cout << sqCal << endl;
    int v1[] = {0,1,2,23,4,4,4};
    for(auto &x:v1){ 
        cout << x << endl;
    }
    // [&](int a){return a<10;};
    ostream_iterator<string> oo(cout);
    // istream_iterator<string> ii(cin);
    user();
    *oo = "hello trans";
    Vector vec_test(10);
    // cout << vec_test[11] << endl;
    auto t0 = high_resolution_clock::now();
    user();
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(t1-t0).count()<<"mssec"<<endl;
    tuple<string,int,double> tup("hi",12,123.3);
    string s = get<0>(tup);
    cout << s << endl;
    cout << __STDCPP_THREADS__ << endl;
    // Vector *p;
    // auto *dycast = dynamic_cast<Vector*>(p);
    //cout << dycast->size() << endl;
    int inum = 10;
    int *p = &inum;
    cout << *p << endl;
    int numi = 42;
    p = &numi;
    cout << *p << endl;
    cout << inum << endl;
    return My_code::main();
}