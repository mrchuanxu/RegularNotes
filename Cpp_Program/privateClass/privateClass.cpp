#include <iostream>

using namespace std;

class Person{
    public:
        Person(){
            cout << "Person" << endl;
        };
        virtual void run() = 0;
        ~Person(){
            cout << "~person" <<endl;
        }
};

class Student:private Person{
    public:
        Student() = default;
        virtual void run() override{
            cout << "run to the sky" << endl;
        }
};

int main(){
    Student stu;
    stu.run();
    return 0;
}