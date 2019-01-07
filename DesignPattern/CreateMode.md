首先来看看这5个模式
# 创建类型模式 单例、原型、工厂方法、抽象工厂、建造模式
## 单例模式（我就是我，不一样的烟火）
cpp effective 55 说过，如果你不想让别人可以构造你，你就把你的构造函数声明为private吧。<br>
```cpp
class Brother{
    private:
        Brother(){
            cout << "only me is you brother" << endl;
        };
};
```
确保某个类只有一个实例，而且自行实例化并向整个系统提供这个实例。<br>
优点：<br>
* 只有一个实例，一个对象需要频繁地创建，销毁，而且创建或销毁时性能无法优化，就需要一个实例，删除，销毁，也只有一个实例。
* 单例模式只生成一个实例，所以较少了系统的性能开销，当一个对象的产生需要比较多的资源时，如读取配置，产生其他依赖对象，就可以在应用启动的时候，直接产生一个单例对象。然后永久驻留内存。<br>
* 避免资源多重占用，由于只有一个实例存在内存中，避免对同一个资源文件的同时写操作。
* 单例模式可以在系统设置全局的访问点，优化和共享资源访问。<br>
缺点：<br>
* 没有接口
* 测试不利
* 与单一职责原则有冲突
所以要结合场景需求，一般与原则不符，就需要多多考虑。<br>
**场景：**<br>
要求一个类有且仅有一个对象。
而且在高并发的状态，需要判断这个单例是否存在！<br>
多个实例会很麻烦！<br>
**扩展一下:**<br>
设定上限产生对象。
```cpp
class Brother{
    private:
        Brother(){
            cout << "only me is you brother" << endl;
        };
        list<Brother> listBrother;
        for(){
            listBrother.add()...
        }
};
```
所以上面又叫做有上限的多例模式。<br>
## 原型模式 clone
用原型实例指定创建对象的种类，并且通过拷贝这些原型创建❤️新对象。<br>
其实就是拷贝一个对象，不用新创建它，直接拷贝它，然后你后面的资源就没了<br>
参见cpp的右值引用
```cpp
#include <iostream>
using namespace std;
void processValue(int &a){cout <<"lvalue"<<endl;}
void processValue(int &&a){cout << "rvalue"<<endl;}
template<typename T> void func(T&& val){
    processValue(std::forward(val)); // 这里是转发的设计 固定了类型，是左值就左值，是右值就是右值 forward是有条件地转为右值
}
int && i = 0; // 这种就是直接声明为右值
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
Test getA(){ // 返回的临时量就是右值
   Test test;
   return test; // 这是一个临时量
}
// 右值引用独立于左值和右值，可是右值和左值都可能是右值引用的类型，右值引用会根据左右值生成对应的左右值
```
在这里用的是移动构造函数，直接移动，不用新创建对象，而move，则是转为右值，直接无条件转为右值。调用std::move就会调用move<br>
构造函数不会被执行。这个结合起右值引用比较好。<br>
右值引用不用引起深拷贝，重新申请新的内存空间，也不会如浅拷贝一样容易造成空悬指针，只是单纯地移动会让资源使用更加合理。<br>

##工厂方法模式 我有一个工厂，模型你提供，生产让工厂来
定义一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法使一个类的实例化延迟到其子类。<br>
让方法成为一个模版，让类型，又子类提供。<br>
```cpp
class Product{
    public:
        Product()=default;
        virtual void method1();
        virtual void method2();
};
void Product::method1(){
    cout<<"Product need method1" << endl;
}
void Product::method2(){
    cout << "this is method2" << endl;
}

// 具体实现产品方法，继承
class ConcreteProductA:public Product{
    public:
        ConcreteProductA()=default;
        virtual void method1(){
            cout << "concreteProductA method1" << endl;
        }
        virtual void method2(){
            cout << "concreteProductA method2" << endl;
        }
};

// 具体实现产品方法，继承
class ConcreteProductB:public Product{
    public:
        ConcreteProductB() = default;
        virtual void method1(){
            cout << "concreteProductB method1" << endl;
        }
        virtual void method2(){
            cout << "concreteProductB method2" << endl;
        }

};

// 抽象一个工厂 抽象工厂类 里面的T都是要被抽象出来的
class Creator{
    public:
    Creator() = default;
    template <typename T> T* createProduct(){
        return new T();
    }
};

// 具体工厂 具体生产的工厂
class ConcreteCreator:public Creator{
    public:
        ConcreteCreator()=default;
        template<typename T> T* createProduct(){
            return new T();
        }
};

int main(){
    Creator *create = new ConcreteCreator();
    Product *product = create->createProduct<ConcreteProductB>(); // 这里就是构建产品的子类
    product->method1(); // 生成b产品
    return 0;
}
```
良好的封装性，代码的结构清晰。降低模块间的耦合。<br>
屏蔽了产品类，产品怎么样变化，调用者根本不用担心，直接生产就好。<br>
符合迪米特，依赖倒置，里氏替换原则。哇啦古🉐️<br>
**扩展:**<br>
1. 缩小为简单工厂模式<br>
一个模块仅需要一个工厂类，就搞一个工厂。觉得加一个静态方法并没有很多改变这个工厂类，只不过让类的继承关系会更少。<br>
2. 升级为多个工厂类<br>
复杂的项目，遇到初始化一个对象很耗费精力的情况，所有的产品类都放在一个工厂方法中进行初始化会使代码结构不清晰。<br>
所以为了结构清晰，需要为每个产品定义一个创造者。让调用者去选择与哪个工厂方法关联<br>
就是让多个不同的工厂共同继承抽象工厂
```cpp
Human whiteHuman = (new WhiteHumanFactory()).createHuman(); //  create -> return WhiteHuman() 这样调用就清晰很多了
```
3. 替代单例模式<br>
通过工厂方法模式也可以只在内存中生产一个对象。<br>
觉得这里很难用cpp实现，有点嗯...鸡肋<br>
4. 延迟初始化<br>
延迟初始化，就是一个对象被消费完毕之后，并不立刻释放，工厂类保持其初始状态，等待再次被使用。<br>
设置一个map，里面存储所有的初始化对象。没有就重新初始化，有就拿出来使用。每次调用都查询一下map。这个可以设置上限。最大的加载量，释放内存的使用空间。<br>
其实这里让我想起了原型模式，减少创建的次数。工厂模式可以这样加载也是很可以的。<br>

## 抽象工厂模式 让一切都变得很毕加索
```cpp
class Human{};
class AbstractWHuman:public Human{};
class AbstractHHuman:public Human{};
class AbstractBHuman:public Human{};
class AbstractBFHuman:public AbstractBHuman{};
class AbstractHFHuman:public AbstractHHuman{};
class HumanFactory{};
class FemaleFactory:public HumanFactory{};
HumanFactory *male = new MaleFactory();
HumanFactory *female = new FemaleFactory();
Human maleYellowHuman = male->createYellowHuman(); // 这里就只是提供一个接口
```
为创建一组相关或相互依赖的对象提供一个接口，而无需指定它们的具体类。<br>
* 封装性高，高层模块关心的是接口就可以了。
* 产品族内的约束为非公开状态。
缺点: 产品族扩展困难。额，我去看看这个抽象工厂的实现模式<br>
增加一个产品就很容易，但是要改变一个产品里面的等级就要修改类。太麻烦！<br>

## 建造者模式 变化很多，但是我有建造者，告诉建造者，他知道怎么做。
将一个复杂对象的构建与它表示分离，使得同样的构建过程可以创建不同的表示。<br>
要不同的类型，使用sequence保存不同的顺序，并且让导演来制造，<br>
**优点：**<br>
封装性好！建造者独立，容易扩展。便于控制细节风险<br>
**场景：**<br>
* 相同的方法不同的顺序，产生不同的事件结果。<br>
* 多个部件或零件，都可以装配到这个对象中。<br>
* 产品类比较复杂
* 在对象创建过程中会使用到系统中的一些其他对象，这些对象在产品对象的创建的创建过程中不易得到时，也可以采用建造者模式封装该对象的创建过程。<br>

# 没有对比就没有伤害 来互相伤害啊
## 工厂方法模式vs建造者模式
工厂方法模式注重的是整体对象的创建方法，而建造者模式注重的是部件构建的过程，旨在通过一步一步地精确构造创建出一个复杂的对象。<br>
举个🌰，差异：如果建造一个超人，工厂模式就是马上就能生产一个超人，建造者模式就会生产手脚头躯干等部分，然后穿内裤，才出来一个超人。<br>
关注点会不同。建造者，关注的是全身部件细节，最后还要穿底裤！工厂方法模式就是一个整体，已经穿上底裤了，没什么看头。<br>

## 抽象工厂模式vs建造者模式
抽象工程模式实现对产品家族的创建，一个产品家族是这样的一系列产品：具有不同分类维度的产品组合，采用抽象工厂就不需要关心构建过程，只关心什么产品由什么工厂生产即可。<br>
建造这模式 按照要求的蓝图构建产品，目的是组装。<br>
抽象工厂模式就是一个一个工厂，每个工厂生产自己的产品。<br>
建造者就是有一条生产线，在生产线上操作生成什么样的产品<br>
如果需要屏蔽对象的创建过程，可以选择抽象工厂。如果通过不同的组装，相同的方法，可以选择建造者模式。<br>

## 单例模式vs原型模式
单例，内存只有一个，原型，通过复制，移动，生成一个新的对象。<br>