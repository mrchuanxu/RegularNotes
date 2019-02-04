## 什么是多态，多态有什么用途。(虚函数)
先从哪里说起呢，先说一下virtual这个关键字，然后重载，然后类继承，private继承，派生类，讨论类层次，讨论虚函数表，讨论虚函数在继承中的实现，讨论虚函数的准则，讨论虚函数重载的过程，讨论底层实现，顺便了解一下inline内联函数，以上都是要讲的内容，慢慢讲。<br>
首先我先不回答这个问题，什么是多态，我们先来看看什么是函数重载。
### 函数重载 (一个简单的多态)
```cpp
#include <iostream>
using namespace std;
int func(int a,int b){
    return a+b;
}
void func(char a){
    cout << a << endl;
}
double func(double a,int b){
    return a+b;
}
int main(){
    int a = func(1,2);
    double d = func(1.22,3);
    func('a');
    cout << a << ',' << d << endl;
    return 0;
}
```
编译器会根据上下文语义来决定最适合的func执行。而我们使用同样的函数表现出不同的结果，这也叫做一个函数多种不同的形态，这也正好印证了函数指针的使用，一个函数体生成的代码，置于某块内存区域中，有自己的地址。函数指针的详细可以在上一节可调用对象查看，这里我就不再赘述<br>
那么这跟cpp的多态有什么关系呢？且等我娓娓道来，我们首先构建一个类，一个类首先我们必须知道编译器为他默默生成的四个函数(拷贝构造，构造，拷贝赋值运算符以及析构函数)。那么一个类如何呈现多态呢？我们先来看看定义， **多态，是指”一种接口，多种方法“，而这些方法是在运行时确定的“**。咋一看概念好像很好懂，但是要是想彻底了解，也需要从最基本的说起。首先它是有多种方法，一种接口，这会让我们联想到派生类，一个基类，多种派生类的出现
### 派生类 (表达类层次关系)
派生类通过继承关系而来，先来看看继承又是什么关系，先来看看两个大的继承关系，实现继承与接口继承
* 实现继承：通过共享基类所提供的特性来减少实现工作量<br>

```cpp
// 一个书上的🌰，比较复杂，但是为了后面讲述类层次，先拿来用
#include <iostream>
using namespace std;
class lval_box{
    protected:
        int val;
        int low,high;
        bool changed = false;
    public:
    lval_box(int ll,int hh):val(ll),low(ll),high(hh){}
    virtual int get_value(){ changed = false;return val;}
    virtual void set_value(int i){changed = true;val = i;}
    virtual void reset_value(int i){changed = false;val = i;}
    virtual void prompt(){}
    virtual bool was_changed()const { return changed;}
    virtual ~lval_box(){};
};
```
这就是基类实现了大部分的特性，如果要继承，就可以直接使用基类函数。<br>
* 接口继承：通过一个公共基类提供的接口允许不同派生类互换使用。(常被称为运行时多态，动态多态)<br>

```cpp
#include <iostream>
using namespace std;
class lval_box{
    public:
    virtual int get_value()=0;
    virtual void set_value(int i)=0;
    virtual void reset_value(int i)=0;
    virtual void prompt()=0;
    virtual bool was_changed()=0;
    virtual ~lval_box(){};
};
```
这就是一个接口继承的公共基类，没有实现任何函数，只是提供了一个简单的纯虚函数的接口。这就方便后面的派生类实现多态了<br>
接口继承常被称为运行时多态或者动态多态，模版就反了，模版所提供的类的通用性与继承无关，常被称为编译时多态或静态多态。(模版多态，会在模版那一章节继续讲)。<br>
继承扯远了，先回来看看派生类
#### 最简单的派生
```cpp
struct Employee{
    string first_name,family_name;
    char middle_initial;
    string hiring_date;
    short department;
};

struct Manager:public Employee{
    list<Employee*> group;
    short level;
    //...
};
```
这就是继承关系，manager也是一个employee，继承employee的属性，并且可以将自己放入列表中。public继承就是is-a属性。这个public是一个访问说明符，待会也会细细与private，protected一起讲。<br>
对于这个is-a属性，可以由下面的🌰可以得知
```cpp
Employee *eman = new Manager();
eman->first_name = "mrtrans";
```
可以将派生类赋予基类，但是不能将基类赋予派生类，也就是说，父类可以出现的地方，子类也可以出现，但是子类出现的地方，父类不能出现。也就是说，子类是父类类型，但是父类类型不是子类。<br>
可是如果我硬是要转换呢？也可以用static_cast暴力转换，来看看这个暴力转换
```cpp
void g(){
    Employee *pe = new Employee();
    Manager *pm = static_cast<Manager*>(pe);
    pm->level = 12;
    cout << pm->level << endl;
    delete pe;
}
```
这样就暴力解决了，也是很暴力，硬生生把pe改成了manager类型。<br>
其实，当我们这样将子类赋予给父类类型的时候，发现出现了切片的现象，什么是切片现象？
##### 切片现象
切片，一个指向派生类的指针可以隐式转换为指向其公有基类的指针。这样，指针原本的指向就会转向公有基类，而子类部分的成员就会被切割掉，这就是切片。<br>
#### 复杂一点的派生 (自从复杂之后，派生的人生达到了高潮)
一个简单的派生就要涉及那么多学问，那么复杂的派生还得了？没错，不得了，复杂的派生讲的点包括，成员函数，访问控制，虚函数，虚继承，虚基类，析构函数，构造函数，强制类型转换等<br>
##### 构造函数和析构函数 (先从你的诞生讲起)
* 构造，基类先于成员，成员先于派生(先有爸爸👨)，析构，派生类先于成员，成员先于基类(先打儿子，先欺负小的👦)
* 每个类都可以初始化其成员和基类
* 类层次中的析构函数通常是virtual的。(为什么呢？)<br>
```cpp
class Shape{
    public:
        virtual void draw();
        virtual ~Shape(){
            cout << "delete shape!" << endl;
        };
};

class Circle:public Shape{
    public:
        ~Circle(){
            cout << "delete shape?" << endl;
        }
};
int main(){
    Shape *cir = new Circle();
    delete cir;
}
```
因为Shape定义了虚函数就会有被继承的效果，而继承之后就需要构造，而构造是从基类开始的，但是析构就是从派生类开始的。在上面的🌰中，如果操纵一个对象是通过基类提供的接口的话，那么就应该通过该接口来delete它。所以virtual就提供了这个接口，让派生类释放基类资源。<br>