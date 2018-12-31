/***
 * 依赖倒置原则
 * 高层模块不依赖低层模块，两模块都依赖其抽象
 * 抽象不依赖细节 实现
 * 细节依赖抽象
 * ***/
#include <iostream>
using namespace std;

class IDriver{
    public:
        IDriver(){}
        virtual void drive() = 0;
        virtual ~IDriver() = default;
};

class ICar{
    public:
        ICar(){}
        virtual void run(){
            cout << "a car can run"<<endl;
        };
        virtual ~ICar() = default;
};

class Benz:public ICar{
    public:
        Benz(){}
        void run() override;
        ~Benz()=default;
};

class BMW:public ICar{
    public:
        BMW(){}
        void run() override;
        ~BMW()=default;
};

class Driver:private IDriver{
    public:
        Driver(ICar* _icar):icar(_icar){

        }
        void drive(){
            icar->run();
        }
        ~Driver()=default;
    private:
        ICar* icar;
};

void Benz::run(){
    cout << "benz run" << endl;
}

void BMW::run(){
    cout << "BMW run" << endl;
}

int main(){
    ICar *benz = new Benz();
    benz->run();
    // benz.run();
    Driver *trans = new Driver(benz);
    trans->drive();
    return 0;
}