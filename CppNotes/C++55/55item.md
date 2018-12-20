## Effective C++ 55 items
### 导读
学习程序语言根本大法是一回事； **学习如何以某找那个语言设计并实现高效程序则是另一回事。特别是C++**<br>
一组明智的选择并精心设计的classes,functions和templates可使程序编写容易、直观、高效、并且远离错误。<br>
这里的导引，使你的软件易理解、易维护、可移植、可扩充、高效、并且有着你所预期的行为。<br>
本书会告诉你如何回避编译器难以显露的问题。<br>
### 术语
**所谓声明式(declaration)** 是告诉编译器某个东西的名称和类型(type)，但略去细节。
```cpp
extern in x; // 对象声明式
size_t numDigiys(int number); //函数声明式
class Widget; // 类的声明式
template<class T> class GraphNode; // 模版声明式
```

size_t,vector,cout这类东西都在std内。<br>
每个函数的声明揭示其签名式(signature)，也就是参数和返回类型。<br>
一个函数的签名等同于该函数的类型。numDigits函数的签名式`std::size_t(int)`。<br>
**定义式(definition)** 的任务是提供编译器一些声明式所遗漏的细节。<br>
⭕️ 对对象而言，定义式是编译器为此对象拨发内存的地点。<br>
⭕️ 对function或function template而言，定义式提供了代码本体。<br>
⭕️ 对class或class template而言，定义式列出它们的成员<br>
```cpp
int x;
std::size_t numDigits(int number){
    ...
};
// 都是定义式
class Widget{  
    public:
        Widget();
        ...
};

```
初始化(initialization)是“给予对象初值”的过程。对用户自定义类型的对象而言，初始化由构造函数执行。<br>
所谓default构造函数是一个可被调用而不带任何实参者。这样的构造函数要不没有参数，要不每个参数都有缺省值 **这里应该对default有了更深的认识**<br>
```cpp
class A{
    public:
        A(); // default
};
class B{
    explicit B(int x = 0,bool b = false); //default
};
class C{
    public:
        explicit C(int x); // 非default
};
```
上述的explicit声明，阻止它们被用来执行隐式转换(implicit type conversions)，但它们可被用来进行显式转换(explicit type conversions)<br>
被声明为explicit的构造函数禁止了编译器执行非预期的类型转换。 **鼓励执行explicit**<br>
copy构造函数被用来 **“以同型对象初始化自我对象”**，copy assignment操作符被用来 **"从另一个同型对象中拷贝其值到自我对象“**。<br>
```cpp
class Widget{
    public:
       ...
       Widget(const Widget& rhs);
       Widget& operator=(const Widget& lhs);
};
Widget w1(w2); // 调用copy构造函数
w1 = w2; // 调用copy assignment操作符
Widget w3 = w2; // 调用copy构造函数！！！ ⬅️⬅️⬅️⬅️⬅️
```
如果有一个新对象被定义，例如w3，一定会有个构造函数被调用，不可能调用赋值操作。如果没有新对象被定义，就不会有构造函数被调用，那么就会调用赋值操作。<br>
🌈 pass by value意味着“调用copy构造函数”。STL➡️➡️致力于vector,list,set,map等等，迭代器`vector<int>::iterator`,`set<string>::iterator`，算法for_each,find,sort等等。<br>
不明确行为。undefined,空指针，无效的指针索引。不明确（未定义）行为的结果是不可预期的。C++没有接口，但是有近似接口的virtual。<br>
### 关于线程
可移植C++提供了多线程。⬅️⬅️⬅️
### TR1和Boost
TR1("Technical Report 1")是一份规范，描述加入C++标准库的诸多新机能<br>
所有TR1组件都被置于命名空间tr1内，后者嵌套于命名空间std内。<br>
Boost是一个组织。也是一个网站，提供可移植、同僚复审、源码开放的C++程序库。<br>

## A 让自己习惯C++ Accustoming Yourself to C++
### 01 View C++ as a federation of languages
不同于C with class的各种观念、特性和编程战略。<br>
⭕️ Exception 对函数的结构化带来不同的做法。<br>
⭕️ templates 将我们带到新的设计思考方式<br>
⭕️ STL则定义了前所未见的伸展性做法<br>
今天的C++已经是一个多重范型编程语言，一个同时支持过程形式C、面向对象C with class、函数形式、范型形式、元编程形式的语言。<br>
✅ 语言联邦：**C && Object-Oriented C++ && Template C++ && STL**<br> 
对内置类型而言pass-by-value通常比pass-by-reference高效。但是从C part of C++移往OO C++，由于用户自定义的析构函数和构造函数的存在，pass-by-reference-to-const 往往会更好。对于template尤其如此。<br>
⭕️ C++高效编程守则视状况而变化，取决于你使用C++的哪一部分。<br>

### 02 Prefer to const,enum,inline to #defines
宁可以编译器替换预处理器。<br>
以一个常量替换宏(#define)
```cpp
const double AspectRatio = 1.653;
```
解决一个可能出现的编译错误，如果并非你写的头文件，可能出现未知行为。若是一个语言常量肯定会被编译器知道，并进入了记号表。<br>
两种特殊情况<br>
* 定义常量指针。
```cpp
const char* const authorName = "trans";
```
其实这样定义更好
```cpp
const std::string authorName("trans");
```
* class专属常量。<br>
为了将常量的作用域限制于class内，你必须让它成为class的一个成员(member)；而为确保此常量至多只有一份实体，必须让它成为一个static成员
```cpp
class GamePlayer{
    private:
        static const int NumTurns = 5; // 常量声明式
        int scores[NumTurns]; // 使用该常量
        ...
}
```
如果取某个class专属常量的地址
```cpp
const int GamePlayer::NumTurns;
```
`#define不重视作用域`<br>
旧式编译器也许不支持上述语法，不允许static成员在其声明式上获得初值。此外所谓的“in-class初值设定“也只允许对整数常量进行。可以这样做
```cpp
class CostEstimate{
    private:
        static const double FudgeFactor;
        ...
};
const double CostEstimate::FudgeFactor = 1.35; // 位于实现文件内实现定义
```
一个属于枚举类型的数值可权充ints被使用。<br>
```cpp
class GamePlayer{
    private:
        enum{NumTurns = 5};
        int scores[NumTurns];
        ...
};
```
> enum hack的行为某方面说比较像#define而不像const，取一个enum的地址就不合法。<br>
Enums和#defines一样绝不会导致非必要的内存分配。<br>
> 实用主义使用enum，事实上，enum hack是template metaprogramming(模版元编程)的基础技术。<br>
inlines更实用，解决函数作用域与访问规则问题，#define过于顺序，不如用inline直接声明函数。<br>
形似函数的宏(marcos)，最好改用inline函数替换#defines<br>

### 03 Use const whenever possible
const 的一件奇妙事情，它允许你指定一个语义约束，也就是指定一个不被改动的对象，而编译器会强制实施这项约束。<br>
关键字const多才多艺。可以在classes外部修饰global或namespace作用域的常量，或修饰文件、函数或块作用域(block scope)中被声明为static的对象。<br>
你也可以用const修饰classes内部的static和non-static成员变量。面对指针，可以指出指针本身、指针所指物，或者两者都（或都不）是const。<br>
```cpp
char greeting[] = "Hello";
char *p = greeting;
const char *p = greeting;
char *const p = greeting;
const char* const p = greeting;
```
`const f1(const W *pw)`与`void f2(W const *pw)`两种写法是一样的。<br>
STL迭代器系以指针为根据塑模出来，所以迭代器的作用就像个T* 指针。声明迭代器为const就像声明指针为const一样（即声明一个T* const指针)。
```cpp
const vector<int>::iterator iter = vec.begin();
*iter = 10; // 改变的是所指物
++iter; // ❌
vector<int>::const_iterator cIter = vec.begin(); // const T*
*cIter = 10; // ❌
++cIter; // ✅
```
#### const 成员函数
* 它们使class接口比较容易被理解。得知能否改动对象内容很重要。<br>
* 使“操作const对象“成为可能。<br>
两个成员函数如果只是常量性不同可以被重载。<br>
