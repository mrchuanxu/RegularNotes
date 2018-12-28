#include <iostream>
#include <utility>
#include <exception>
using namespace std;

/***
 * friend
 * static 静态成员独立于任何对象
 * 拷贝初始化
 * 1.将一个对象作为对象传递一个非引用类型的形参
 * 2. 从一个返回类型为非引用类型的函数返回一个对象
 * 3. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
 * std::move
 * 
 * ***/
class Student;
class Person{
    friend void dance(Student&,Person&);
    friend istream &read(const istream&);
    friend ostream &write(ostream&);
    friend class Student;
    public:
        Person() = default;
        Person(const Person&);
        void eat(){
            cout << "yes i can eat" << endl;
        }
        Person& operator=(const Person&);
        static double rate(){ return period+interRate;}
        int tons_sz(){
            return tons;
        }
        // 定义一个移动构造函数 体会右值使用
        Person(Person &&) noexcept;
    private:
        int tons = 1000;
        static double interRate; 
        static constexpr int period = 30;
};
double Person::interRate = .9;

Person::Person(const Person &percopy):tons(0){
}
Person& Person::operator=(const Person &perassign){
    tons = perassign.tons;
    return *this;
}

Person::Person(Person &&permov)noexcept:tons(permov.tons){
    permov.tons = 0;
}


class Student{
    public:
    Student() = default;
    void readbook(Person &per){
        cout << per.tons << endl;
    }
};

void dance(Student &stu,Person &per){
    cout << per.tons <<endl;   // 可以访问private元素

}

/***
 * 强制左侧运算对象是一个左值
 * ***/
class Foo{
    public:
        Foo sorted() &&;
        Foo sorted() const &;
        Foo &operator=(const Foo&) &; // 只能向可以修改的左值赋值
};
Foo &Foo::operator=(const Foo &rhs) &{
    return *this;
}
Foo Foo::sorted() const &{
    //Foo ret(*this);
    //return ret.sorted(); // 递归最后溢出 这里调用的是sorted() const & 不停地调用
    // 改成 Foo(*this).sorted(); 就会调用移动版本 没问题
    return Foo(*this).sorted();
}

/***
 * 了解一下move的骚操作
 * remove_reference 去掉引用 &&去 &去
 * static_cast 进行显式转换
 * 
 * ***/
template<typename T> typename remove_reference<T>::type&& move(T&& t){
    return static_cast<typename remove_reference<T>::type&&>(t);
}


int main(){
    Student stu;
    Person per;
    dance(stu,per);
    stu.readbook(per);
    double r = Person::rate();
    cout << r << endl;

    Person per1 = move(per);
    cout << per1.tons_sz()<<endl;
    cout << per.tons_sz() <<endl;
    return 0;
}