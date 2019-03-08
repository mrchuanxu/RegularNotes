### 札记 面试题集锦
最近真的要准备面试了，不能继续深挖某某知识点了😄，看到这些问题，自己答一遍，加深印象。
#### 字节对齐以及为什么要字节对齐？字节对齐的相关规则？
在我遇到的字节对齐的相关知识点是struct和union。字节对齐使得内存空间使用更大，不用浪费空间，char一般会分配1个字节，结合CPU访问的效率来说，对齐字节会对访问的效率更高，对齐存取效率会更高。OK，现在是标准答案。
1⃣️ 什么是字节对齐？<br>
看了那么多文章，其实总结了一下，什么是字节对齐。字节对齐就是在内存存储数据的时候是按照字节存储的，而字节存储是存在位置的，那就是内存，内存一般都会有地址，而地址是按顺序分高低位的。在结构中，编译器为结构的每个成员按其自然边界(aligment)分配空间。各个成员按照被声明的顺序在内存中顺序存储，第一个成员的地址就和整个结构的地址相同。然后按顺序，现代操作系统的cpu都是默认按4个字节访问内存。那么为了让cpu能够快速访问，一般，变量都会按照 **起始地址%sizeof(type) == 0**进行地址对齐，也就是字节对齐会让每个内存地址对应上每个字节的起始位置。如果当前成员的起始地址能被sizeof整除，就可以把数据存放在这；否则就得🉐️继续看下一个地址能不能被sizeof整除，直到找到合适的地址为止。不适合作为起始地址的空间将被空(lang)闲(fei)。<br>

[字节对齐与地址](../unixAdvance/img/sizeof.png)

现在计算机的内存空间都是按照byte划分的，从理论上讲似乎对任何类型的变量的访问可以从任何地址开始，但是实际情况是在访问特定类型变量的时候经常在特定的内存地址访问，就需要各种类型数据按照一定的规则在空间上排列，而不是顺序的一个接一个的排放。以上对齐。<br>

2⃣️ 为什么字节对齐，如果对齐CPU访问效率会更高<br>
好了，我们知道了字节对齐，那么为什么要字节对齐呢？为了提高cpu的访问内存的效率。为什么能提高cpu内存的访问效率呢？因为每次cpu访问内存的时候都需要以字节为单位进行访问。如果自然对齐，当然，cpu就能一次取出数据而不用通过剔除不要的数据，再次访问内存，然后在拼接成想要的数据，这就需要字节对齐的设计。
3⃣️ 字节对齐相关规则<br>
字节对齐的规则是什么呢？我们先来看一段代码<br>
```c
struct alig{
    char a;
    char b;
    int c;
}
```
首先a会放在第一个字节，那么就是0x00，而b会放在第二个字节0x01因为一个存储空间一个字节，地址可以按照 **起始地址%sizeof(type) == 0**公式来存放。那么int c占2个字节，地址会放在0x02很和谐。那么下面这个呢？
```c
struct alig1{
    double a;
    char b;
    int c;
}
```
根据以上的逻辑，double a会占8字节，从0x00-0x07，char b占一个字节，会占用0x08，int c占用两个字节，0x09与2求余不为0，继续找，找到了0x10，所以占了多少字节？8+1+1+2=12字节。<br>
所以规则就是按照 **起始地址%sizeof(type) == 0**公式计算地址位置。起始明白了，底层的数据存储格式，按照多少字节读取都是一样的计算方式。<br>
pragma就是告知cpu读取字节的模式，但是cpu
#### STL的了解情况（对顺序容器、关联型容器做了一些简单的介绍）
连续型容器:vector,array,heap,priotiry,list,slist,deque,stack,queue。<br>
关联容器: set,map,multiset,multimap,unordered map,unordered set。<br>
怎么介绍呢？介绍一下怎么写的，特性。<br>
所有容器都默认使用了默认分配器，它用new分配空间，delete释放空间，所以我们的先明白分配器到底是怎么回事！allocator到底是怎么回事呢？<br>
```cpp
/***allocator实现模型
 * ***/
template<typename T>
class allocator_{
    public:
        using size_type = size_t;

        template<typename U>
            using other = allocator_<U>;
        
        allocator_()noexcept;
        allocator_(const allocator_&)noexpect;

        template<typename U>
        allocator_(const allocator_<U>&)noexcept;

        ~allocator_();

        T* address(T& x)const noexpect;

        const T* address(const T&) const noexpect;

        T* allocate(size_t n,allocator_<void>::const T* hint=0); // 分配n个字节
        void deallocate(T* p,size_t n); // 释放n个字节

        size_t max_size()const noexpect;

        template<typename U,typename... Args>
        void construct(U* p,Args&&... args); // new(p)U{args}

        template<typename U>
            void distory(U* p); // p->~U()

};
```
所以它的实现目的是为给定类型提供内存资源以及提供在内存不再需要时将其归还的地方。allocator分配的内存都是未构造的，我们将在需要添加新元素时用allocator的construct成员在原始内存中创建对象。
```cpp
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
    tesla.destroy(--q);
    tesla.destroy(--q);
    tesla.deallocate(p,3);// destory之后就是释放
    unordered_map<string,int> score1{{"andy",10},{"al",20},{"ba",30}};

    // cout << "haha" << endl;
    // for(const auto &x:score1){
    //     cout<< x << endl;
    // }
    return 0;
}
```
好了，allocator了解了，那么关于allocator的类型，其实并不多，只是告诉编译器，先分配内存，提高一些性能，然后不构造。好了挑几个重点介绍一下<br>
vector常用，先看一下vector的底层模版实现<br>
#### vector、list以及map、set这些的数据结构是怎么样的？（连续型内存，类似数组；红黑树）
先了解一下vector底层设计。<br>
先了解红黑树()。
#### 上述结构中插入数据和删除数据的时间复杂度是怎么样的？
