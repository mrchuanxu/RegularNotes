/***
 * STL容器
 * 顺序容器提供对元素（半开）序列的访问
 * 关联容器提供基于关键字查询
 * 容器适配器提供对底层容器的特殊访问
 * 拟容器保存元素序列，提供容器的大部分但非全部功能
 * allocator<T> 希望内存分配和对象构造分离 意味着我们可以分配大量的内存，但是只在真正执行对象创建时操作
 * 调用deallocate之前要先调用destory
 * less<T>一比较标准库
 * at(i)会做范围检查 直接[i]不做范围检查
 * 
 * ***/

#include <memory>
#include <iostream>
#include <unordered_map>
using namespace std;

class Tesla{
    public:
        Tesla(int iinum,char cctr):inum(iinum),ctr(cctr){
            cout << "i am testla"<< ctr << iinum << endl;
        }
        void eat(){
            cout << "eat person" << endl;
        }
        virtual ~Tesla(){
            cout << "delete me" << inum << endl;
        }
    private:
        int inum;
        char ctr;
};

template<typename X,typename Y> ostream& operator<<(ostream &os,pair<X,Y>&p){
    return os<<'{'<<p.first<<','<<p.second<<'}';
}

int main(void){
    allocator<Tesla> tesla;
    auto const p = tesla.allocate(3);
    auto q = p;
    tesla.construct(q++,10,'n');
    tesla.construct(q++,30,'o');
    tesla.construct(q++,4,'p');
    tesla.destroy(--q);
    tesla.deallocate(p,3);

    unordered_map<string,int> score1{{"andy",10},{"al",20},{"ba",30}};

    // cout << "haha" << endl;
    // for(const auto &x:score1){
    //     cout<< x << endl;
    // }
    return 0;
}