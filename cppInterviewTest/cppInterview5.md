## 什么是可调用对象？了解lambda表达式吗？function又是怎么回事？
`[](){}`是C++什么特性<br>
### 可调用对象(可以向一个算法传递任何类别的可调用对象)
原文再续就书接上一回。<br>
上一回我们讲到了shared_ptr通过调用可调用对象进行内存的释放。那么对于可调用对象我们知道多少？<br>
**可调用对象都有哪些？**<br>
C++语言中有5种可调用对象，在这里将会进行一一介绍。包括： **函数、函数指针、lambda表达式、bind创建的对象以及重载了函数调用运算符的类。** 和其他对象一样，可调用对象也有类型。例如lambdayou 自己唯一的（未命名）类类型；函数以及函数指针的类型则由返回值类型和实参类型决定等。<br>
#### 函数
顾名思义，函数也算是一种可调用对象，补充一点，函数的类型由它的返回类型和形参类型共同决定，与函数名无关。那我们来看看实例
```cpp
void funcf(Node* p){
    cout << "hello world" << endl;
}
shared_ptr<Node> bar(new Node(),funcf);
```
为森么可以这样用呢？为什么可以直接将funcf调用，我们首先清楚一点，和函数调用，就是由函数生成的代码置于某块内存中的地址被调用的过程。所以，funcf间接地成为了这块地址的指针。也就是我们说的函数指针，那函数指针的具体定义是什么？
#### 函数指针 (偷偷摸摸地指向了函数)
函数指针指向的是函数而非对象。和指针一样，函数指针指向某些特定类型。先来看一个🌰
```cpp
bool lengthCompare(const string& a,const string& b){
    return a.size()>b.size();
}

bool (*pf)(const string&,const string&);

int main(void){
    pf = lengthCompare;
    if(pf("rrrs","sss")){
        cout << "yes"<<endl;
    };
    return 0;
}
```
我们可以看到pf是一个函数指针，他只想一个函数，该函数的参数是两个const string的引用。我们声明的是函数指针，指向的必须是一个同样的返回类型以及参数类型的函数(需要精准匹配)。<br>
那怎么使用呢？代码中的使用是直接指向某个函数，而且这个函数名其实也充当着指向某块内存的作用，所以这里其实相当于给类型为bool的指针赋值。<br>
也可以这样使用
```cpp
pf = &lengthCompare;
bool b1 = (*pf)("aaa","bbbb");
```
那么如果函数重载呢？函数指针会怎么选择？其实这里并不存在选择的问题，因为函数指针必须精准匹配。<br>
```cpp
void ff(int *);
void ff(unsigned int);

void(*pf)(unsigned int) = ff; // 这里必须精准匹配
```
那么既然一般的指针可以做形参使用，那函数指针呢？如前所述，这也是一个指针，当然可以当作形参来使用。
```cpp
void usePointer(const string& s1,const string& s2,bool (*pf)(const string&,const string&));

usePointer(s1,s2,lengthCompare);
```
如果嫌弃这个指针的声明过于冗长，那么我们可以使用typedef来简化。
```cpp
typedef bool Func(const string&,const string&);
typedef decltype(lengthCompare) Func2;
typedef bool (*Funcp)(const string&,const string&);
typedef decltype(lengthCompare) *FuncP2;
```
所以可以这样使用
```cpp
void usePointer(const string&,const string&,Func);
void usePointer(const string&,const string&,Func2);
```
既然可以传入函数指针，那么返回这个函数的指针呢？
```cpp
using PF = bool(*) (const string&,const string&);

PF f1(const int& a){
    cout << a << endl;
    return lengthCompare;
}
bool (*pf1)(const string&,const string&);
pf1 = f1(9);
pf1("sss","ddd");
```
所以上面使用了lengthCompare作为返回的指针，如代码中这样使用。<br>
返回指向函数的指针我们说明了，哪还有别的吗？也可以用尾置返回函数指针。
```cpp
auto f11(const int& a)->bool(*)(const string&,const string&){
    cout << a << endl;
    return lengthCompare;
}
bool (*pf1)(const string&,const string&);
pf1 = f11(10);
pf1("eeee","sssssss");
```
**尾置返回类型**，任何函数的定义都能使用尾置返回。这种新标准针对于返回类型比较复杂的函数而设计的。比如返回指针数组类型
```cpp
auto func(int i)->int(*)[10];
```
在本应该出现返回类型的地方放置了一个auto。这是显式地指明返回类型。<br>
返回类型有个例子比较重要，这里贴一下
```cpp
decltype(odd) *aPtr(int i){
    return (i%2)?& odd:& even;
}
```
所以继续我们的函数指针，这个可调用对象在shared_ptr中的使用
```cpp
void funcf(Node* p){
    cout << "hello world" << endl;
}
void (*pf)(Node *p);
...
pf = funcf;
shared_ptr<Node> bar(new Node(),pf); // 函数指针
```
那么五个可调用对象我们讲了两个，一个是函数，一个是函数指针，接下来我们讲一下lambda表达式
#### lambda表达式 (我只是一个闭包)
我们先来了解一下谓词<br>
什么是谓词？谓词是一个可调用表达式，其返回结果是一个能用作条件的值。<br>
标准算法所使用的谓词分为一元谓词(接受一个参数)和二元谓词(接受两个参数)<br>
```cpp
bool isShorter(const string& a,const string& b){
    return a.size()< b.size();
}
sort(words.begin(),words.end(),isShorter); // 这里就是二元谓词
```
接受谓词参数的算法对输入序列中的元素调用谓词。因此元素类型必须能转换为谓词的参数类型。<br>
猜测，算法实现中会有这样的模版
```cpp
template<typename T> class sort{
    ...
    sort(T::iter,T::iter,bool (*pf)(const T& a,const T& b));
}
```
还有其他的定义，估计，例如限制谓词的参数长度不大于2。<br>
那么我们如果需要传入更多的参数呢？这时候就需要lambda表达式。<br>
我们先来介绍一下lambda表达式，这也是一个可调用对象，我们可以向一个算法传递任何类别的可调用。<br>
**对于一个对象或表达式，如果可以对其使用调用运算符`()`，则称它为可调用的。**<br>
使用官方的解释，一个lambda表达式表示一个可调用的代码单元。(理解为一个未命名的内联函数)
```cpp
[capture list](parameter list) -> return type { function body} // 这是标准的形式
```
一个lambda表达式包含
1. 一个可能为空的capture list[]，指明定义环境中的那些名字能被用在lambda表达式内，以及这些名字的访问方式是拷贝(=)还是引用(&)。<br>
2. 一个可选的(parameter list)指明lambda表达式所需的参数
3. 一个可选的mutable修饰符 指明lambda表达式可能会修改它自身的状态(即改变通过值捕获的变量的副本)`[v]()mutable{return ++v1;};`<br>
4. 一个可选的noexcept修饰符
5. 一个可选的->返回类型声明 lambda的返回值必须用->尾置返回指定返回类型
6. 一个表达式体<br>
先来看一下一个简单的lambda表达式的使用
```cpp
auto f = []{return 42;};
cout << f() << endl;
```
也是够简单的，但是为什么会有调用运算符呢？其实上面的代码可以看成下面这一段
```cpp
class lambda1{
    public:
       int operator()(){
            return 42;
        }
};
lambda1 lam1;
cout << lam1() << endl;
```
这就是原理<br>
接下来向lambda传递参数，也就是可选的参数列表里面的参数
```cpp
stable_sort(words.begin(),words.end(),[](const string& a,const string& b){return a.size()>b.size();});
```
其实lambda就是一个未命名的类，可以看作下面的实现方式
```cpp
class lambda2{
    public:
        bool operator()(const string& a,const string& b){
            return a.size()>b.size();
        }
}
```
调用运算符的参数就是lamda表达式的形参列表。看完了形参列表我们再来看一下这个捕获列表
```cpp
void print_modulo(const vector<int>& v,ostream& os,int m){
    for_each(begin(v),end(v),[&os,m](int x){if(x%m==0) os<< x << '\n';});
}
// 等价于
class lambda3{
    ostream& os;
    int m;
    public:
        lambda3(ostream& s,int m):os(s),m(mm){} // 捕获列表
        void operator()(int x)const{
            if(x%m==0) os<< x<<'\n'; // m是个全局的变量
        }
}
```
捕获分为6类
[], [&], [=], [capture_list], [&,capture_list], [=,capture_list]<br>
上面出了lambda3之外，都是空捕获，那么什么是捕获呢？[]是lambda的引入符号，如果我们需要在lambda内部需要访问外部的变量就需要捕获。<br>
我们先来看看引用捕获和值捕获有什么区别。先来看一段代码
```cpp
void print(){
    int i = 42;
    auto f = [&i](){return i;}
    ++i;// 改变了i 引用捕获，f()也会改变为43 f保存的是i的引用而非拷贝
}

void print2(){
    int i = 42;
    auto f = [i](){return i;}
    ++i; // 改变了i 值捕获但是f()并没有改变 f保存的是i的副本
}
```
以上就是两个捕获，一个是引用捕获，保存的是i的别名，而另一个是值捕获，保存的是i的副本。<br>
所以这两个混合使用就是我们lambda3的效果。我们继续来看后面几个捕获<br>
拥有多个捕获参数的🌰
```cpp
void print(){
    int i = 42;
    int ir = 43;
    int ie = 44;
    auto f = [&i,&ir,&ie](){i = ir+ie;return i;};
    ++ir;
    f();
    cout << i << endl;
}
//  auto f = [&i,&ir,ie](){i = ir+ie;return i;};也可以这样，但是ie只是一个副本
```
这里改变了i的值，因为通过引用访问，所以改变了i的值。<br>
那么我们继续来看看只有一个[&]或一个[=]的情况。<br>
```cpp
int i = 42;
auto f = [&](){return ++i;};
f();
```
让编译器去推断捕获方式以及参数。名字必须与外部的变量相同，值捕获同理<br>
除了如此，捕获列表还能这样使用[&,capture_list]。我们来看看例子
```cpp
auto f = [&,ir](){i = ir+ie;return i;};
f();
cout << i << endl;
```
对于名字没有出现在捕获列表中的局部变量，通过引用隐式捕获，列表中可以出现this或紧跟这...的名字以表示元素。<br>
看看lambda和this的使用
```cpp
class Request{
    function<map<string,string>(const map<string,string>&)> oper; 
    map<string,string> values;
    map<string,string> results;
    public:
        Request(const string& s);
        void execute(){
            [this](){ results = oper(values);};//根据结果执行相应的操作 相当于执行this.oper,this.results
        }
};
```
但是这里的function又是怎样一回事，啥玩意？<br>
function是标准库类型，通过指明返回类型和参数类型来说明。<br>
🌰
```cpp
int f(double a){
    ++a;
    return 0;
}
function<int(double)> fct{f};
```
function是一种类型，它可以保存你能用调用运算符()调用的任何对象。也就是说一个function类型对象就是一个函数对象。<br>
还能作为lambda的返回方式
```cpp
function<int(double)> f;
f = [](double x){ return x>0?x+0.5:x;}
```
所以其实可以发现，function对于回调、将操作作为参数传递等机制很有用。<br>
```cpp
template<typename...Var>
void algo(int s,Var ...v){
    auto helper = [&s,&v...]{ return s*h1(v...)+h2(v...);}
}
```
这样都是引用捕获的方式。<br>
再来看看[=,capture_list]
```cpp
auto f = [=,&ir](){ return i;};
f();
cout << i << endl;
```
同样对于名字没有出现在捕获列表中的局部变量，通过值隐式捕获。捕获列表不允许包含this。列出的名字必须都是引用捕获(&前缀)。<br>
可变，一般情况下，人们不希望修改函数对象的状态，因此我们可以看到调用运算符是设置成不可修改const的状态，只有极少数情况下才需要修改。所以不能因为少用我们就不学，我们还是的知道。mutable这叫可变
```cpp
stable_sort(words,begin(),words.end(),[count]()mutable{ return --count;});
```
--count负责递减闭包中的v的副本。值捕获也能改，看怎么改。<br>
```cpp
[capture list](parameter list) -> return type { function body} // 这是标准的形式
```
我们继续来看上述的标准形式，后面有一个->尾置返回的类型，这是神马？这就是显式指定返回类型
```cpp
int a;
auto z1 = [=,a]()->int{if(a)return 1;else return 2;};// 指定返回int
```
好了，他的使用形式到这里也就是差不多了，他高频使用于泛型算法，作为可调用对象，平常要很多行代码搞定的事情，它一句话可以搞定，而且这么写了之后执行效率反而提高了。因为编译器有可能使用”循环展开“来加速执行过程<br>
以前不会lambda，你要这么写
```cpp
vector<int> v;  
v.push_back( 1 );  
v.push_back( 2 );  
//...  
for ( auto itr = v.begin(), end = v.end(); itr != end; itr++ ){  
    cout << *itr;  
} 
```
现在会lambda，你可以这么写
```cpp
vector<int> v;  
v.push_back( 1 );  
v.push_back( 2 );  
...  
for_each(v.begin(),v.end(),[](int val){  
    cout << val;
});
```
其实lambda表达式是什么呢？lambda是一种局部类类型，它含有一个构造函数以及一个const成员函数operator()()。<br>
如上，一般情况下，可以使用function配合lambda表达式一起使用，若只是使用一下，起个名字，就可以用auto.<br>
```cpp
auto rev = [&](char *b,char *e){...};
```
或者如果lambda不捕获任何值，可以赋值给一个函数指针(强调，类型必须匹配)
```cpp
double (*p1)(double) = [](double a){return sqrt(a);};
```
#### bind 函数适配器
说完了，lambda，我们再说说bind，这个函数适配器。<br>
使用bind()是有条件的，给定一个函数和一组实参，bind会生成一个可用该函数"剩余"实参<br>
简单的🌰
```cpp
double cube(double);
auto cube2 = bind(cube,2);
```
这是什么意思呢？cube2()会用实参2调用cube()，即cube(2)。<br>
其实也不需要绑定所有的实参，说明了是函数适配器，可以有绑定某一个实参的情况，使用`_n`，_n是占位符，_1表示实参在函数对象中应放在什么位置
```cpp
using namespace placeholders;
void f(int,const string&);
auto g = bind(f,2,_1); // 将实参绑定到2
g("hello");// <=>f(2,"hello");
```
所以可以看到，bind，接受一个可调用对象，并生成一个新的可调用对象，来适应原对象的参数列表。<br>
```cpp
auto newCallable = bind(callable,arg_list);
```
经典用法，用bind修改参数的顺序
```cpp
double f(int a,int b,int c,int d,int e);
auto g = bind(a,b,_2,c,_1);
g(1,2);
```
就会将1给了_1，2给了_2。达到了交换的效果。
详情可以参考我的另一篇文稿[bind参数绑定](https://github.com/Vitomy/RegularNotes/blob/master/CppNotes/Cpp_genericAlogrithm_associative-container_dynamicMemory.md#%E5%8F%82%E6%95%B0%E7%BB%91%E5%AE%9A)
好了，可调用对象，大概就是这样，用于算法的计算，缩短代码，让代码的可读性提高。非常有用。下一篇将讲述省略符形参以及可变参数模版。<br>
##### 未完待续...