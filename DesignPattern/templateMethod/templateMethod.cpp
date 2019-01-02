#include <iostream>
using namespace std;

/***
 * 模版方法
 * 符合开闭原则
 * 将所有子的操作由父类同一集成操作
 * ***/

class HummerModel{
    protected:
        virtual void start(){
            cout << "Hummer start"<<endl;
        }
        virtual void stop(){
            cout << "Hummer stop"<<endl;
        }
        virtual void alarm(){
            cout << "Hummer alarm"<<endl;
        }
    public:
       virtual void run() final{
            start();
            stop();
            alarm();
        }
};

class HummerModel1:public HummerModel{
    protected:
        virtual void start(){
            cout << "HummerModel1 start"<<endl;
        }
        virtual void stop(){
            cout << "HummerModel1 stop"<<endl;
        }
        virtual void alarm(){
            cout << "HummerModel1 alarm"<<endl;
        }
};


int main(){
    HummerModel *hummerModel = new HummerModel1();
    hummerModel->run();
    return 0;
}