
#include <iostream>
using namespace std;
/***单例模式
 * 自己的事情自己做！
 * 保证线程安全
 * ***/

class Father{
    public:
        static Father* getFather();
        static void say(){
            cout << "i am father" << endl;
        }
    private:
        Father(){};
        Father& operator=(const Father&);
        Father(const Father&);
        static Father* father;   
        virtual ~Father(){
            delete father;
            father = nullptr;
        }         
    };
Father* Father::father = nullptr;
Father* Father::getFather(){
    if(nullptr == father){
        father = new Father();
    }
    return father;
}

int main(){
    Father *iamfather = Father::getFather();
    iamfather->say();
    return 0;
}