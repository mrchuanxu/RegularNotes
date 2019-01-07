
#include <iostream>

using namespace std;

/***
 * 所以右值引用是独立于左值和右值
 * 以下是一个好例子
 * 放入一个左值，那么T&& t 就是一个左值
 * 放入一个右值，那么T&& t 就是一个右值
 * 这里发生了自动类型推断
 * 是发生在函数中的
 * 类型中
 * 并没有类型的自动推断
 * 所以当我们使用移动构造函数的时候，需要使用的移动运算符std::move
 * 
 * **/
void processValue(int &a){cout <<"lvalue"<<endl;}
void processValue(int &&a){cout << "rvalue"<<endl;}
template<typename T> void func(T&& val){
    processValue(std::forward(val)); // FIXME:
}
int && i = 0;

class Test{
    public:
    Test():m_ptr(new int[0]){
        cout << "construct" << endl;

    }
    Test(const Test& test):m_ptr(new int(*test.m_ptr)){
        cout << "deep copy" <<endl;
    }
    Test(Test&& test):m_ptr(test.m_ptr){ // 这里就一定是右值引用了
        cout << "right move reference" << endl;
       // delete test.m_ptr; ❌ 这里不允许删除一个右值
        test.m_ptr = nullptr;
    }
    ~Test(){
        delete m_ptr;
        cout << "delete"<<endl;
    }
    Test& operator=(const Test& test){ // 其实这里使用了深拷贝
        if(this==&test)
            return *this;
        delete m_ptr;
        Test *temptest;
        temptest->m_ptr = test.m_ptr;
        m_ptr = temptest->m_ptr; 
        delete test.m_ptr;
        cout << "assign to other" <<endl;
        return *this;
    }
    Test& operator=(Test&& test){
        cout << "move function"<< endl;
        if(this==&test)
            return *this;
        //delete m_ptr;
        m_ptr = test.m_ptr;
        test.m_ptr = nullptr;
        return *this;
    }
    private:
    int *m_ptr;
};
Test getA(){
   Test test;
   return test; // 这是一个临时量
}
int main(){
    // cout << i << endl;
    // int inum = 100;
    // const int&& inumref = 100;
    // func(inumref);
    Test test;
    Test movTest = std::move(getA()); // 调用移动构造函数 所以这里不需要再构造一次，直接用移动构造
    // test = movTest;
    test = std::move(getA()); // 这里
    int i = 10;
    func(i);
    func(0);
    return 0;
}