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

int main(){
    Person *sp = new Student("trans");
    Student *st = new Student("trans");
    cout << sp->name() << endl;
    st->countNum();
    st->doHeathValue();
    st->name();
    return 0;
}