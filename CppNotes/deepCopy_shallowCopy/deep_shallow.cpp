/***
 * 关于深拷贝与浅拷贝
 * 尝试深拷贝与浅拷贝的实践问题
 * 首先来熟悉一下拷贝构造函数
 * 浅拷贝，两个都指向同一个内存，当一个被销毁，接下去销毁拷贝而来的对象的时候，就会出现❌ 已经释放过了，还释放？！
 * 深拷贝，两个指向不同的内存，申请一个新的内存空间 一个新的内存空间存储旧内存的值，从而让新分配的值得以删除
 * ***/
#include <iostream>
using namespace std;

class ShallowCopy{
    public:
        ShallowCopy(const int& mCount):m_iCount(mCount){
            cout << "浅拷贝构造函数被调用"<< endl;
            str = new char[4];
        }
        ~ShallowCopy(){
            cout << "浅拷贝析构函数被调用"<< endl;        
            if(nullptr==str)
                return; 
            m_iCount=0;
            delete[] str;
            str = nullptr;
        }
        ShallowCopy(const ShallowCopy& shallowCopy):m_iCount(shallowCopy.m_iCount),str(shallowCopy.str){
            cout << "浅拷贝拷贝构造函数被调用" << endl;
            // 首先这是浅拷贝 存在一个问题，就是会指向同一个指针，当两者销毁的时候就会出现，该对象已经被销毁了
        }
        ShallowCopy& operator=(const ShallowCopy& shallowCopy){
            cout << "浅拷贝拷贝赋值运算符被调用"<<endl;
            if(this!=&shallowCopy){
                delete [] str;
                m_iCount = shallowCopy.m_iCount;
                str = shallowCopy.str;
            }
            return *this;
        }
    private:
       int m_iCount;
       char *str;
};

class DeepCopy{
    public:
        DeepCopy(const int &mCount):m_iCount(mCount){
            cout << "深拷贝de构造函数被调用"<<endl;
            str = new char[4];
        }
        ~DeepCopy(){
            cout << "深拷贝的析构函数被调用"<<endl;
            if(str!=nullptr){
                delete [] str;
                str = nullptr;
            }
        }
        DeepCopy(const DeepCopy& deepCopy):str(new char[4]),m_iCount(deepCopy.m_iCount){// 动态开辟新空间
            // 深拷贝，就是要申请一个新的内存 让指向不再只有一个
            for(int i=0;i<4;++i){
                str[i] = deepCopy.str[i]; // 这里不能单纯地赋值指针，要将每一个指针的指向的值赋给新产生的内存
            }
            cout << "深拷贝的拷贝构造函数被调用"<<endl;
        }
        DeepCopy& operator=(const DeepCopy& deepCopy){
            cout << "深拷贝的赋值运算符被调用"<<endl;
            if(this!=&deepCopy){
                char *tmp = new char[4];
                delete [] str;
                m_iCount = deepCopy.m_iCount;
                for(int i=0;i<4;++i){ // 这里的4是我申请的四个数组的内存空间
                    tmp[i] = deepCopy.str[i]; // 这里不能单纯地赋值指针，要将每一个指针的指向的值赋给新产生的内存
                }
                str = tmp;
            }
            return *this;
        }
    private:
        int m_iCount;
        char *str;
};
int main(){
    // ShallowCopy dp(9);
    // ShallowCopy dp1(10);
    // dp = dp1;
    DeepCopy dp(9);
    DeepCopy dp1(10);
    dp =dp1;
    return 0;
}
