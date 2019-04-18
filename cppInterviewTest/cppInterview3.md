## 指针和引用区别，引用可以用常指针实现吗？
上次讲到了static和const不能同时定义成员函数，因为会自相矛盾，没有const *this造成不能访问对象变量，与类关联但是独立于对象，这是最实用的一句话。<br>
那么这次我们继续讲述一下指针和引用这两个复合类型的使用，以及区别。然后我们再回答最后一个问题，引用可以用常指针实现吗？<br>
首先我们先了解一下什么是指针，函数指针以及智能指针，管理资源对象的指针(shared_ptr,unique_ptr,weak_ptr,maked_ptr)。<br>
其次我们了解一下引用包含的左值引用，右值引用，引用折叠，常量引用以及引用的基本概念。<br>
### 指针与引用 相爱相杀相似
C++语言中存放及使用内存地址是通过指针和引用完成的。而对象就是位于某个地址中。
* 什么是指针？<br>
a. 指针是一个对象，允许对指针进行赋值和拷贝，而且在指针的生命周期中，指针可以先后指向不同的对象。<br>
首先我们来看一段代码
```cpp
int *ptr;
int val = 42;
ptr = &val;
```
这就是指针最基本的用法，反映了什么呢？首先我们定义了一个指针ptr，它是一个对象，我们允许对其进行赋值，而这里赋的值是val的地址，先说明一下`&`这个符号就是用来获取某个对象的地址的，取名叫 **取地址符**。<br>
那么我们皮一下，将一个常量赋值给ptr<br>
```cpp
    int *ptr;
    int val = 42;
    ptr = val; // ❌
```
这里是会报错的，为什么呢？首先我们说明了指针是一个对象，那么，这个对象必须要有一个类型，指针的类型就决定了我们能对指针所指的对象进行哪些操作。这里的指针的类型就是`int *`，它是一个对象，它是一个指向int型的对象。<br>
所以当我们给ptr赋值int类型的时候，就会报错。<br>
那么如果是一个对象，那需不需要给他赋初值呢？不需要，因为如果在其作用域中没有赋予初值，将会有一个不确定的值。<br>
那么，对一个指针最基本的操作，就是解引用，也是用`*`获取指针所指的值。这个操作也叫做间接取值(indirection)（霸气的英文，印地略顺）。<br>
解引用获取到相应类型的值<br>
说到类型，那么我们继续来看看`void*`这个指向未知类型。<br>
#### void*
这个怎么用呢？偶尔需要不知道对象确切类型的情况下，仅通过对象在内存中的地址存储或传递对象。
```cpp
    int *ptr;
    int val = 42;
    void *pi;
    void *pi1;
    pi = ptr; // 这里发生了隐式转换
```
那我们能使用pi吗？并不行。其实两个void*指针能比较是不是相等，因为都是存了内存地址的，但是事实上，编译器并不清楚`void*`所指的对象到底是什么类型的，所以对它执行其他操作可能不太安全并且会引发编译器错误。如果要使用还得把它显式地转换成某一特定类型的指针
```cpp
int *piv = static_cast<int*>(pi);
```
这样就可以使用piv的值。强制类型转换将一个指针的类型转换成一种与实际所指对象类型完全不同的新类型，则使用转换后的指针是不安全的行为。<br>
使用转换后的指针是不安全的，因为例如
```cpp
double *pd1 = static_cast<double*>(pi); // 可以但是不安全
```
可能int与double分配内存的方式不一样，就会造成不安全的后果。<br>
那么我们平常见的的数组中的数组名可以看成是指向数组的首元素的指针是怎么回事呢？<br>
#### 数组中的指针
首先，数组的空间申请，就是申请一块连续的空间。那么首元素就是指针，指针加上`n*sizeof(data)`就是数组的元素的位置。
```cpp
char carr[] = {'a','b','c'};
char *p = carr; // char[] 类型到char *隐式转换。
```
#### 函数指针
函数指针和指向类成员的指针不能被赋为void*。<br>
前面说过，指针是一个对象，用以存储内存地址。那么我们可以看到函数题生成的代码也是置于某块内存区域中，因此它也有自己的地址。既然指针可以指向一个对象，存放对象的内存地址，当然也可以让指针指向函数。对于函数，我们只能调用它或者获取它的地址来使用。
```cpp
void errorf(string s){
    cout << s << endl;
}
void (*efct)(string);
int main(){
    efct = &errorf; // 通过函数名获取地址
    efct("runtime_error"); // 
}
```
经典的用法！ 编译器发现efct是一个函数指针，而且参数类型声明相同，函数类型精确匹配，然后就调用函数。<br>
```cpp
void (*f1)(string) = &errorf;// <=> =errorf
void (*f2)(string) = errorf; // <=> =&errorf
int main(){
    f1("error");
    (*f1)("error");// 上下表达式等价
}
```
所以讲到函数指针之后，我们可以开始将一下关于引用的用法
* 什么是引用<br>
讲引用必须包括左值引用，右值引用，折叠引用、常量引用以及普通引用的知识点<br>
其实指针的使用就是为了避免拷贝构造，拷贝赋值等默认操作这些高代价的操作，而传递大量的数据。<br>
其实引用也是为了降低代价来传递大量的数据的。它的作用就是作为对象的别名存放对象的机器地址。<br>
那么引用和指针有什么区别吗？<br>
* 指针是通过解引用`(*)` 来访问对象本身的，而访问引用跟访问对象本身从语法上看是一样一样的。<br>
* 指针可以在其生命周期指向不同的对象（但必须是同类型），而引用所引的永远是一开始初始化那个对象。<br>
* 指针可以为空 `nullptr`，而引用不能为空引用，引用一定会对应着某个对象。<br>
所以总结来说，引用实际上是对象的另外一个名字。<br>
我们先看一段简单的代码，待会再看一段吓人的。
```cpp
int i = 42;
int &r(i);
++r;
int *ptr = &r; // ptr指向i
```
没错，就只有四行，很好，可以看出，引用(&)就是只是i的别名，操作r就等于操作i；`i=43`，这里充分说明了，引用存放的是对象的机器地址，操作r就等于操作i<br>
我们在这里也可以看出，我们不能令某个指针指向引用，也不能定义引用的数组，所以，其实区别于指针，引用他不是一个对象。<br>
每次使用引用，就好像对该指针执行解引用操作。<br>
再来看一段复杂的
```cpp
template<typename T>
class Vector{
    T *elem;
    public:
        T& operator[](int){ return elem[i];} // 返回元素的引用
        const T& operator[](int i)const { return elem[i];} // 返回常量元素的引用
        void push_back(const T& a); //  通过引用传入待添加的元素
};

void func(const Vector<double> &v){
    double b1 = v[1]; //  把operator[](1)所引的double值拷贝给b1
    ...
}
```
很复杂吧！这里面所有都是左值引用，说到左值引用，我们可以先看看以下定义
* 左值引用 引用我们希望改变值的对象
* const引用 引用那些我们不希望改变值的对象
* 右值引用 所引对象的值在我们使用之后就无须保留了（比如临时变量）<br>
上面说得前两种都是左值引用，一般来说（左值持久，右值短暂）<br>
上面持续用到T&，这个普通的T类型的引用，其实传给这个T类型的引用是左值引用，因为它并不是传了值，这个值就没了，而是持续存在的，那么请问const T&就可以不一定是个左值又是为什么呢？先来看一段代码
```cpp
const double& cdr(1);
```
这段代码是可以通过编译并运行的，那为什么这个1这个临时变量可以在常量引用中存在，到底是为什么呢？
* 1. 如果必要的话，先执行目标为T的隐式类型转换
* 2. 所得的值置于一个T类型的临时变量中
* 3. 把这个临时变量作为初始值<br>
所以这个临时变量的生命周期从它创建开始，直到它的引用作用于结束为止。<br>
所以我们经常会在函数中使用
```cpp
void func(const T&,const T&);
```
这种传参方式。<br>
当然也可以返回一个引用类型<br>
```cpp
template<typename K,typename V>
class Map{
    public:
        V& operator[](const K&);
        pair<K,V>* begin(){return &elem[0];}
        pair<K,V>* end(){return &elem[0]+elem.size();}
    private:
        vector<pair<K,V> > elem;
};
template <class K,class V>
V& Map<K,V>::operator[](const K& k){
    for(auto &x:elem)
        if(k==x.first)
            return x.second;
    elem.push_back({K,V{}});
    return elem.back().second; // 返回新元素的默认值
}
```
这里的返回值类型是引用，因为用户肯定是想改以下这个查找到的map值，而这个map的值就是一个引用而不是const引用，可以直接改动。<br>
讲完左，我们讲以下右，这个短暂的引用。<br>
其实设计那么多，就是为了支持对象的不同方法。<br>
* 右值引用对应一个临时对象，用户可以修改这个对象，并且认定这个对象以后不会被用到了。<br>
这里推荐以下这篇文章，四行代码讲述右值引用。<br>
[从四行代码看右值引用](http://purecpp.org/detail?id=172)<br>
所以读完者篇文章，突然对右值引用又有了很深的一次了解。<br>
在这里我挑一段小的来讲
```cpp
    Test& operator=(Test&& test){
        cout << "move function"<< endl;
        if(this==&test)
            return *this;
        //delete m_ptr;
        m_ptr = test.m_ptr;
        test.m_ptr = nullptr;
        return *this;
    }
```
这是移动赋值运算符。使用std::move就可以调用它<br>
```cpp

#include <iostream>

using namespace std;

/***
 * 所以右值引用是独立于左值和右值
 * 以下是一个好例子
 * 放入一个左值，那么T&& t 就是一个左值
 * 放入一个右值，那么T&& t 就是一个右值
 * 这里发生了自动类型推断
 * 是发生在函数中的
 * 类型中
 * 并没有类型的自动推断
 * 所以当我们使用移动构造函数的时候，需要使用的移动运算符std::move
 * 
 * **/
void processValue(int &a){cout <<"lvalue"<<endl;}
void processValue(int &&a){cout << "rvalue"<<endl;}
template<typename T> void func(T&& val){
    processValue(std::forward(val)); // FIXME:
}
int && i = 0;

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
        Test tmpTest;
        tmpTest.mptr = test.mptr;
        test.mptr = mptr;
        mptr = tmpTest.mptr;
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
Test getA(){
   Test test;
   return test; // 这是一个临时量
}
int main(){
    // cout << i << endl;
    // int inum = 100;
    // const int&& inumref = 100;
    // func(inumref);
    Test test;
    Test movTest = std::move(getA()); // 调用移动构造函数 所以这里不需要再构造一次，直接用移动构造
    // test = movTest;
    test = std::move(getA()); // 这里
    int i = 10;
    func(i);
    func(0);
    return 0;
}
```
move并不执行什么移动操作，他只是无条件地把左值转换为右值，而forward也不做什么转发工作，只是有条件地将左值转换为右值，或者将左值保留为左值。<br>
那么知道了move，我们来看看以下这段代码，完美的swap
```cpp
template<class T>
void swap(T& a,T& b){
    T tmp(move(a)); // a中移出值
    a = move(b); // b中移出值
    b = move(tmp); // tmp中移出值
}
```
确实很完美，根本没有浪费成本执行拷贝操作。<br>
基本上讲了大概的引用与指针，也说明了这两个的区别，那我们来回答一下能不能使用常量指针来实现引用呢？
```cpp
int *const p;// ❌ 必须要有初始化的对象
int i;
int &r = i;
int ii;
r = ii;
```
* 常量指针，一开始必须要有初始化的对象，后面也不允许改变这个指针存放的内存值，也就是不能重新赋值。而引用却是可以的，因为它不是一个对象，他只是一个别名，它的更改是直接更改于原来的对象的
* 而且常量指针根本没办法改变，没办法改变自己的值，自己的内存地址
* 传参也不一样，引用穿得参是可以改的，但是常量指针传的就不能改，只能改变这个常量指针原来保存的值才能改。
通过这样的区别，所以说，其实引用是不能用常量指针来实现的。<br>
问题是回答了，但是还是需要讲一下智能指针的使用，weak_ptr和unique_ptr的使用。<br>
#### 未完待续...