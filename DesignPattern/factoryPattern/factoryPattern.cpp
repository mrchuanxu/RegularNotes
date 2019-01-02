#include <iostream>
using namespace std;

/***
 * 工厂模式
 * 定义于一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法使一个类的实例化延迟到其子类
 * 
 * 抽象工厂模式
 * 为创建一组相关或相互依赖的对象提供一个接口，而且无须指定它们的具体类
 * 
 * 把生产线实现
 * 把工厂类抽象
 * 工厂抽象出来调用实现
 * 根据不同的生产线生产！
 * ***/

// 工厂模式
// 定一个抽象的Product类，模版类，可以根据类型变化
// 实现两个方法 抽象出来两个方法
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

// 抽象一个工厂
class Creator{
    public:
    Creator() = default;
    template <typename T> T* createProduct(){
        return new T();
    }
};

// 具体工厂
class ConcreteCreator:public Creator{
    public:
        ConcreteCreator()=default;
        template<typename T> T* createProduct(){
            return new T();
        }
};

int main(){
    Creator *create = new ConcreteCreator();
    Product *product = create->createProduct<ConcreteProductB>();
    product->method1();
    // Product *pA = new ConcreteProductA();
    // Product *pB = new ConcreteProductB();
    // pA ->method1();
    // pB ->method1();
    return 0;
}