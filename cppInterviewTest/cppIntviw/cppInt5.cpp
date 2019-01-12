#include <iostream>
#include <string>

extern "C" size_t strlen(const char *);
using namespace std;

// void * 指向其他任意类型
void f(int *pi){
    void *pv = pi; // 发生了int* 到void*的隐式类型转换
    // *pv; // ❌不允许解引用void*
    // ++pv; ❌ 不允许对void*执行递增操作
    // 必须进行显式转换int* 才能操作
    int *pi2 = static_cast<int*>(pv); // static_cast类型转换要着重讲一下 强制类型转换
    // double *pd1 = pv; //  ❌ 
    double *pd3 = static_cast<double*>(pv); // 这是一种不安全的行为
    // 如果某个指针已经被转换成（强制类型转换）指向一种与实际所指对象类型完全不同的新类型，则使用转换后的指针是不安全的行为。
    // 例如，某个机器假定double沿着8字节边界分配内存，如果指向int的pi分配内存的方式与之不同，将造成意想不到的后果
}

// 函数指针
void errorf(string s){
    cout << s << endl;
}
// 函数成员指针
class Std_interface{
    public:
        virtual void start() = 0;
        virtual void suspend() = 0;
        virtual void resume() = 0;
        virtual ~Std_interface(){};
};

class Text:public Std_interface{
    public:
        virtual void print();
};

// void (Std_interface::*pmi)() = &Text::print;// ❌  c
void (Text::*print)() = &Std_interface::start; // ✅
// 所以说，基类成员指针可以赋给一个派生类成员指针，其实这也说明，父类在的地方，子类可以适应，子类在的地方，父类不会适应
// using pStd_mem = void (Std_interface::*)(); // 成员指针类型

// void fstd(Std_interface* p){
//     pStd_mem s = &Std_interface::suspend; // 指向suspend()的指针 就是s特定指向suspend这个函数
//     p->suspend(); // 直接调用
//     p->*s(); // 通过成员指针调用
// }
struct C{
    const char *val;
    int i;
    void print(int x){cout << x << "\n";}
    int f1(int);
    void f2();
    C(const char *v){val = v;}
};

using Pmfi = void (C::*)(int); // c的成员函数指针，接收int
using Pm = const char * C::*; // c的char数据成员的指针
void funcv(C &z1,C &z2){
    C *p = &z2;
    Pmfi pf = &C::print;
    Pm pm = &C::val; //  数据成员指针，指向val
    z1.print(3);
    (p->*pf)(4); // 将pf绑定到p所指向的对象
    (z1.*pf)(42); // pf绑定到对象z1上
}
void (*efct)(string s);
int main(){
    // efct = &errorf; // 该函数指针 指向函数
    // // efct("runtime_error");
    // efct("hello");
    // char arr[2] = {'1','2'};
    // char *p = arr; // int[] 到int*的隐式转换
    // char *pe = arr+2;
    // cout << strlen(p) << endl;
    // cout << strlen(arr) << endl;
    C z1("rr"),z2("ss");
    funcv(z1,z2);

    return 0;
}