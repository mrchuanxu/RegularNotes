#include <memory>
#include <iostream>

using namespace std;

class Widget{
    public:
    void print(){
        cout << "Widget" << endl;
    }
};

template <class T> class SmartPtr{
    public:
        template<typename U> SmartPtr(const SmartPtr<U>& other):heldPtr(other.get()){}
        T* get() const { return heldPtr;}
    private:
        T* heldPtr;
};

struct ArrNode{
    int val;
    ArrNode *next;
};


/***
 * 模版元编程
 * 在编译期间，完成代码执行
 * ***/
template<unsigned n> struct Factorial{
    enum{value = n*Factorial<n-1>::value};
};
// 特殊情况
template<> struct Factorial<0>{
    enum{value = 1};
};
// operator new 是自己写一个new和一个delete也可以写
class Midget{
    public:
        static new_handler set_new_handler(new_handler p) throw();
        static void* operator new(size_t size) throw(bad_alloc);
        static void* operator delete(size_t size) throw(bad_alloc);
    private:
        static new_handler currentHandler;
};

void* Midget::operator new(size_t size) throw(bad_alloc){
       ::operator new(size);
       return;
}
new_handler Midget::currentHandler = 0;

int main(){
//     shared_ptr<string> sptr = make_shared<string>("hello");
//     //*sptr = "hello,world!";
//     cout << *sptr << endl;

//     shared_ptr<Widget> wptr;
//     wptr->print();

//    //  SmartPtr<Widget> smaPtr(Widget);
//     int *arr[10];
//     int iNum = 10;
//     arr[1] = &iNum;
//     cout << *arr << endl;
//     char ctr = 'a';
//     int a = ctr%15;
//     cout << a << endl;
    
//     ArrNode *arrNode[4];
//     arrNode[0]->val = 42;
//     cout << arrNode[0]->val << endl;
    enum enumType{Mon,Tue,Wed,Thur,Fri,Sat,Sun} Weekday;
    Weekday = enumType(3);
    cout << Weekday << endl;
    cout << Factorial<5>::value<<endl;
    return 0;
}