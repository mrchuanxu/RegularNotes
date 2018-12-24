/***
 * 一些难点
 * 比较烦人的点
 * 1. 虚析构函数的用法 体验一下继承 构造 ***/
#include <iostream>

using namespace std;
class Person{
    public:
        Person(){
            cout << "I am person" << endl;
        }
        virtual ~Person(){
            cout << "fuck off i am die" << endl;
        }
        virtual void read();
};

class People{
    public:
        virtual void eat() = 0;
        People(){
            cout << "I am people"<< curr<<endl;
        }
        virtual ~People(){
            cout << "fuck off i am die again"<<endl;
        }
    private:
        static int curr;
};
int People::curr = 42;
class Student:public People,protected Person{
    public:
    void eat(){
          cout << "eat by some one" << endl;
      }
      Student(){
          cout << "fuck student" << endl;
      }
      ~Student(){
          cout << "shift" << endl;
      }
    protected:
      void read(){
            cout << "already read" << endl;
        }
};

int main(){
    People *pt = new Student;
    pt->eat();
    delete pt;
    return 0;
}