#include <string>
#include <memory>
#include <string>
#include <iostream>
using namespace std;
class PersonImpl;
// class Date;
// class Address;
/***
 * 相依于声明式，不相依于定义式
 * 使用智能指针 shared_ptr<>pp()
 * derived class 与 abstract class
 * 继承关系，实现细目
 * ***/

class Person{ // 这个是接口类
    public:
        Person(const string& name);
        string name() const;
        string birthDate() const;
        string address() const;
    private:
        shared_ptr<PersonImpl> pImpl; //这里面是实现的类
        virtual int doHeathValue() const{
            int value = 100;
            return value;
        }
};

class Student:public Person{ // is-a 学生是人，人不一定是学生
    public:
        Student(const string& name):Person(name){

        };
        virtual int doHeathValue() const{
            int value = 90;
            return value;
        }
        int countNum(){
            int count = 0;
            return count;
        }

    
};
// 函数指针的应用
class GameCharacter;
int defaultHeathCalc(const GameCharacter& gc);
class GameCharacter{
    public:
        typedef int (*HeathCalcFunc)(const GameCharacter&); // 一个函数指针，指向参数值是const GameCharacter&，返回值类型是int的函数
        explicit GameCharacter(HeathCalcFunc hcf = defaultHeathCalc):healthFunc(hcf){} // healthFunc指向一个defaultHeathCalc的函数
        int healthValue() const{
            return healthFunc(*this);
        }
    private:
        HeathCalcFunc healthFunc; // healthFunc是一个函数指针
};

class EvilBadGuy:public GameCharacter{
    public:
        explicit EvilBadGuy(HeathCalcFunc hcf = defaultHeathCalc):GameCharacter(hcf){}
};

class Shape{
    public:
        enum ShapeColor{red,Green,Blue};
        virtual void draw(ShapeColor color = red) const = 0;
};

class Rectangle:public Shape{
    public:
        virtual void draw(ShapeColor color = Green) const{
            cout << "rect" << endl;
        }
};

class Circle:public Shape{
    public:
        virtual void draw(ShapeColor color) const{
            cout << "circle" << endl;
        }
};

class Square:virtual public Shape{ // 一般很少使用virtual继承

};
class CompanyZ{
    public:
        void sendEncrypted(const string& msg);

};

class MsgInfo;

template<typename company> class MsgSender{
    public:
        void sendSecret(const MsgInfo& info);
};
template<> class MsgSender<CompanyZ>{
    public:
        void sendSecret(const MsgInfo& info){

        }
        void sendClear(const MsgInfo& info){

        }
};

template<typename company> class logMsgSender:public MsgSender<company>{
    public:
        using MsgSender<company>::sendClear;
        void sendClearMsg(const MsgInfo& info){
            sendClear(info);
        }
};

template<typename T> class SquareMatrixBase{
    protected:
        SquareMatrixBase(size_t n,T* pMem):size(n),pData(pMem){}
        void setDataPtr(T* ptr){pData = ptr;}
    private:
        size_t size;
        T* pData;
};
template<typename T,size_t n>class SquareMatrix:private SquareMatrixBase<T>{
    public:
       SquareMatrix():SquareMatrixBase<T>(n,data){}
    private:
        T data[n*n];
};


class Top{
    public:
    void tprint(){
        cout << "Top" << endl;
    }
};
class Middle:public Top{
    public:
    void print(){
        cout << "middle" << endl;
    }
};

template<typename T> class SmartPtr{
    public:
        template<typename U> SmartPtr(const SmartPtr<U>& other):heldPtr(other.get()){}
        T* get() const{ return heldPtr;}
    private:
        T* heldPtr;
};


template <typename T> class Handler{
    public:
    T val;
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

int main(){
    // 模版元编程的使用
    cout << Factorial<8>::value;
    
    SmartPtr<Top> ptr1(Middle);
    // Person *sp = new Student("trans");
    // Student *st = new Student("trans");
    // cout << sp->name() << endl;
    // st->countNum();
    // st->doHeathValue();
    // st->name();
    Shape *ps;
    Shape *pc = new Circle;
    Shape *pr = new Rectangle;
    pc->draw(Shape::red);
    pr->draw(Shape::red);

    Handler<char> 
    return 0;
}