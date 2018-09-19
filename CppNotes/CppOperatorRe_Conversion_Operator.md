![trans.运算符重载与类型转换](./img/1103576888.jpg)
这章节是第十四章。这章介绍运算符重载，这种机制允许内置运算符作用于类类型的运算对象。这样我们创建的类型直观上就可以像内置类型一样使用，运算符重载是C++借以实现这一目的的方法之一。<br>
类可以重载的运算符中有一种特殊运算符---函数调用运算符。对于重载了这种运算符的类，我们可以“调用”其对象，就好像它们是函数一样。新标准库中提供了一些设施，使得不同类型的可调用对象可以以一种一致的方式来使用，我们也将介绍这部分内容。<br>
最后将介绍另一种特殊类型的类成员函数---转换运算符。这些运算符定义了类类型对象的隐式转换机制。编译器应用这种转换机制的场合与原因都与内置类型转换是一样的。<br>
那么，在第四章中我们看到C++语言定义了大量的运算符以及内置类型的自动转换规则。这些特性使得程序员能编写出形式丰富、含有多种混合类型的表达式。<br>
当运算符被用于类类型的对象时，C++语言允许我们为其制定新的含义；同时，我们也能自定义类类型之间的转换规则。和内置类型的转换一样，类类型转换隐式地将一种类型的对象转换成另一种我们所需类型的对象<br>
@ 当运算符作用于类类型的运算对象时，可以通过运算符重载重新定义该运算符的含义。<br>
## 基本概念
**重载的运算符时具有特殊名字的函数**：它们的名字由关键字operator和其后要定义的运算符号共同组成。和其他函数一样，重载的运算符也包含返回类型、参数列表以及函数体。<br>
**重载运算符函数的参数数量与该运算符作用的运算对象数量一样多。一元运算符又一个参数，二元运算符有两个。**<br>
@ 对于二元运算符来说，左侧运算对象传递给第一个参数，而右侧运算对象传递给第二个参数。除了重载的函数调用运算符operator()之外，其他重载运算符不能含有默认实参。<br>
@ 如果一个运算符函数是成员函数，则它的第一个（左侧）运算对象绑定到隐式的this指针上，因此，成员运算符函数的（显式）参数数量比运算符的运算对象总数少一个。<br>
📒 当一个重载的运算符是成员函数时，this绑定到左侧运算对象。成员运算符函数的（显式）参数数量比运算对象的数量少一个。<br>
**约定：对于一个运算符函数来说，它或者是类的成员，或者至少含有一个类类型的参数:**<br>
```cpp
// ❌ 不能为int重定义内置的运算符
int operator+(int,int);
```
这一约定意味着当运算符作用于内置类型的运算对象时，我们无法改变该运算符的含义。<br>
**我们可以重载大多数（但不是全部）运算符。**<br>
我们只能重载已有的运算符，而无权发明新的运算符号。<br>
有四个符号（+，-，*，&）即是一元运算符也是二元运算符，所有这些运算符都能被重载，从参数的数量我们可以推断到底定义的是哪种运算符。<br>
@ 对于一个重载的运算符来说，其优先级和结合律与对应的内置运算符保持一致。<br>
可以重载的运算符太多，这里列举不能重载的运算符<br>
```cpp
::    .*    .    ?:
```
#### 直接调用一个重载的运算符函数
通常情况下，我们将运算符作用于类型正确的实参，从而以这种间接方式“调用”重载的运算符函数。然而，我们也能像调用普通函数一样直接调用运算符函数，先指定函数名字，然后传入数量正确、类型适当的实参：
```cpp
// 一个非成员运算符函数的等价调用
data1+data2;
// 基于“调用”的表达式
operator+(data2,data2);
// 对成员运算符函数的等价调用
```
两次调用都是等价的，它们都调用了非成员函数operator+。传入的data1是第一个实参，传入data2作为第二个实参<br>
显式地调用成员运算符函数。
```cpp
// 基于“调用”的表达式
data1 += data2;
data1.operator+=(data2);
// 对成员运算符函数的等价调用 将this绑定到data1的地址、将data2作为实参传入了函数。
```
#### 某些运算符不应该被重载
@ 使用重载的运算符本质上是一次函数调用，所以关于运算对象求值顺序的规则无法应用到重载的运算符上。<br>
特别是，逻辑与运算符、逻辑或运算符和逗号运算符的运算对象求值顺序无法保留下来.除此之外，&&和||运算符的重载版本也无法保留内置运算符的短路求值属性，两个运算对象总是会被求值。<br>
我们一般不重载逗号运算符和取地址运算符。<br>
✨ 通常情况下，不应该重载逗号、取地址、逻辑与和逻辑或运算符<br>

#### 使用内置类型一直的含义
当你开始设计一个类时，首先应该考虑的是这个类将提供哪些操作。在确定类需要哪些操作之后，才能思考到底应该把每个类操作设成普通函数还是重载的运算符。如果某些操作在逻辑上与运算符相关，则它们适合于定义成重载的运算符：<br>
@ 如果类执行IO操作，则定义移位运算符使其与内置类型的IO操作保持一致。<br>
@ 如果类的某个操作是检查相等性，则定义operator==；如果类有了operator==，意味着它通常也应该有operator!=。<br>
@ 如果类包含一个内在的单序比较操作，则定义operator<；如果类有了operator<,则它也应该 含有其他关系操作。<br>
@ 重载运算符的返回类型通常情况下应该与其内置类型版本的返回类型兼容：逻辑运算符和关系运算符应该返回bool，算术运算符应该返回一个类类型的值，赋值运算符和复合赋值运算符则应该返回左侧运算对象的一个引用。<br>
💡 **尽量明智滴使用运算符重载。**<br>
每个运算符在用于内置类型时都有比较明确的含义。以二元+运算符为例，它明显执行的是加法操作。因此，把二元+运算符映射到类类型的一个类似操作上可以极大地简化记忆。<br>
#### 赋值和复合赋值运算符
赋值运算符的行为与复合版本的类似：赋值之后，左侧运算对象和右侧运算对象的值相等，并且运算符应该返回它左侧运算对象的一个引用。**重载的赋值运算应该继承而非违背其内置版本的含义**<br>
#### 选择作为成员或者非成员
当我们定义重载的运算符时，必须首先决定是将其声明为类的成员函数还是声明为一个普通的非成员函数。<br>
将运算符定义为成员函数还是普通的非成员函数的准则以及抉择:<br>
@ 赋值（=），下标（[]),调用(（）)和成员访问箭头（->）运算符必须是成员。<br>
@ 复合赋值运算符一般来说应该是成员，但并非必须，这一点与赋值运算符略有不同。<br>
@ 改变对象状态的运算符或者与给定类型密切相关的运算符，如递增、递减、和解引用运算符，通常应该是成员<br>
@ 具有对称性的运算符可能转换任意一端的运算对象，例如算术、相等性、关系和位运算符等，因此它们通常应该是普通的非成员函数。<br>
程序员希望能在含有混合类型的表达式中使用对称性运算符。🌰 我们能求一个int 和 double的和，因为它们中的任意一个都可以是左侧运算对象或右侧运算对象，所以加法是对称的。**如果我们想提供含有类对象的混合类型表达式，则运算符必须定义非成员函数。**<br>
当我们把运算符定义成成员函数时，它的左侧运算对象必须时运算符所属类的一个对象。<br>
🌰 ：
```cpp
string s = "world";
string t = s+')'; // 可以把一个const char*加到一个string对象中 s.operator+(')')
string u = "hi"+s; // 如果+是string的成员，则产生错误。
```
因为string将+定义成了普通的非成员函数，所以"hi"+s等价于operator+("hi",s)。和任何其他函数调用一样，每个实参都能被转换成形参类型。唯一的要求是至少又一个运算对象是类类型，并且两个运算对象都能准确无误地转换成string.<br>
❓ 在什么情况下重载的运算符与内置运算符有所区别？在什么情况下重载的运算符又与内置运算符一样？<br>
我们可以直接调用重载运算符函数。重置运算符与内置运算符有一样的优先级与结合性。<br>
```cpp
#include <string>
#include <iostream>
class Sales_data{
    friend std::istream& operator>>(istream&, Sales_data&); // input
    friend std::ostream& operator<<(ostream&, const Sales_data&); //output
    friend Sales_data operator+(const Sales&, const Sales_Data&);
    ...
    Sales_data& operator+=(const Sales_data&);
}
```
### 输入和输出运算符
IO标准库分别使用>>和<<执行输入和输出操作。对于两个运算符来说，IO库定义了用其读写内置类型的版本，而类则需要自定义适合其对象的新版本以支持IO操作<br>
#### 重载输出运算符<<
通常情况下，输出运算符的**第一个形参是一个非常量ostream对象的引用**。之所以ostream是非常量是因为向流写入内容会改变其状态；而该形参是引用是因为我们无法直接复制一个ostream对象。<br>
**第二个形参一般来说是一个常量的引用，该常量是我们想要打印的类类型。**第二个形参是引用的原因是我们希望避免复制实参；而之所以该形参可以是常量是因为（通常情况下）打印对象不会改变对象的内容。<br>
为了与其他输出运算符保持一致，operator<<一般要返回它的ostream形参。<br>
##### Sales_data的输出运算符
🌰 
```cpp
ostream &operator<<(ostream &os, const Sales_data &item){
    os<<item.isbn()<<""<<item.units_sold<<""<<item.revenue<<""<<item.avg_price();
    return os;
}
```
##### 输出运算符尽量减少格式化操作
用于内置类型的输出运算符不太考虑格式化操作，尤其不会打印换行符，用户希望类的输出运算符也像如此行事。
##### 输入输出运算符必须是非成员函数
假设输入输出运算符是某个类的成员，则它们也必须是istream或ostream的成员。然而，这两个类属于标准库，并且我们无法给标准库中的类添加任何成员。<br>
因此，如果我们希望为类自定义IO运算符，则必须将其定义成非成员函数。**当然，IO运算符通常需要读写类的非公有数据成员，所以IO运算符一般被声明为友元。**<br>
```cpp
class Sales_data{
    friend ostream &operator<<(ostream &os, const Sales_data &item);
    ...
}
```

```cpp
class String{
    friend ostream &operator<<(ostream &os, const String&);
}

ostream &operator<<(ostream &os, const String &s){
    char *c =  const_cast<char*>(s.c_str());
    while(*c)
        os<<*c++;
    return os;
}
```
### 重载输入运算符>>
@ 输入运算符的第一个形参是运算符将要读取的流的引用。<br>
@ 第二个形参时将要读入到的（非常量）对象的引用。<br>
@ 该运算符通常会返回某个给定流的引用。<br>
第二个形参之所以必须是个非常量是因为输入运算符本身的目的就是将数据读入到这个对象中<br>
##### Sales_data的输入运算符
吃个🌰 ：
```cpp
istream &operator>>(istream &is, Sales_data &item){
    double price; // 不需要初始化，因为我们将先读入数据到price，之后才使用它
    is>>item.bookNo >> item.units_sold >> price;
    if(is)
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();// 输入失败就赋予默认值，确保对象处于正确的状态
    return is;
}
```
📒 输入运算符必须处理输入可能失败的情况，而输出运算符不需要<br>
##### 输入时的错误
@ 当流含有错误类型的数据时读取操作可能失败。<br>
@ 当读取操作到达文件末尾或者遇到输入流的其他错误时也会失败<br>
🏊‍♀️ 当读取操作发生错误时，输入运算符应该负责从错误中恢复。<br>
#### 标示错误
一些输入运算符需要做更多数据验证的工作。<br>
通常情况下，输入运算符只设置failbit。除此之外，设置eofbit表示文件耗尽，而设置badbit表示流被破坏。最好的方式是由IO标准库来标示这些错误。<br>
```cpp
class Sales_data{
    friend istream &operator>>(istream &is, Sales_data &item);
    ...
}
istream &operatr>>(istream &is,Sales_data &item){
    ...
}
```
### 算术和关系运算符
@ 算术和关系运算符定义成非成员函数以允许对左侧或右侧的运算对象进行转换。<br>
@ 因为这些运算符一般不需要改变运算对象的状态，所以形参都是常量的引用。<br>
算术运算符通常会计算它的两个运算对象并得到一个新值，这个值有别于任意一个运算对象，常常位于一个局部变量之内，操作完成后返回该局部变量的副本作为其结果。<br>
如果定义了算术运算符，则它一般也会定义一个对应的复合赋值运算符。此时，最有效的方式是使用复合赋值来定义算术运算符：
```cpp
Sales_data operator+(const Sales_Data &lhs, const Sales_data &rhs){
    Sales_Data sum = lhs; 
    sum += rhs; // 将rhs加到sum中
    return sum;
}
```
与原来的add函数完全等价。<br>
💡 如果类同时定义了算术运算符和相关的复合赋值运算符，则通常情况下应该使用复合赋值来实现算术运算符。<br>
❓ 为什么调用operator+=来定义operator+比其他方法更有效? 因为用`operator+=`会避免使用一个临时对象，而使得更有效。<br>
#### 相等运算符
通常情况下，C++中的类通过定义相等运算符来检验两个对象是否相等。也就是说，它们会比较对象的每一个数据成员，只有当所有对应的成员都相等时才认为两个对象相等。
```cpp
bool operator==(const Sales_data &lhs, const Sales_data &rhs){
  return lhs.item == rhs.item && ...
}
```
几个设计原则：<br>
@ 如果一个类含有判断两个对象是否相等的操作，则它显然应该把函数定义成operator==而非一个普通的命名函数：因为用户肯定希望能使用==比较对象，所以提供了==就意味着用户无须再费时费力地学习并记忆一个全新的函数名字。此外，类定义了==运算符之后也更容易使用标准库容器和算法。<br>
@ 如果类定义了operator==， 则运算符应该能判断一组给定的对象中是否含有重复数据。<br>
@ 通常情况下，相等运算符应该具有传递性，换句话说，如果a==b和b==c都为真，则a==c也应该为真。<br>
@ 如果类定义了operator==，则这个类也应该定义operator!=。对于用户来说，当他们能使用==时肯定也希望能使用!=，反之亦然。<br>
@ 相等运算符和不相等运算符中的一个应该把工作委托给另外一个，这意味着其中一个运算符应该负责实际比较对象的工作，而另一个运算符只是调用那个真正工作的运算符。<br>
💡 如果某个类在逻辑上有相等的含义，则该类应该定义operator==。这样做可以使得用户更统一使用标准库算法来处理这个类。<br>
#### 关系运算符
定义了相等运算符的类也常常（但不总是）包含关系运算符。特别是，因为关联容器和一些算法要用到小于运算符，所以定义operator会比较有用。<br>
通常情况下关系运算符应该<br>
1. 定义顺序关系，令其与关联容器中对关键字的要求一致。<br>
2. 如果类同时也含==运算符的话，则定义一种关系令其与==保持一致。特别是，如果两个对象是!=的，那么一个对象应该<另外一个。<br>
对于Sales_data类来说，不存在一种逻辑可靠的<定义。这个类不定义<运算符也许更好。<br>
💡 如果存在唯一一种逻辑可靠的<定义，则应该考虑为这个类定义<运算符。如果类同时还包含==，则当 且仅当<的定义和==产生的结果一致时才定义<运算符。<br>
### 赋值运算符
之前已经介绍过拷贝赋值和移动赋值运算符，它们可以把类的一个对象赋值给该类的另一个对象。此外，类还可以定义其他赋值运算符以使用别的类型作为右侧运算对象<br>
🌰 ： 在拷贝赋值和移动赋值运算符之外，标准库vector类还定义了第三种赋值运算符，该运算符接受花括号内的元素列表作为参数。
```cpp
vector<string> v;
v = {"a","b"...};
```
同样可以把这个运算符添加到StrVec类中
```cpp
class StrVec{
  public:
  StrVec &operator=(std::initializer_list<std::string>);
  ...
};
```
为了与内置类型的赋值运算符保持一直（也与我们已经定义的拷贝赋值和移动赋值运算符一致），这个新的赋值运算符将返回其左侧运算对象的引用。<br>
```cpp
StrVec &StrVec::operator=(initializer_list<string> il){
  // alloc_n_copy 分配内存空间并从给定范围内拷贝元素
  auto data = alloc_n_copy(il.begin(),il.end());
  free();   //销毁对象中的元素并释放内存空间
  elements = data.first; //更新数据成员使其指向新空间
  first_free = cap = data.second;
  return *this; // 返回其左侧运算对象的引用。
}
```
相同：这个和拷贝赋值及移动运算符一样，其他重载的赋值运算符也必须先释放当前内存空间，再创建一片新空间。<br>
不同：这个运算符无需检查对象向自身的赋值，这是因为它的形参`initializer_list<string>`确保il与this所指的不是同一个对象。<br>
❕**我们可以重载赋值运算符。不论形参的类型是什么，赋值运算符都必须定义为成员函数。**<br>
#### 复合赋值运算符
复合赋值运算符不非得是类的成员，不过我们还是倾向于把包含复合赋值在内的所有赋值运算都定义在类的内部。<br>
为了与内置类型的符合赋值保持一致，类中的复合赋值运算符也要返回其左侧运算对象的引用。
```cpp
// 作为成员的二元运算符：左侧运算对象绑定到隐式的this指针
// 假定两个对象表示的是同一本书
Sales_data& Sales_data::operator+=(const Sales_data &rhs){
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}
```
@ 两类，赋值与复合赋值运算符都应该返回左侧运算对象的引用。<br>
### 下标运算符
表示容器的类通常可以通过元素在容器中的位置访问元素，这些类一般会定义下标运算符operator[]。<br>
📒 下标运算符必须是成员函数。<br>
我们最好同时定义下标运算符的常量版本和非常量版本，当作用于一个常量对象时，下标运算符返回常量引用以确保我们不会给返回的对象赋值。<br>
💡 如果一个类包含下标运算符，则它通常会定义两个版本：一个返回普通引用，另一个是类的常量成员并且返回常量引用。<br>
```cpp
class StrVec{
  public:
  std::string& operator[](std::size_t n){
    return elements[n];
  }
  const std::string& operator[](std::size_t n) const {
    return elements[n];
  }
  private:
  std::string *elements; //指向数组首元素的指针。
}
```
怎么用？？？（黑人问好脸）<br>
假设svec是一个StrVec对象
```cpp
const StrVec cvec = svec;
if(svec.size() && svec[0].empty()){
  svec[0] = "zero";  // 🙆 下标运算符返回string 的引用
  cvec[0] = "zip"; // 🙅 对cvec取下标返回的是常量引用
}
```
这个跟匹配的const有关系！
### 递增和递减运算符
在迭代器类中通常会实现递增运算符(++)和递减(--)运算符，这两种运算符使得类可以在元素的序列中前后移动。C++语言并不要求递增和递减运算符必须是类的成员，但是因为它们改变的正好是所操作对象的状态，所以建议将其设定为成员函数。<br>
为类定义两个版本的递增递减运算符（因为前置，um...后置）。<br>
#### 定义前置递增/递减运算符
```cpp
class StrBlobPtr{
  public:
  // 递增和递减运算符
  StrBlobPtr& operator++();
  StrBlobPtr& operator--();
  ...
}
```
💡 为了与内置版本保持一致，前置运算符应该返回递增或递减后对象的引用。<br>
工作机理：<br>
首先调用check函数检验StrBlobPtr是否有效，如果是，接着检查给定的索引值是否有效。如果check函数没有抛出异常，则运算符返回对象的引用。<br>
在递增运算符的例子中，我们把curr的当前值传递给check函数。如果这个值小于vector的大小，则check正常返回；否则，如果curr已经到达了vector的末尾，check将抛出异常：<br>
```cpp
// 前置版本： 返回递增/递减运算对象的引用
StrBlobPtr& StrBlobPtr::operator++(){
  // 如果curr已经指向了容器的尾后位置，则无法递增它
  check(curr,"increment past end of StrBlobPtr");
  ++ curr; // 将curr在当前状态下向前移动一个元素
  return *this;
}
```
```cpp
// 前置版本： 返回递增/递减运算对象的引用
StrBlobPtr& StrBlobPtr::operator++(){
  // 如果curr是0，则继续递减它将产生一个无效下标
  -- curr; // 将curr在当前状态下向后移动一个元素
  check(curr,"increment past end of StrBlobPtr");
  return *this;
}
```
#### 区分前置和后置运算符
要想同时定义前置和后置运算符，必须首先解决一个问题，即普通的重载形式无法区分这两种情况。前置和后置版本使用的是同一个符号，意味着其重载版本所用的名字将是相同的，并且运算对象的数量和类型也相同。<br>
为了解决这个问题，后置版本接受一个 **额外的（不被使用）int类型的形参。** 当我们使用后置运算符时，编译器为这个形参提供一个值为0的实参。尽管从语法上来说后置函数可以使用这个额外的形参，但是在实际过程中通常不会这么做。<br>
这个形参的唯一作用就是区分前置版本和后置版本的函数，而不是真的要在实现后置版本时参与运算。<br>
```cpp
class StrBlobPtr{
  public:
  // 递增和递减运算符
  StrBlobPtr operator++(int); // 后置版本
  StrBlobPtr operator--(int);
}
```
💡 为了与内置版本保持一致，后置运算符应该返回对象的原值（递增或递减之前的值），返回的形式是一个值而非引用。<br>
```cpp
StrBlobPtr StrBlobPtr::operator++(int){
  // 此处无需检查有效性，调用前置递增运算时才需要检查
  StrBlobPtr ret = *this; // 记录当前的值
  ++*this; // 向前移动一个元素，前置++需要检查递增的有效性
  return ret; // 返回之前的记录的状态
}
```
```cpp
StrBlobPtr StrBlobPtr::operator--(int){
    // 此处无需检查有效性，调用前置递减运算时才需要检查
  StrBlobPtr ret = *this; // 记录当前的值
  --*this; // 向后移动一个元素，前置--需要检查递减的有效性
  return ret; // 返回之前的记录的状态
}
```
@ 无须为int命名。<br>
#### 显式地调用后置运算符
调用要为整形参数传递一个值。<br>
```cpp
StrBlobPtr p(a); // p指向a1中的vector
p.operator++(0); // 后置
p.operator++(); // 前置
```
❓ 为什么不定义const版本的递增和递减运算符？<br>
因为递增和递减会改变对象本身，所以定义const版本毫无意义<br>
### 成员访问运算符
在迭代器类及智能指针类中常常用到解引用运算符(*)和箭头运算符(->)。<br>
```cpp
class StrBlobPtr{
  public:
  std::string& operator*()const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr]; 
    // (*p) 是对象所指的vector
  }
  std::string* operator->()const{
    // 将实际工作委托给解引用运算符
    return & this->operator*();
  }
  ...
}
```
解引用运算符首先检查curr是否仍在作用范围内，如果是，则返回curr所指元素的一个引用。箭头运算符不执行任何自己的操作，而是调用解引用运算符并返回解引用结果的元素的地址。<br>
📒 箭头运算符必须是类的成员。解引用运算符通常也是类的成员，尽管并非必须如此。<br>
⚠️ 我们将这两个运算符定义成了const成员，这是因为与递增和递减运算符不一样，获取一个元素并不会改变`StrBlobPtr`对象的状态。同时，它们的返回值分别是非常量`string`的引用或指针，因为一个StrBlobPtr只能绑定到非常量的StrBlob对象。<br>
用法
```cpp
StrBlob a1 = {"hi","wolf"};
StrBlobPtr p(a1);
*p = "okey";
cout << p->size() << endl; // 首元素的大小
cout << (*p).size() << endl; // 等价p->size()
```
#### 对箭头运算符返回值的限定
和大多数其他运算符一样（尽管这样做不太好），我们能令operator*完成任何我们指定的操作。箭头运算符则不是，它永远不会丢掉成员访问这个最基本的含义。<br>
当我们重载箭头时，可以改变的是箭头从哪个对象当中获取成员，**而箭头获取成员这一事实则永远不变。**<br>
对于形如point->mem的表达式来说，point必须是指向类对象的指针或者是一个重载了operator->的类的对象。根据point类型的不同，point->mem分别等价于
```cpp
(*point).mem; // point是一个内置的指针类型
point.operator()->mem; // point是类的一个对象
```
除此之外，代码都将发生错误。point->mem的执行过程如下所示：<br>
@ 如果point是指针，则我们应用内置的箭头运算符，表达式等价于(*point).mem。首先解引用该指针，然后从所得的对象中获取指定的成员。如果point所指的类型没有名为mem的成员，程序会发生错误。<br>
@ 如果point是定义了operator->的类的一个对象，则我们使用point.operator->()的结果来获取mem。其中如果该结果是一个指针，则执行第一步；如果该结果本身含有重载的operator->()，则重复调用当前步骤。最终，当这一过程结束时程序或者返回了所需的内容，或者返回一些表示程序错误的信息。<br>
📒 重载的箭头运算符必须返回类的指针或者自定义了箭头运算符的某个类的对象。<br>
❓ 定义一个类令其含有指向StrBlobPtr对象的指针，为这个类定义重载的箭头运算符。<br>
```cpp
class StrBlobPtr;
class StrBlobPtr_pointer{
  public:
  StrBlobPtr_pointer() = default;
  StrBlobPtr_pointer(StrBlobPtr* p):pointer(p){}
  StrBlobPtr& operator*();
  StrBlobPtr* operator->();
  private:
  StrBlobPtr* pointer = nullptr;
}
```
### 函数调用运算符
如果类重载了函数调用运算符，则我们可以像使用函数一样使用该类的对象。因为这样的类同时也能存储状态，所以与普通函数相比它们更加灵活。<br>
举个🌰 ：
```cpp
struct absInt{
  int operator()(int val) const{
    return val < 0 ? -val : val;
  }
};
```
这个类只定义了一种操作：函数调用运算符，它负责接受一个int类型的实参，然后返回该实参的绝对值。<br>
我们使用调用运算符的方式是另absInt对象作用于一个实参列表，这一过程看起来非常像调用函数的过程。<br>
```cpp
int i = -42;
absInt absObj;
int ui = absObj(i); 
// 将i传递给absObj.operator()
```
即使absObj只是一个对象而非函数，我们也能“调用”该对象。调用对象实际上是在运行重载的调用运算符。在此例中，该运算符接受一个int值并返回其绝对值。<br>
📒 函数调用运算符必须是成员函数。一个类可以定义多个不同版本的调用运算符，相互之间应该在参数数量或类型上有所区别。<br>
如果类定义了调用运算符，则该类的对象称作 **函数对象** 。因为可以调用这种对象，所以我们说这些对象的“行为”像函数一样。<br>
#### 含有状态的函数对象类
函数对象类通常含有一些数据成员，这些成员被用于定制调用运算符中的操作。<br>
🌰 ：
```cpp
class PrintString{
  public:
      PrintString(ostream &o = cout, char c = ' '):os(o),sep(c){}
      void operator() (const string &s) const { os << s << sep;}
  private:
      ostream &os ; // 用于写入的目的流
      char sep; // 用于将不同输入隔开的字符
}
```
上述类有一个构造函数，它接受一个输出流的引用以及一个用于分隔的字符，这两个形参的默认实参分别是cout和空格。之后的函数调用运算符使用这些成员协助其打印给定的string。<br>
```cpp
PrintString printer; // 使用默认值，打印到cout
printer(s);   // 在cout中打印s，后面跟一个空格
PrinterString errors(cerr,'\n'); 
errors(s); // 在cerr中打印s，后面跟一个换行符
```
函数对象常常作为泛型算法的实参。<br>
```cpp
for_each(vs.begin(),vs.end(),PrintString(cerr,'\n'));
```
❓ 一个重载的函数调用运算符应该接受几个运算对象？<br>
一个重载的函数调用运算符接受的运算对象应该和该运算符拥有的操作数一样多。<br>
```cpp
int operator()(bool b,int ia, int ib){
  return b?ia:ib;
}
```
❓编写一个类似于 PrintString 的类，令其从 istream 中读取一行输入，然后返回一个表示我们所读内容的string。如果读取失败，返回空string。<br>
```cpp
#include <iostream>
#include <string>

class GetInput {
  public:
     GetInput(std::istream &i = std::cin):is(i){}
     std::string operator()() const {
         std::string str;
         std::getline(is,str);
         return is?str:(std::string());
     }
  private:
     std::istream &is;
};

int main(){
  GetInput getInput;
  std::vector<std::string> vec;
  for(std::string tmp;!(tmp = getInput()).empty();) vec.push_back(tmp);
  for(const auto &str:vec) std::cout<< str << " ";
  std::cout << std::endl;
  return 0;
}
```
#### lambda是函数对象
当我们编写一个lambda后，编译器将该表达式翻译成一个未命名类的未命名对象。在lambda表达式产生的类中含有一个重载的函数调用运算符。举个🌰 吧：
```cpp
// 根据单词的长度对其进行排序，对于长度相同的单词按照字母表顺序排序。
stable_sort(words.begin(),words.end(),[] (const string &a, cosnt string &b){return a.size() < b.size();});
```
其行为类似下面这个未命名的对象
```cpp
class ShorterString{
  public:
  bool operator() (const string &s1, const string &s2) const {
    return s1.size() < s2.size();
  }
};
```
产生的类只有一个函数调用运算符成员，它负责接受两个string并比较它们的长度，它的形参列表和函数体与lambda表达式完全一样。<br>
默认情况下lambda不能改变它捕获的变量。因此在默认情况下，由lambda产生的类当中的函数调用运算符是一个const成员函数。如果lambda被声明为可变的，则调用运算符就不是const的了。<br>
用这个类替代lambda表达式后，我们可以重写并重新调用stable_sort:
```cpp
stable_sort(words.begin(),words.end(),ShorterString());
```
第三个实参是新构建的ShorterString对象，当stable_sort内部的代码每次比较两个string时就会“调用”这一对象，此时该对象将调用运算符的函数体，判断第一个string的大小小于第二个时返回true。<br>
#### 表示lambda及相应捕获行为的类
如我们所知，当一个lambda表达式通过引用捕获变量时，将由程序负责确保lambda执行时引用所引的对象确实存在。因此，编译器可以直接使用该引用而无须在lambda产生的类中将其存储。<br>
相反，通过值捕获的变量被拷贝到lambda中。因此，这种lambda产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数，令其使用捕获的变量的值来初始化数据成员。<br>
举个🌰 ：
```cpp
// 获得第一个指向满足条件元素的迭代器，该元素满足size() is >= sz;
auto wc = find_if(words.begin(), words.end(),[sz] (const string &a){ return a.size() >= sz;});
```
该lambda表达式产生的类将形如：
```cpp
class SizeComp{
  SizeComp(size_t n):sz(n){} // 该形参对应捕获的变量
  // 该调用运算符的返回类型、形参和函数体都与lambda一致。
  bool operator()(const string &s) const{ return s.size() >= sz; }
  private:
  size_t sz;
};
```
和我们的ShorterString类不同，上面这个类含有一个数据成员以及一个用于初始化该成员的构造函数。这个合成的类不含有默认构造函数，因此要想使用这个类必须提供一个实参。
```cpp
// 获得第一个指向满足条件元素的迭代器，该元素满足size() is >= sz
auto wc = find_if(words.begin(), words.end(), SizeComp(sz));
```
lambda表达式产生的类不含默认构造函数、赋值运算符及默认析构函数； 它是否含有默认的拷贝/移动构造函数则通常要视捕获的数据成员类型而定。<br>
### 标准库定义的函数对象
标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类，每个类分别定义了一个执行命名操作的调用运算符。例如，plus类定义了一个函数调用运算符用于对一对运算对象执行+的操作；modulus类定义了一个调用运算符执行二元的%操作;equal_to 类执行==，等等。<br>
这些类都被定义成模版的形式，我们可以为其指定具体的应用类型。这里的类型即调用运算符的形参类型。举个🌰 ： `plus<string>`令string加法运算符作用于string对象。`plus<int>` 的运算对象是int; `plus<Sales_Data>`对Sales_Data对象执行加法运算。<br>
```cpp
    plus<int> intAdd; // 可执行int加法的函数对
    negate<int> intNegate; // 可对int值取反的函数对象
    int sum = intAdd(10,20);// 等价sum = 30
    sum = intNegate(intAdd(10,20)); // 等价sum = -30
    // 使用intAdd::operator(int,int)
    sum = intAdd(10, intNegate(10));
    // 使用intNegate(10) 返回-10，然后将-10 作为第二个参数，所以等价sum = 0；
```
9.16🌀 台风山竹，很猛，在家煲剧一整天，只做了一点笔记，很惭愧。
9.17🌀 走了

##### 标准库函数对象
**算术：** plus<Type>,minus...,multiplies...,divides...,modulus...,negate...<br>
**关系：** equal_to...,not_equal_to...,greater...,greater_equal...,less...,less_equal...<br>
**逻辑：** logical_and...,logical_or...,logical_not...<br>
#### 在算法中使用标准库函数对象
表示运算符的函数对象类常用来替换算法中的默认运算符。例如，如果svec是一个`vector<string>`
```cpp
// 传入一个临时的函数对象用于执行两个string对象的>比较运算
sort(svec.begin(),svec.end(),greater<string>());
```
则上面的语句将按照降序对svec进行排序。第三个实参是`greater<string>`类型的一个未命名的对象，因此当sort比较元素时，不再是使用默认的<运算符，而是调用给定的greater函数对象。该对象负责在string元素之间执行>比较运算。<br>
特别⚠️ ，标准库规定其函数对象对于指针同样适用。<br>
曾经介绍过，比较两个无关指针将产生未定义的行为，然而我们可能会希望通过比较指针的内存地址来sort指针的vector。直接这么做将产生未定义的行为，因此我们可以使用一个标准库函数对象来实现该目的：<br>
```cpp
vector<string *> nameTable; // 指针的vector
// ❌ nameTable 中的指针彼此之间没有关系，所以<将产生未定义的行为
sort(nameTable.begin(),nameTable.end(),[] (string *a, string *b){ return a < b;});
// ☑️️ 标准库规定指针的less是定义良好的
sort(nameTable.begin(),nameTable.end(),less<string*>());
```
关联容器使用`less<key_type>`对元素排序，因此我们可以定义一个指针的set或者在map中使用指针作为关键值而无须直接声明less。<br>
❓ 使用标准库函数对象及适配器定义一条表达式，令其a. 统计大于1024的值有多少个  b. 找到第一个不等于pooh的字符串  c. 将所有的值乘以2<br>
```cpp
std::count_if(ivec.cbegin(), ivec.cend(),std::bind(std::greater<int>(), _1, 1024));
std::count_str(ivec.cbegin(),ivec.cend(),std::bind(std::not_equal_to<sting>,_1,"pooh"));
std::mutiply_int(ivec.begin(),ivec.end(),std::bind(std::multiplies<int>,_1.2));
```
❓ 适用标准库函数对象判断一个给定的int值是否能被int容器中的所有元素整除。<br>
```cpp
std::any_of(ivec.begin(),ivec.end(),[&] (int i){ return 0 == std::modulus<int> mod(input,i);});
```
### 可调用对象与function
C++ 语言中有几种可调用的对象：函数、函数指针、lambda表达式、bind创建的对象以及重载了函数调用运算符的类。<br>
和其他对象一样，可调用对象也有类型。例如，每个lambda有它自己唯一的（未命名）类类型；函数以及函数指针的类型则由其返回值类型和实参类型决定，等等。<br>
然而，两个不同类型的可调用对象却可能共享同一种 **调用形式（call signature）**。调用形式指明了调用返回的类型以及传递给调用的实参类型。一种调用形式对应一个函数类型
```cpp
int(int,int); // 是一个函数类型，它接受两个int、返回一个int。
```
##### 不同类型可能具有相同的调用形式
对于几个可调用对象共享同一种调用形式的情况，有时，我们会希望把它们看成具有相同的类型。
```cpp
// 普通函数
int add(int i, int j) {return i+j;}
// lambda,其产生一个未命名的函数对象类
auto mod = [] (int i,int j){ return i%j;};

// 函数对象类
struct divide{
  int operator()(int denominator, int divisor){
    return denominator / divisor;
  }
};
```
上面这些可调用对象分别对其参数执行了不同的算术运算，尽管它们的类型各不相同，但是共享同一种调用形式：`int(int,int)`<br>
举个map的🌰 <br>
假设我们所有函数都相互独立，并且只处理关于int的二元运算，则map可以定义成如下的形式。<br>
```cpp
map<string,int(*)(int,int)> binops;
// 构建从运算符到函数指针的映射关系，其中函数接受两个int、返回一个int
```
可以按照下面的形式将add的指针添加到binops中
```cpp
binops.insert({"+",add}); // ☑️ add是一个指向正确类型函数的指针。
```
但是我们不能将mod或者divide存入binops：
```cpp
binops.insert({"%",mod}); // ❌ mod不是一个函数指针。
```
问题在于mod是个lambda表达式，而每个lambda有它自己的类类型，该类型与存储在binops中的值的类型不匹配。<br>
##### 标准库function类型
我们可以适用一个名为function的新的标准库类型解决上述问题，function定义在functional头文件中。<br>
function操作：<br>
function<T> f; // f是一个用于存储可调用对象的空function，这些可调用对象的调用形式应该与函数类型T相同（即T是retType(args)）<br>
function<T> f(nullptr); // 显式地构造一个空function<br>
function<T> f(obj); // 在f中存储可调用对象obj的副本<br>
f // 将f作为条件：当f含有一个可调用对象时为真；否则为假。<br>
f(args) // 调用f中的对象，参数是args<br>
**定义为function<T>的成员的类型**<br>
result_type // 该function类型的可调用对象返回的类型
argument_type // 当T有一个或两个实参时定义的类型。如果T只有一个实参，则argument_type是该类型的同义词；如果T有两个实参，则 **first_argument_type**和 **second_argument_type**分别代表两个实参的类型。<br>
function是一个模版，和我们使用过的其他模版一样，当创建一个具体的function类型时我们必须提供额外的信息。在此例中，所谓额外的信息是指该function类型能够表示的对象的调用形式。参考其他模版，我们在一对尖括号内指定类型。<br>
```cpp
function<int(int,int)>  // 声明了一个function类型，它可以接受两个int、返回一个int的可调用对象。因此，我们可以用这个新声明的类型表示任意一种桌面计算器用到的类型；
```
```cpp
function<int(int,int)> f1 = add; // 函数指针
function<int(int,int)> f2 = divide(); // 函数对象类的对象
function<int(int,int)> f3 = [] (int i,int j){ return i*j;};
cout<< f1(9,8) << endl;
```
重新定义map
```cpp
map<string, function<int(int,int)>> binops;
```
##### 重载的函数与function
我们不能（直接）将重载函数的名字存入function类型的对象中：
```cpp
int add(int i,int j) {return i+j;}
Sales_data add(const Sales_data&,const Sales__data&);
map<string,function<int(int,int)>> binops;
// 先定义一个指针类型的版本
int (*fp)(int,int) = add; // 指针所指的add是接受两个int的版本
binops.insert({“+”,add})；
// 或者使用lambda
binops.insert({"+",[] (int a,int b){return add(a,b);}});
```
### 重载、类型转换与运算符
转换构造函数和类型转换运算符共同定义了 **类类型转换(class-type conversions)**，这样的转换有时也被称作 **用户定义的类型转换(user-defined conversion)**
#### 类型转换运算符
**类型转换运算符（conversion operator）**是类的一种特殊成员函数，它负责将一个类类型的值转换成其他类型。类型转换函数的一般形式如下：
```cpp
operator type() const;
```
其中type表示某种类型。类型转换运算符可以面向任意类型（除了void外）进行定义，**只要该类型能作为函数的返回类型**。因此，我们不允许转换成数组或者函数类型，但允许转换成指针（包括数组指针及函数指针）或者引用类型。<br>
类型转换运算符既没有显式的返回类型，也没有形参，而且必须定义成类的成员函数。类型转换运算符通常不应该改变待变换对象的内容，因此，类型转换运算符一般被定义成const成员。<br>
##### 定义含有类型转换运算符的类
```cpp
class SmallInt{
  public:
  SmallInt(int i = 0):val(i){
    if(i<0||i>255)
        throw std::out_of_range("Bad SmallInt value");
  }
  operator int() const { return val; }
  private:
      std::size_t val;
}
```
SmallInt类既定义了向类类型的转换，也定义了从类类型向其他类型的转换。其中，构造函数将算术类型的值转换成SmallInt对象，而类型转换运算符将SmallInt对象转换成int：
```cpp
    SmallInt si;
    si = 4; // 首先允许将4隐式地转换成SmallInt，然后调用SmallInt::operator=
    si+3; // 首先将si隐式地转换成int，然后执行整数的加法
```
尽管编译器一次只能执行一个用户定义的类型转换，但是隐式的用户定义类型转换可以置于一个标准（内置）类型转换之前或之后，并与其一起使用。 因此我们可以将任何算术类型传递给SmallInt的构造函数。类似的，我们也能使用类型转换运算符将一个SmallInt对象转换成int，然后再将所得的int转换成任何其他算术类型：
```cpp
SmallInt si = 3.14; // 调用SmallInt(int) 构造函数
// SmallInt的类型转换运算符将si转换成int
si+3.14; // 内置类型转换将所得的int继续转换成double
```
因为类型转换运算符是隐式执行的，所以无法给这些函数传递实参，当然也就不能在类型转换运算符的定义中使用任何形参。同时，尽管类型转换函数不负责指定返回类型，但实际上，每个类型转换函数都会返回一个对应类型的值。<br>
```cpp
class SmallInt;
operator int(SmallInt&); // ❌ 不是成员函数
class SmallInt{
  public:
  int operator int() const; // ❌ 指定了返回类型
  operator int(int = 0) const; // ❌ 参数列表不为空
  operator int*() const { return 42;} // ❌ 42不是一个指针
}
```
❕ **避免过多使用类型转换函数**<br>
如果在类类型和转换类型之间不存在明显的映射关系，则这样的类型转换可能具有误导性。<br>
##### 类型转换运算符可能产生意外结果
在实践中，类很少提供类型转换运算符。<br>
```cpp
int i = 42;
cin << i; // 被当成左移运算符，转换成bool值（1或0）最终被左移42个位置。
```
##### 显式的类型转换运算符
为了防止这样的异常情况发生，C++11新标准引入了 **显式的类型转换运算符(explicit conversion operator)**<br>
```cpp
class SmallInt{
  public:
  // 编译器不会自动执行这一类型转换
  explicit operator int() const{ return val; }
  // 其他成员与之前的版本一致
}
```
```cpp
static_cast<int> (si)+3; // ☑️ 显式地请求类型转换
```
该规定有一个例外，即如果表达式被用作条件，则编译器会将显式的类型转换自动应用于它。<br>
@ if、while以及do语句的条件部分<br>
@ for 语句头的条件表达式<br>
@ 逻辑非运算符(!)、（||）、（&&）的运算对象<br>
@ 条件运算符(?:)的条件表达式<br>
##### 转换为bool
⚠️ 向bool的类型转换通常用在条件部分，因此operator bool一般定义成explicit的。<br>
```cpp
explicit operator string() const { return ... // string; }
explicit operator double() const { return ... // double; }
```
❓ 为Date类定义一个bool的类型转换运算符<br>
```cpp
explicit operator bool() { return (year<4000)?true:false;}
```
#### 避免有二义性的类型转换
如果类中包含一个或多个类型转换，则必须确保在类类型和目标类型之间只存在唯一一种转换方式。<br>
两种情况下会产生多重转换路径。a. 两个类提佛那个相同的类型转换。例如：A类定义了一个接受B类对象的转换构造函数，同时B类定义了一个转换目标是A类的类型转换运算符时。<br>
b. 类定义了多个转换规则，而这些转换涉及的类型本身可以通过其他类型转换联系在一起。<br>
⚠️ 通常情况下，不要为类定义相同的类型转换，也不要在类中定义两个及以上转换源或转换目标是算术类型的转换。<br>
##### 实参匹配和相同的类型转换
B -> A B换成A
```cpp
struct B;
struct A{
  A() = default;
  A(const B&); // 把一个B转换成A
  ...
};
struct B{
  operator A() const; // 也是把一个B转换成A
  ...
};
A f(const &A);
B b;
A a = f(b); // ❌ 二义性 含义是f(B::operator A()) 还是f(A::A(const B&))?
``` 
所以呀，要显式地调用类型转换运算符活着转换构造函数：
```cpp
A a1 = f(b.operator A()); // ☑️ 使用B的类型转换运算符
A a2 = f(A(b)); // ☑️ 使用A的构造函数
```
⚠️ 我们无法使用强制类型转换来解决二义性问题，因为强制类型转换本身也面临二义性。<br>
##### 二义性与转换目标为内置类型的多重类型转换
另外如果类定义了一组类型转换，它们的转换源（或者转换目标）类型本身可以通过其他类型转换联系在一起，则同样会产生二义性的问题。<br>
🌰 ：类当中定义了多个参数都是算术类型的构造函数，或者转换目标都是算术类型的类型转换运算符。<br>
当我们使用用户定义的类型转换时，如果转换过程包含标准类型转换，则标准类型转换级别将决定编译器选择最佳匹配的过程。<br>
📒  **类型转换与运算符**<br>
@ 不要令两个类执行相同的类型转换<br>
@ 避免转换目标是内置算术类型的类型转换。<br>
一言记之日：除了显式地向bool类型的转换外，我们应该尽量避免定义类型转换函数并尽可能地限制那些“显然正确”的非显式构造函数<br>
##### 重载函数与转换构造函数
当我们调用重载的函数时，从多个类型转换中进行选择将变得更加复杂。如果两个或多个类型转换都提供了同一种可行匹配，则这些类型转换一样好。<br>
显式地构造正确的类型从而消除二义性。<br>
⚠️ 如果在调用重载函数是，我们需要使用构造函数活着强制类型转换来改变实参的类型，则这通常意味着程序的设计存在不足。<br>
##### 重载函数与用户定义的类型转换
当调用重载函数时，如果两个（或多个）用户定义的类型转换都提供了可行匹配，则我们认为这些类型转换一样好。<br>
只有当重载函数能通过同一个类型转换函数得到匹配时，我们才会考虑其中出现的标准类型转换。<br>
就是说，如果构造函数时可行匹配的，编译器就会产生二义性，需要显式地使用。<br>
转换的优先级如下：<br>
精确匹配<br>
const 转换。<br>
类型提升<br>
算术转换<br>
类类型转换<br>
### 函数匹配与重载运算符
重载的运算符也是重载的函数。📒 表达式中运算符的候选函数集既应该包括成员函数，也应该包括非成员函数。<br>
🌰 
```cpp
class SmallInt{
  friend SmallInt operator+(const SmallInt&, const SmallInt&);
  public:
  SmallInt(int = 0); //转换源为int的类型转换
  operator int() const {return val;} //转换目标为int的类型转换
  private:
  std::size_t val;
}
```
⚠️ 如果我们对同一个类既提供了转换目标是算术类型的类型转换，也提供了重载的运算符，则将会遇到重载运算符与内置运算符的二义性问题。<br>
其实二义性问题，需要在程序设计中要好好思考一下，避免这种调用就行了。<br>
14章节结束，谢谢观赏。😊 
