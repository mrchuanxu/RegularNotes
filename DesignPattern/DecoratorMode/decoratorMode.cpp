/***
 * 装饰模式
 * 动态地给一个对象添加一些额外的职责
 * 主要是动态
 * 减少添加子类
 * 就是用装饰的思想，给每个实现类加一层包装
 * 加一层封装，调用的时候，直接调用装饰器，这样就能出现需要的封装后的效果
 * 装饰后就是很漂亮咯
 * 方法都重写咯
 *                                                                                  
 * ***/

// 举个🌰 
// 抽象类 schoolreport
#include <string>
using namespace std;

class SchoolReport{
    public:
       virtual void report();
       virtual void sign(string &name);
};

class Decorator:public SchoolReport{
    private:
        SchoolReport dsr;
    public:
        Decorator(SchoolReport sr){
            dsr = sr;
        }

        void report(){
            dsr.report();
        }

        void sign(string &name){
            dsr.sign(name);
        }
};


