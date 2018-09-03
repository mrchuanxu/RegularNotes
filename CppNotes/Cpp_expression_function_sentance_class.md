# C++表达式&语句&函数&类

## 表达式

C++语言提供了一套丰富的运算符，并定义了这些运算符作用于内置类型的运算对象时所执行的操作。同时当运算对象是类类型时，C++语言也允许由用户指定上述运算符的含义。<br>
表达式由一个或多个运算对象组成，对表达式求值将得到一个结果字面值和变量是最简单的表达式，其结果就是字面值和变量的值。<br>
把一个运算符和一个或多个运算对象组合起来可以生成较复杂的表达式<br>
**组合运算符和运算对象**<br>
优先级、结合律以及运算对象的求值顺序。<br>
**运算对象转换**<br>
**重载运算符：**当运算符作用域类类型的运算对象时，用户可以自定义其含义。<br>
**左值与右值：**当一个对象被用作右值的时候，用的是对象的值（内容）；当对象被用作左值的时候，用的是对象的身份（在内存的位置）<br>
**warn：一个重要的原则，是在需要右值的地方可以用左值来替代，但是不能把右值当成左值使用。**<br>
@ 赋值运算符需要一个非常量（左值）作为其左侧运算对象，得到的结果也仍然是一个左值。<br>
@ 取地址符作用于一个左值运算对象，返回一个指向该运算对象的指针，这个指针是一个右值。<br>
@ 内置解引用运算符、string 和 vector 的下标运算度的求值结果都是右值<br>
@ 内置类型和迭代器的递增递减运算符作用于右值运算对象，其前置版本所得的结果也是左值<br>
使用关键字 decltype 的时候，左值和右值也有所不同。如果表达式的求值结果是左值，decltype 作用于该表达式（非变量）得到一个引用类型。<br>
举个例子： 假定 p 的类型是 int *,因为解引用运算符生成左值，所以 decltype(*p)的结果是 int &。另一方面，因为取地址运算符生成右值，所以 decltype(&p)的结果是 int \*\*,也就是说，结果是一个指向整型指针的指针 <br>

## 优先级与结合律

复合表达式是指含有两个或多个运算符的表达式。求复合表达式的值需要首先将运算符和运算对象结合在一起，优先级与结合律决定了运算对象结合的方式。表达式中的括号无视上述规则。<br>

**算术运算符** + - \* % /<br>

**逻辑和关系运算符** ！,<,<=,>,>=,==,!=,&&,||<br>

**赋值运算符** 1.赋值运算符的左侧运算对象必须是一个可修改的左值。2.赋值运算的结果是它的左侧运算对象，并且是一个左值。C++11 标准允许使用花括号括起来的初始值列表作为赋值语句的右侧运算对象： vector<int> vi; vi={0,1,2,3,4,5,6,7,8,9};<br>

3.赋值运算满足右结合律 string s1,s2; s1=s2="ojbk";<br>

4.赋值运算优先级较低<br>

5.复合赋值运算符<br>

## 递增和递减运算符

1.++，-- 递增递减有两种形式：前置版本和后置版本<br>

前置版本将对象本身作为左值返回，后置版本则将对象原始值的副本作为右值返回<br>

```cpp
int i=0,j;

j=++i; //前置版本得到递增后的值

j=i++; //后置版本得到递增前的值
```

建议：如非必须，否则不用递增递减运算符的后置版本<br>

在一条语句中混用解引用和递增运算符<br>

后置递增运算符的优先级高于解引用运算符因此 _pbeg++ <=> _(pbeg++)<br>

2.运算对象可按任意顺序求值<br>

**成员访问运算符**<br>

1.点运算符和箭头运算符都可以用与访问成员<br>

```cpp
(*ptr).mem <=> ptr->mem
```

**条件运算符**<br>

cond ? expr1:expr2;

**位运算符**<br>

1.为运算符作用于整数类型的对象，并把运算对象看成二进制位的集合。 ～位求反 <<,>>,&,^,|<br>

移位运算符 //!important<br>

例子：//529<br>

```cpp
unsigned char bits = 0233;   10011011

0233= 8^2*2+8^1*3+8^0*3; <=> 2^7+2^4+2^3+2^1+2^0

bits<<8 //bits提升成int型，然后向左移动8位

bits<<31 //向左移动31位，左边超出边界的位丢弃掉

bits >>3 //向右移动3位，最右边三位丢弃掉
```

位求反运算符～将 1 置于 0，0 置于 1<br>

位与 **一一得一**，**一零得零**，位或 **一一得一**，**一零得零**，位异或 **对应位置有且只有一个为 1，运算结果中该位为一否则为零**<br>

**sizeof 运算符**<br>

sizeof 运算符返回一条表达式或一个类型名字所占的字节数。sizeof 运算符满足右结合律，其所得的值是一个 size_t 类型的常量表达式。<br>

sizeof(type)<br>

sizeof expr //返回的是表达式结果类型的大小<br>

Sales_data data,\*p;<br>

sizeof(Sales_data); //存储 Sales_data 类型的对象所占的空间大小<br>

sizeof data; //data 的类型的大小<br>

sizeof p; // 指针所占空间大小<br>

sizeof \*p; //p 所指类型的空间大小<br>

sizeof data.revenue; //Sales_data 的 revenue 成员对应类型的大小<br>

sizeof Sales_data::revenue<br>

_C++新标准允许我们使用作用域运算符来获取成员的大小。_

sizeof 运算符的结果部分地依赖于其作用的类型<br>

对 char 或者类型为 char 的表达式执行 sizeof 运算，结果为 1<br>

对引用类型执行 sizeof 运算得到指针本身所占空间的大小<br>

对指针执行 sizeof 运算得到指针本身所占空间大小<br>

对解引用指针执行 sizeof 运算得到指针指向的对象所占空间的大小，指针不需有效<br>

对数组执行 sizeof 运算得到整个数组所占空间大小，等价于对数组中所有元素各执行一次 sizeof 运算并将所得结果求和。<br>

对 string 对象或 vector 对象执行 sizeof 运算只返回该类型固定部分的大小，不会计算对象中的元素占用了多少空间<br>

**逗号运算符**<br>

含有两个运算对象，按照从左向右的顺序依次求值。和逻辑与、逻辑或以及条件运算符一样，逗号运算符也规定了运算对象求值的顺序。<br>

对于逗号运算符来说，首先对左侧的表达式求值，然后将求值结果丢弃掉。逗号运算符真正的结果是右侧表达式的值。如果右侧运算对象是左值，那么最终的求值结果也是左值<br>

逗号运算符经常被用在 for 循环中:

```cpp
vector<int>::size_type cnt = ivec.size();

for(vector<int>::size_type ix = 0;ix!=ivec.size();++ix,--cnt)

      ivec[ix] = cnt;
```

## 类型转换！

如果两种类型可以相互转换，那么它们就是关联的<br>

**自动执行的类型转换叫隐式转换.**

算术类型之间的**隐式转换被设计得尽可能避免损失精度。**（如果表达式中既有整数类型的运算对象也有浮点数类型的运算对象，整型会转换成浮点型。

先执行运算再执行初始化<br

## 何时会发生隐式类型转换

@比 int 类型小的整型值首先提升为较大的整数类型<br>

@在条件中，非布尔值转换成布尔类型<br>

@初始化过程中，初始值转换成变量的类型；在赋值语句中，右侧运算对象转换成左侧运算对象的类型<br>

@如果算术运算或关系运算的运算对象有多种类型，需要转换成同一种类型<br>

@函数调用时也会发生类型转换<br>

## 算术转换

把一种算术类型转换成另一种算术类型。算术转换的规则定义了一套类型转换的层次，其中运算符的运算对象将转换成最宽的类型。<br>

### 整型提升

负责把小整数类型转换成较大的整数类型。<br>

对于 bool,char,signed char,unsigned char, short 和 unsigned short 等类型来说，只要它们所有可能的值都能存在 int 里，它们就会提升成 int 类型；否则提升成 unsigned int 类型。<br>

### 无符号类型的运算对象

如果某个运算符的运算对象类型不一致，这些运算对象将转换成同一种类型。但是如果某个运算对象的类型是无符号类型，那么转换的结果就要依赖于机器中各个整数类型的相对大小了。<br>

### 其他隐式类型转换

数组转换成指针：在大多数用到数组的表达式，数组自动转换成指向数组首元素的指针：<br>

```cpp
int ia[10]; //含有10个整数数组

int *ip = ia; //ia转换成指向数组首元素的指针
```

**指针的转换：**C++还规定了几种其他的指针转换方式，包括常量整数值 0 或字面值 nullptr 能转换成任意指针类型；指向任意非常量的指针能转换成 void*；指向任意对象的指针能转换成 const void*。<br>

**转换成布尔类型：**﻿ 存在一种从算术类型或指针类型向布尔类型自动转换的机制<br>

转换成常量：允许将指向非常量类型的指针转换成指向相应的常量类型的指针，对于引用也是这样。<br>

```cpp
int i;

const int &j = i; //非常量转换成const int的引用

const int *p = &i; //非常量的地址转换成const的地址
```

**类类型定义的转换：**类类型能定义由编译器自动执行的转换，不过编译器每次只能执行一种类类型的转换。<br>

**显式转换:**有时候我们希望显式地将对象强制转换成另外一种类型。<br>

```cpp
int i,j;

double slop = i/j;//强制类型转换
```

### 命名的强制类型转换

cast-name<type>(expression);<br>

type﻿ 是转换的目标类型，﻿expression 是要转换的值。cast-name 是 static_cast,dynamic_cast,const_cast 和 reinterpret_cast 中的一种。<br>

dynamic_cast 支持运行时类型识别。<br>

### static_cast

任何具有明确定义的类型转换，只要不包含底层 const，都可以使用 static_cast。<br>

````cpp
double slop = static_cast<double> (j)/i;

static_cast 对于编译器无法自动执行的类型转换非常有用。

void* p = &d;

double *dp = static_cast<double *>(p);
``
### const_cast

﻿﻿只能改变运算对象的底层const<br
```cpp
const char *pc;

char *p = const_cast<char *>(pc);//去掉const性质（cast away the const)
````

只有 const_cast 能改变表达式的常量属性，使用其他形式的命名强制类型转换改变表达式的常量属性都将引发编译器错误，同样的，也不能用 const_cast 改变表达式的类型<br>

### reinterpret_cast

为运算对象的位模式提供较低层次上的重新解释。<br>

```cpp
int *ip;

char *pc = reinterpret_cast<char*>(ip);
```

**避免强制类型转换！**

### 运算符优先级表

### try 语句块和异常处理

异常是指存在与运行时的反常行为，这些行为超出了函数正常功能的范围。<br>

throw 表达式 异常检测部分使用 throw 表达式来表示它遇到了无法处理的问题。<br>

try 语句块 异常处理部分使用 try 语句块处理异常。<br>

try 语句块以 try 开始，并以一个或多个 catch 子句结束。<br>

一套异常类 用于在 throw 表达式和相关的 catch 子句之间传递异常的具体信息<br>

### throw 表达式

表达式后面通常紧跟一个分号，从而构成一条表达式语句

```cpp
if (item1.isbn() != item2.isbn())

    throw runtime_error("Data must refer to same ISBN");

cout<<item1+item2<<endl;
```

抛出异常将终止当前函数，并把控制权转移给能处理该异常的代码。<br>

## try 语句块

### 标准异常

exception,

runtime_error,

range_error,

overflow_error,

underflow_error,

logic_error,

domain_error,

invalid_argument,

length_error,

out_of_range,

```cpp
#include <iostream>

int main(){

    int i,j;

while(cin>> i>>j){

try{

    int res = i/j;

}catch(runtime_error err){

    cout<<"wrong"<<endl;

    char c;

    cin>>c;

    if(!cin||c=='n')

        break;

}

}
```

## 函数

本章首先介绍函数的定义和声明，包括参数如何传入函数以及函数如何返回结果。在 C++语言中允许重载函数，也就是几个不同的函数可以使用同一个名字。所以接下来我们介绍重载函数的方法，以及编译器如何从函数的若干重载形式中选取一个与调用匹配的版本。最后将介绍一些关于函数指针的知识。<br>

函数是一个命名了的代码块，我们通过调用函数执行相应的代码。函数可以有 0 或多个参数，而且（通常）会产生一个结果。可以重载函数，也就是说，同一个名字可以对应几个不同的函数<br>

### 函数基础

一个典型的函数定义包括以下部分：返回类型，函数名字，由一个或多个形参组成的列表以及函数体。函数执行操作的语句块中说明，该语句称为函数体。<br>

我们通过调用运算符类执行函数。调用运算符的形式是一对圆括号，他作用于一个表达式，该表达式是函数或者指向函数的指针；圆括号之内是一个用逗号隔开的实参列表，我们用实参初始化函数的形参。调用表达式的类型就是函数的返回类型<br>

编写函数

```cpp
int fact(int a){

    int ret = 1;

    while(a>1)

          ret*=a--;

    return ret;

}
```

### 调用

int j = fact(4);<br>

### 形参与实参

实参是形参的初始值。<br>

函数的形参列表,函数的返回值

### 局部对象

名字有作用域，对象有生命周期<br>

@名字的作用域是程序文本的一部分，名字在其中可见<br>

@对象的生命周期是程序执行过程中该对象存在的一段时间<br>

//6.7 暴雨天气 😢

### 函数体是一个语句块。

形参是一种自动对象，函数开始时为形参申请存储空间，因为形参定义在函数体作用域之内，所以一旦函数终止，形参也就被销毁 <br>

## 局部静态对象

```cpp
size_t count_call(){

    static size_t ctr = 0;

    return ++ctr;

}

int main(){

    for(size_t i=0;i!=10;i++)

             cout<<count_call()<<endl;

return 0;

}
```

## 函数声明

函数的名字在使用之前必须声明。函数的声明无须函数体，用一个分号替代即可，也无须形参的名字，写上更好<br>

在头文件进行函数声明<br>

@函数应该在头文件声明，而在源文件中定义<br>

定义函数的源文件应该把含有函数声明的头文件包含进来，编译器负责验证函数的定义和声明是否匹配。<br>

### 分离式编译

分离式编译允许我们把程序分割到几个文件中去，每个文件独立编译。<br>

编译和链接多个源文件<br>

### 参数传递

@每次调用函数时都会重新创建它的形参，并用传入的实参对形参进行初始化。<br>

@形参的类型决定了形参和实参交互的方式。<br>

当形参是引用类型，它对应的实参被引用传递或者函数被传引用调用。@0 引用形参是它对应的实参的别名<br>

当实参的值被拷贝给形参时，形参和实参是相互独立的对象。我们说这样的实参被值传递或者函数被传值调用。<br>

### 传值参数

@当初始化一个非引用类型的变量时，初始值被拷贝给变量。此时对变量的改变不会影响初始值。

### 指针形参

@指针的行为和其他非引用类型一样。<br>

当执行指针拷贝操作时，拷贝的是指针的值。拷贝之后，两个指针是不同的指针。

```cpp
int n = 0, i =42;

int *p = &n, *q = &i; //p指向n；q指向i

*p = 42; // n的值改变；p不变

p = q; //p现在指向了i；但是i和n的值都不变

//该函数接受一个指针，然后将指针所指的值置为0

void reset(int *ip){

    *ip = 0;

    ip = 0;

}

void swap(int *a,int *b){

    int tmp = *a;

   *a = *b;

   *b = tmp;

}
```

### 传引用参数

@对于引用的操作实际上是作用在引用所引的对象上。<br>

```cpp
int n = 0,i=42;

int &r = n;

r=42; //现在n的值是42

r=i; //现在n的值和i相同

i=r; //i的值和r相同

void reset(int &i){ i=0;//改变i所引对象的值}
```

引用形参绑定初始化它的对象。

### 使用引用避免拷贝

@当某种类型不支持拷贝操作时，函数只能通过引用形参访问该类型的对象<br>

举个栗子，我们准备编写一个函数比较两个 string 对象的长度，使用引用避免拷贝<br>

```cpp
bool isShorter(const string &s1. const string &s2)

{

return s1.size() < s2.size();

}
```

@当函数无须修改引用形参时，最好使用。<be>

### 使用引用形参返回额外信息

一个函数只能返回一个值，然而有时函数需要同时返回多个值，引用形参为我们返回多个结果提供了有效的途径。<br>

如何定义函数既返回位置也返回出现次数呢?传入一个额外的引用实参，令其保存字符出现的次数<br>

```cpp
string::size_type find_char(const string&s,char c,string::size_type &occurs){

    auto ret = s.size();

    occurs = 0;

   for(decltype(ret) i = 0;i!=s.size();++i){

        if(s[i] == c){

                  if(ret == s.size())

                         ret = i;

                 ++occurs;

}

} return ret;

}
```

这样我就能在调用 find_char 时，可以直接得出 occurs 的值，也可以获得返回的 ret 的值，根据引用的形参使用

### const 形参与实参

当形参是 const 时，必须要注意的是关于顶层 const 的讨论。顶层 const 作用于对象本身<br>

```cpp
const int ci = 42;//不能改变ci，const是顶层的

int i = ci;

int * const p = &i;// const是顶层的，不能给p赋值

*p = 0; //改变了i
```

当实参初始化形参时会忽略掉顶层 const。换句话说，形参的顶层 const 被忽略掉了。当形参有顶层 const 时，传给它常量对象或者非常量对象都是可以的<br>

void fcn(const int i){//这里举了一个很好的例子，形参是顶层的，可以传入常量和非常量对象；}<br>

### 指针或引用形参与 const

形参的初始化方式和变量的初始化方式是一样的，我们可以使用非常量初始化一个底层 const 对象，但是反过来不行；同时对于一个普通的引用必须用同类型的对象初始化。<br>

const int & ri = 42;//**允许一个常量引用绑定一个非常量，字面值，甚至是一个表达式**

### 尽量使用常量引用

## 数组形参

数组的两个特殊的性质，1. 不允许拷贝数组，2.使用数组时（通常）会将其换成指针。<br>

为函数传递数组时，实际上传递的是指向数组首元素的指针<br>

尽管不能以值传递的方式传递数组，但是我们可以把形参写成类似数组的形式。<br>

void print(const int \*);<br>

void print(const int []);<br>

void print(const int[10]);<br>

上面三个函数是等价的。每个函数的唯一形参都是 const int\*类型。<br>

```cpp
int i = 0, j [3] = {1,1,1};

print(&i);

print(j);
```

因为数组是以指针的形式传递给函数的，所以一开始函数并不知道数组的确切尺寸，调用者应该为此提供一些额外信息<br>

### 管理指针的形参的三种常用技术

@使用标记指定数组长度<br>

@使用标准库规范 //迭代器<br>

@显式传递一个表示数组大小的形参 形参<br>

### 数组形参和 const

### 数组引用形参

C++语言允许将变量定义成数组的引用，基于同样的道理，形参也可以是数组的引用。此时引用形参绑定到对应的实参撒谎那个，也就是绑定到数组上。<br>

```cpp
void print(int (&arr)[10]){//arr 是具有10个整数的整型数组的引用

   for(auto elem:arr)

         cout<<elem<<endl;

}
```

### 传递多维数组

### 数组的数组

将多维数组传递给函数时，真正传递的是指向数组首元素的指针。因为我们处理的是数组的数组，所以首元素本身就是一个数组，指针就是一个指向数组的指针。<br>

**main: 处理命令行选项**<br>

int main(int argc,char \*argv[]){}

### 含有可变形参的函数

为了编写能处理不同数量实参的函数，C++11 新标准提供了两种主要的方法：<br> 1.如果实参类型相同，可以传递一个名为 initializer_list 的新标准类型 <br>

2. 如果实参的类型不同，我们可以编写一种特殊的函数，也就是所谓的可变参数模板。<br>

C++还有一种特殊的形参类型（省略符），可以用它传递可变数量的实参<br>

initializer_list 形参 一种标准库类型，用于表示某种特定类型的值的数组<br>

如果函数的实参数量未知但是全部实参的类型都相同，我们可以使用 initializer_list 类型的形参。<br>

### 操作

```cpp
initializer_list<T> lst; //T类型元素的空列表

initializer_list<T> lst{a,b,c,d...};//lst的元素数量和初始值一样多，lst的元素是对应初始值的副本；列表中的元素是const

lst2(lst)

lst2 = lst

lst.size()

lst.begin()

lst.end()
```

和 vector 不一样的是，initializer_list 对象中的元素永远是常量值，我们无法改变 initializer_list 对象中的元素的值<br>

### 省略符形参

省略符形参是为了便于 C++程序访问某些特殊的 C 代码而设置的，这些代码使用了名为 Varargs 的 C 标准库功能。<br>

### 返回类型和 return 语句

return 语句终止当前正在执行的函数并将控制权返回到调用该函数的地方。<br>

A.return;B.return expression;<br>

return 语句返回值必须与函数的返回类型相同，或者能隐式转换成函数的返回类型<br>

### 值是如何被返回的

返回一个值的方式和初始化一个变量或者形参的方式完全一样：返回值用于初始化调用点的一个临时量，该临时量就是函数调用的结果。<br>

```cpp
const string &shorterString(const string &s1, const string &s2){

return s1.size() <= s2.size()?s1:s2;

}
```

其中形参和返回类型都是 const string 的引用，不管调用函数还是返回结果都不会真正拷贝 string 对象<br>

### 不要返回局部对象的引用或指针

函数终止意味着局部变量的引用将指向不再有效的内存区域<br>

这是一个经常性犯的错误！！！

```cpp
const string &manip(){
    string ret;
    return ret;
//错误，返回局部对象的引用！or return "Empty";错误，“empty”是一个局部临时变量
}
```

### 返回类类型的函数和调用运算符

```cpp
auto sz = shorterString(s1,s2).size();
```

引用返回左值

### 列表初始化返回值

**C++新标准规定，函数可以返回花括号包围的值的列表。**<br>

类似于其他返回结果，此处的列表也用来对表示函数的返回的临时量进行初始化。如果列表为空，临时量执行值初始化；否则，返回的值由函数的返回类型决定。举个例子<br>

```cpp
vector<string> process(){

// expected 和 actual 是string对象

if(expected.empty()) return {};

else return {"functionZ",expected,actual};

}
```

如果函数返回的是内置类型，则花括号包围的列表最多包含一个值，而且该值所占空间不应该大于目标类型的空间。如果函数返回的是类型，由类本身定义初始值如何使用。<br>

### 主函数 main 的返回值

如果函数的返回类型不是 void，那么它必须返回一个值。但是这条规则有个例外:我们允许 main 函数没有 return 语句直接结束。 如果控制到达了 main 函数的结尾处而且没有 return 语句，编译器将隐式地插入一条返回 0 的 return 语句。<br>

main 函数的返回值可以看做是状态指示器。返回 0 表示执行成功，返回其他值表示执行失败，其中非 0 值的具体含义<br>

main 函数的返回值可以看作是状态指示器。<br>

### 递归

### 返回数组指针

@因为数组不能拷贝，所以函数不能返回数组。不过，函数可以返回数组的指针或引用。<br>

```cpp
typedef arr[10]; //arr是一个类型别名，它表示的类型是含有10个整数的数组

using arrT = int[10];//arrT 的等价声明

arrT* func(int i); //func返回一个指向含有10个整数的数组的指针
```

### 声明一个返回数组指针的函数

@要想在声明 func 时不使用类型别名，我们必须牢记被定义的名字后面数组的维度

```cpp
int arr[10]; //arr是一个含有10个整数的数组

int *p1[10];//p1 是一个含有10个指针的数组

int (*p2)[10] = &arr; //p2是一个指针，它指向含有10个整数的数组
```

和这些声明一样，如果我们想定义一个返回数组指针的函数，则数组的维度必须跟在函数名字之后。然而函数的形参列表也跟在函数名字后面且形参列表应该先于数组的维度，因此，返回数组指针的函数形式如下所示：<be>

```cpp
Type (*function(parameter_list))[dimension]
```

如果没有这对括号，函数返回的类型将是指针的数组

```cpp
int (*func(int i))[10];
```

### 使用尾置返回类型

在 C++新标准中还有一种可以简化上述 func 声明的方法，就是使用尾置返回类型。<br>

@任何函数的定义都能使用尾置返回，但是这种形式对于返回类型比较复杂的函数最有效，比如返回类型是数组的指针或者数组的引用。<br>

```cpp
auto func(int i)->int(*)[10];
```

因为我们把函数的返回类型放在形参列表之后，所以可以清楚地看到 func 函数返回的是一个指针，并且该指针指向了含有 10 个整数的数组。

### 使用 decltype

还有一种情况，如果我们知道函数返回的指针将指向哪个数组，就可以使用 decltype 关键字声明返回类型。

```cpp
int odd[] = {1,3,5,7,9};

int even[] = {0,2,4,6,8};

@decltype(odd) *arrPtr(int i){

return (i%2)?&odd : &even;

}
```

接下来是比较重要的函数重载

### 函数重载

@如果同一作用域内的几个函数名字相同但形参列表不同，我们称之为重载函数。<br>

编译器会根据传递的实参类型推断想要的是哪个函数

### 定义重载函数

@不允许两个函数除了返回类型外其他所有的要素都相同

### 重载和 const 形参

@一个拥有顶层 const 的形参无法和另一个没有顶层 const 的形参区分开来<br>

Record lookup(Phone);<br>

Record lookup(const Phone); //两个是一样的<br>

如果形参是某种类型的指针或引用，则通过区分其指向的是常量对象还是非常量对象可以实现函数重载，此时 const 是底层的:<br>

```cpp
Record lookup(Account&);
Record lookup(const Account&);
Record lookup(Account*);
Record lookup(const Account*);
```

@当我们传递一个非常量对象或者指向非常量对象的指针时，编译器会优先选用非常量版本的函数

### const_cast 和重载

@当实参不是常量时，得到的结果是一个普通的引用，使用 const_cast 可以实现这一点

```cpp
string &shortString(string &s1,string &s2){

    auto &r = shortString(const_cast<const string&>(s1), const_cast<const string&>(s2));

    return const_cast<string&>(r);

}
```

### 调用重载的函数

### 重载与作用域

### 特殊用途语言特性

@默认实参，内敛函数和 constexpr 函数<br>

1.默认实参<br>

2.内联函数和 constexpr 函数<br>

内联函数可避免函数调用的开销<br>

@调用函数一般比求等价表达式的值要慢一些。内联函数可避免函数调用的开销。<br>

将函数指定为内联函数，通常就是将它在每个调用点上“内联地” 展开。<br>

在函数的返回类型前面加上关键字 inline，这样就可以将它声明成内联函数了。<br>

```cpp
inline const string& aaa(){}
```

constexpr 函数 用于常量表达式的函数。<br>

@﻿ 内联函数和 constexpr 函数通常定义在头文件中<br>

### 调式帮助

程序可以包含一些用于调试的代码，但是这些代码只在开发程序时使用。当程序编写完成准备发布时，要先屏蔽掉调试代码。预处理功能 assert 和 NDEBUG<br>

assert 是一种预处理宏。所谓预处理宏其实是一个预处理变量，它的行为有点类似于内联函数。assert 宏使用一个表达式作为它的条件<br>

assert (expr);

首先对 expr 求值，如果表达式为假（0），assert 输出信息并终止程序执行。如果表达式为真，即非（0），assert 什么都不做

@assert 宏定义在 cassert 头文件中。预处理名字由预处理器管理。直接使用 assert

### NDEBUG 预处理变量

如果定义了 NDEBUG assert 就什么鬼也不做

### #define NDEBUG

@定义 NDEBUG 能避免检查各种条件所需的运行时开销，当然此时根本就不会执行运行时检查。因此，assert 应该仅用于验证那些确实不可能发生的事情。<br>

### 函数匹配

@确定候选函数和可行函数<br>

### 寻找最佳匹配

### 含有多个形参的函数匹配

### 函数指针

@函数指针指向的是函数而非对象。和其他指针一样，函数指针指向某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。

```cpp
bool lengthCompare(const string&,const string &);
//该函数的类型是bool (const string &,const string&)要想声明一个可以指向该函数的指针，只需要用指针替换函数名即可：

bool (*pf)(const string&,const string &);
//未初始化 pf指向一个函数，该函数的参数是两个const string的引用，返回值是bool类型
```

### 使用函数指针

当我们把函数名作为一个值使用时，该函数自动地转换成指针。<br>

```cpp
pf = lengthCompare; //pf指向名为lengthCompare的函数

pf = &lengthCompare; //等价的赋值语句：取地址符是可选的
```

此外，我们还能直接使用指向函数的指针调用该函数，无须提前解引用指针：

```cpp
bool b1 = pf("hello","goodbye"); //调用lengthCompare函数

bool b2 = (*pf)("hello","goodbye"); //一个等价的调用

bool b3 = lengthCompare("hello","goodbye"); //另一个等价的调用
```

在指向不同函数类型的指针间不存在转换规则。

### 重载函数的指针

```cpp
void ff(int*);

void ff(unsigned int);

void (*pf1)(unsigned int) = ff; //pf1 指向ff(unsigned)
```

### 函数指针形参

和数组类似，虽然不能定义函数类型的形参，但是可以是指向函数的指针。此时，形参看起来是函数类型，实际上却是当成指针使用：

```cpp
void useBigger(const string &s1,const string &s2,bool (*pf)(const string &, const string &));
```

第三个形参是函数类型，他会自动地转换成指向函数的指针

```cpp
void useBigger(const string &s1, const string &s2,bool (*pf)(const string &,const string &));
```

等价声明：显式地将形参定义成指向函数的指针

useBigger(s1,s2,lengthCompare);

简化

```cpp
typedef bool Func(const string &,const string &);

typedef decltype(lengthCompare) func2; //等价类型

typedef bool (*FuncP)(const string &,const string &);

typedef decltype(lengthCompare) *FuncP2;
```

### 返回指向函数的指针

和数组类似，虽然不能返回一个函数，但是能返回指向函数类型的指针。然而，我们必须把返回类型写成指针形式，编译器不会自动地将函数返回类型当成对应的指针类型处理。<br>

using F = int(int\*, int); //F 是函数类型，不是指针

using PF = int(_)(int _,int); //PF 是指针类型

PF f1(int); //显式地将返回类型指定为指针

F \*f1(int); //显式地指定返回类型是指向函数的指针

```cpp
int (*f1(int))(int*,int);
//f1是一个函数，f1前面有*，所以f1返回一个指针，指针类型也包含形参列表
//因此指针指向函数，该函数的返回类型是int
auto f1(int) ->int(*)(int*,int);
```

将 auto 和 decltype 用于函数指针类型<br>

### 函数声明

```cpp
int f1(int ,int);

int f2(int a,int b){ return a+b;};

vector<decltype(f1)*> v;

v.push_back(f2);
```

## 类

在C++语言，我们使用类定义自己的数据类型。通过定义新的类型来反映待解决问题中的各种概念，可以使我们更容易编写、调试和修改程序。本章主要关注数据抽象的重要性。数据抽象能帮助我们将对象的具体实现与对象所能执行操作分离开来。<br>

@类的基本思想是数据抽象和封装。数据抽象是一种依赖于接口和实现分离的编程（以及设计）技术。类的接口包括用户所能执行的操作；类的实现则包括类的数据成员、负责接口实现的函数体以及定义类所需的各种私有函数。<br>

@封装实现了类的接口和实现的分离。封装后隐藏了它的实现细节，也就是说，类的用户只能使用接口而无法访问实现部分。<br>

@类要想实现数据抽象和封装，需要首先定义一个抽象数据类型，在抽象数据类型中，由类的设计者负责考虑类的实现过程。<br>

### 定义抽象数据类型

@设计自己的类（Sales_data）

我们先看一个类

```cpp
struct Sales_data{

    std::string isbn() const { return bookNo;}

    Sales_data& combine(const Sales_data&);

    double avg_price() const;

    std::string bookNo;

    unsigned units_sold = 0;

    double revenue = 0.0;

};

Sales_data add(const Sales_data&, const Sales_data&);

std::ostream &print(std::ostream&,const Sales_data&);

std::istream &read(std::istream&,Sales_data&);
```

### 定义成员函数

成员函数体可以定义在类内也可以定义在类外。<br>

```cpp
std::string isbn() const {return bookNo;}
//定义在类内,它是如何获得bookNo成员所依赖的对象的呢？
```

### 引入 this

total.isbn() 编译器会把 total 的地址传递给 isbn 的隐式形参 this=>Sales_data::isbn(&total);<br>

任何对类成员的直接访问都被看作 this 的隐式引用。this->bookNo;<br>

this 是一个常量指针，**我们不允许改变 this 中保存的地址**<br>

### 引入 const 成员函数

isbn 函数，紧随参数列表之后的 const 关键字，这里 const 的作用是修改隐式 this 指针的类型。<br>

@默认情况下，this 的类型是指向类类型的非常量版本的常量指针。<br>

例如在 Sales_data 成员函数中，this 的类型是 Sales_data \*const。 **尽管 this 是隐式的，但它仍然需要遵循初始化规则，意味着（在默认情况下）我们不能把 this 绑定到一个常量对象上。这一情况也就使得我们不能在一个常量对象上调用普通的成员函数。<br>**

如果 isbn 是一个普通函数而且 this 是一个普通的指针参数，则我们应该把 this 声明成 const Sales_data \*const。毕竟，在 isbn 的函数体内不会改变 this 所指的对象，所以把 this 设置为指向常量的指针有助于提高函数的灵活性。<br>

@允许把 const 关键字放在成员函数的参数列表之后，此时，紧跟在参数列表后面的 const 表示 this 是一个指向常量的指针。像这样，使用 const 成员函数被称作常量成员函数。<br>

@常量对象以及常量对象的引用或指针都只能调用常量成员函数<br>

### 类作用域和成员函数

类本身就是一个作用域

编译器分两步处理类：首先编译成员声明，然后才轮到成员函数体。因此成员函数体可以随意使用类的其他成员而无须在意这些成员出现。<br>

### 在类的外部定义成员函数

@如果成员被声明成常量成员函数，那么它的定义必须在参数列表后明确指定 const 属性。同时，类外部定义的成员的名字必须包含它所属的类名。

```cpp
double Sales_data::avg_price() const{

    if(unit_sold)

return revenue/units_sold;

else

return 0;

}
```

定义一个返回 this 对象的函数

```cpp
Sales_data& Sales_data::combine(const Sales_data &rhs){

units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上

revenue += rhs.revenue;

return *this;

}
```

调用 total.combine(trans);

total 的地址被绑定到隐式的 this 参数上，而 rhs 绑定到了 trans 上。<br>

@我们无须使用隐式的 this 指针访问函数调用者的某个成员，而是需要把调用函数的对象当成一个整体来访问：return \*this. return 语句解引用 this 指针以获得执行该函数的对象。调用返回 total 的引用。<br>

### 定义类相关的非成员函数

定义 read 和 print 函数

```cpp
istream &read(istream &is, Sales_data &item){

    double price = 0;

    is>>item.bookNo >> item.units_sold >> price;

    item.revenue = price*item.units_sold;

    return is;

}



ostream &print(ostream &os, const Sales_data &item){

    os<<item.isbn() << "" <<item.units_sold << "" <<item.revenue << "" <<item.avg_price();

    return os;

}
```

@read 和 print 分别接受一个各自 IO 类型的引用作为参数，这是因为 IO 类属于不能被拷贝的类型，因此我们只能通过引用来传递它们。而且因为读取和写入的操作会改变流的内容，所以两个函数接受的都是普通引用，而非常量引用。<br>

@print 函数不负责换行。<br>

### 定义 add 函数

add 函数接受两个 Sales_data 对象作为参数，返回值是一个新的 Sales_data 用于表示前两个对象的和

```cpp
Sales_data add(const Sales_data &lhs,const Sales_data &rhs){

    Sales_data sum = lhs;// 把lhs的数据成员拷贝给sum

    sum.combine(rhs);

    return sum;

};
```

### 构造函数

每个类都分别定义了它的对象被初始化的方式，类通过一个或几个特殊的成员函数来控制其对象的初始化过程，这些函数叫做构造函数。构造函数的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数。<br>

构造函数的名字和类名相同。和其他函数不一样的是，构造函数没有返回类型；除此之外类似其他的函数，构造函数也有一个可能为空的参数列表和一个可能为空的函数体。类可以包含多个构造函数，和其他重载函数差不多，不同的构造函数之间必须在参数数量或参数类型上有所区别。<br>

@不同于其他成员函数，构造函数不能被声明成 const 的。<br>

### 合成的默认构造函数

类中没有声明仍然可以正常执行，因为存在一个默认构造函数。如果我们没有显式声明，那么编译器会隐式给生成一个默认构造函数，规则@如果存在类内的初始值，用它来初始化成员，否则，默认初始化该成员。<br>

### 某些类不能依赖于合成的默认构造函数

@编译器只有发现类不包含任何构造函数，才会默认构造<br>

@对于某些类来说，合成默认构造函数可能执行错误的操作<br>

@编译器不能为某些类合成默认构造函数<br>

定义 Sales_data 的构造函数

```cpp
struct Sales_data{

     Sales_data () = default; //完全等同于之前使用的合成默认构造函数

     Sales_data(const std::string &s):bookNo(s){}

     Sales_data(const std::string &s,unsigned n, double p):bookNo(s),united_sold(n),revenue(p*n){}

     Sales_data(std::istream &);

     std::string isbn() const {return bookNo;}

     Sales_data & combine(const Sales_data&);

     double avg_price() const;

     std::string bookNo;

     unsigned units_sold = 0;

     double revenus = 0.0;

};
```

### 构造函数初始值列表

接下来我们介绍类中定义的另外两个构造函数

```cpp
Sales_data(const std::string &s):bookNo(s){}

Sales_data(const std::string &s, unsigned n, double p): bookNo(s),units_sold(n), revenue(p*n){}
```

我们把新出现的部分称为构造函数初始值列表 他负责为新创建的对象的一个或几个数据成员赋初值。构造函数初始值是成员名字的一个列表，每个名字后面紧跟括号括起来（或者在花括号内的）成员初始值。不同成员的初始化通过括号分隔开来。<br>

### 在类的外部定义构造函数

与其他几个构造函数不同，以 istream 为参数的构造函数需要执行一些实际操作。在它的函数体内，调用了 read 函数以给数据成员赋以初值：<br>

```cpp
Sales_data::Sales_data(std::stream &is){

     read(is,*this);//read函数的作用是从is中读取一条交易信息然后存入this对象

}
```

构造函数没有返回类型，所以上述定义从我们执行的函数名字开始。
<br>
在上例中，我们使用\*this 将"this"对象作为实参传递给 read 函数。<br>

### 拷贝、赋值和析构

除了定义类的对象如何初始化之外，类还需要控制拷贝、赋值和销毁对象时发生的行为。<br>

如果我们自己不定义这些操作，编译器将替我们合成它们。<br>

total = trans; => total.bookNo = trans.bookNo; etc<br>

某些类 不能依赖于合成的版本<br>

### 访问控制与封装

C++，使用了访问说明符加强类的封装性。<br>

@定义在 public 说明符之后的成员在整个程序内可被访问，public 成员定义类的接口<br>

@定义在 private 说明符之后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private 部分封装了（即隐藏了）类的实现细节。<br>

一个类可以包含 0 个或多个访问说明符，而且对于某个访问说明符能出现多少次没有严格的限定。<br>

### 使用 class 或 struct 关键字

实际上我们可以使用这两个关键字中的任何一个定义类。唯一的区别是，struct 和 class 的默认访问权限不一样。<br>

使用 struct，则定义第一个访问说明符之前的成员是 public 的；相反，使用 class 关键字，则这些成员是 private 的<br>

## 友元（friend）

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元（friend）。如果类想把一个函数作为它的友元，只需要添加一条以 friend 关键字开始的函数声明语句即可：<br>
```cpp
class Sales_data{

//为 sales_data 的非成员函数所做的友元声明

friend Sales_data add(const Sales_data&,const Sales_data&);

friend std::istream &read(std::istream&,Sales&);

}

//Sales_data 接口的非成员组成部分的声明

Sales_data add(const Sales_data&, const Sales_data&);
```
@友元不是类的成员也不受它所在区域访问控制级别的约束。<br>

### 友元的声明

友元的声明仅仅指定了访问的权限，而非一个通常意义上的函数声明。如果我们希望类的用户能和够调用某个友元函数，那么我们就必须在友元声明之外再专门对函数进行一次声明。<br>

### 类的其他特性

### 类成员再探
类型成员，类的成员的类内初始值、可变数据成员、内联成员函数、从成员函数返回\*this、关于如何定义并使用类类型以及友元类。<br>

为了展示这些特性，定义一个相互关联的类，分别是 Screen 和 Window_mgr<br>

@定义一个类型成员 & 成员函数<br>
```cpp
class Screen{

    public:

          typedef std::string::size_type pos; =>//using pos = std::string::size_type;

          Screen() = default;

          Screen(pos ht, pos wd,char c):height(ht),width(wd),contents(ht*wd,c){}

          char get() const {return contents[cursor];} //隐式内联

          inline char get(pos ht,pos wd) const;  //显式内联

          Screen &move(pos r,pos c);

    private:

          pos cursor = 0;

          pos height = 0, width = 0;

          std::string contents;

};
```
我们可以在类内部把 inline 作为声明的一部分显式地声明成员函数，同样地，也能在类的外部用 inline 关键字修饰函数的定义。<br>

### 重载成员函数

和非成员函数一样，成员函数也可以被重载，只要函数之间在参数数量和/或类型上有所区别就行。<br>

编译器根据实参的数量来决定运行哪个版本的函数。<br>

### 可变数据成员

能修改某个数据成员，即使是在一个 const 成员函数内。可以通过在变量的声明中加入 mutable 关键字做到这一点。<br>

@一个可变数据成员永远不会是 const，即使它是 const 对象的成员。<br>

```cpp
class Screen{

public:

    void some_member() const;

private:

    mutable size_t access_ctr; //即使在一个const对象内也能被修改
};

void Screen::some_member() const{

    ++access_ctr;

}
```

类数据成员的初始值

在 C++11 新标准中，最好的方式就是把这个默认值声明成一个类内初始值。

```cpp
class window_mgr{

private:

    std::vector<Screen> screens{Screen(24,80,' ')};

};
```

当我们初始化类类型的成员时，需要为构造函数传递一个符合成员类型的实参。

返回\*this 的成员函数

```cpp
class Screen{

public:

    Screen &set(char);

    Screen &set(pos,pos,char);

};

inline Screen &Screen::set(char){

contents[cursor] = c;

return *this;

}

inline Screen &Screen::set(pos r,pos col,char ch){

contents[r*width+col] = ch;

return *this;

}
```

和 move 操作一样，我们 set 成员的返回值是调用 set 的对象的引用。返回引用的函数的左值的，意味着这些函数返回的是对象本身而非对象的副本。<be>
myScreen.move(4,0).set('_');<=> myScreen.move(4,0); myScreen.set('_');//把光标移动到一个指定的位置，然后设置该位置的字符值<br>

这些操作将在同一个对象上执行。<br>

从 const 成员函数返回\*this<br>

添加一个 display 操作，显示一个 Screen，这个 display 并不需要改变它的内容，因此我们令 display 为一个 const 成员，此时，this 将是一个指向 const 的指针而\*this 是 const 对象。由此推断，display 的返回类型应该是 const Sales_data&。然而，如果真的令 display 返回一个 const 的引用，则我们将不能把 display 嵌入到一组动作的序列中去：<br>

```cpp
Screen myScreen;

myScreen.display(cout).set('*'); //常量引用无法调用普通成员函数
```

即使 myScreen 是个非常量对象，对 set 的调用也无法通过编译。问题在于 display 的 const 版本返回的是常量引用，而我们显然无权 set 一个常量对象。<br>

### 基于 const 的重载

@非常量版本的函数对于常量对象是不可用的，所以我们只能在一个常量对象上调用 const 成员函数。<br>
@可以在非常量对象上调用常量版本或非常量版本。<br>

```cpp
class Screen{

public:

Screen &display(std::ostream &os){do_display(os);return *this;}

const Screen &display(std::ostream &os) const {do_display(os);return *this;}

private:

void do_display(std::ostream &os) const {os<<contents;}

};
```

当一个成员调用另外一个成员时，this 指针在其中隐式地传递。<br>

因此，当 display 调用 do_display 时，它的 this 指针隐式地传递给 do_display。<br>

当 display 的非常量版本调用 do_display 时，它的 this 指针将隐式地从指向非常量的指针转换成指向常量的指针。<br>

当 do_display 完成后，display 函数个字返回解引用所得的对象。<br>

在非常量版本中，this 指向一个非常量对象，因此 display 返回一个普通的（非常量）引用；

而 const 成员则返回一个常量引用。<br>

### 类类型

每个类定义了唯一的类型。对于两个类来说，即使它们的成员完全一样，这两个类也是不同的类型。<br>

### 友元再探

@类可以把其他的类定义成友元，也可以把其他类的成员函数定义成友元。此外，友元函数能定义在类的内部，这样的函数是隐式内联的。<br>

类之间的友元关系

```cpp
class Screen{

friend class Window_mgr; //Window_mgr的成员可以访问Screen类的私有部分

}
```

如果一个类指定了友元类，则友元类的成员函数可以访问此类包括非公有成员在内的所有成员。<br>

```cpp
class Window_mgr{

public:

using ScreenIndex = std::vector<Screen>::size_type;

void clear(ScreenIndex);

private:

std::vector<Screen> screens{Screen(24,60,'')};

};

void window_mgr::clear(ScreenIndex i){

Screen &s = Screen[i];

s.contents = string(s.height*s.width, ' ');

}
```

如果 clear 不是 Screen 的友元，此时 clear 将不能访问 Screen 的 height、width 成员。而当 Screen 将 window_mgr 指定为其友元之后，Screen 的所有成员对于 window_mgr 就都变成可见的了。<br>

@友元关系不具有传递性<br>

**令成员函数作为友元。**<br>

@每个类负责控制自己的友元类或友元函数<br>

除了令整个 Window_mgr 作为友元之外，Screen 还可以只为 clear 提供访问权限。当把一个成员函数声明成友元时，我们必须明确指出该成员函数属于哪个类：<br>

```cpp
class Screen{

firend void Window_mgr::clear(ScreenIndex); // 向窗口添加一个Screen，返回它的编号

};

// 首先处理返回类型，之后我们才进入Window_mgr的作用域

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s){//要想使用ScreenIndex作为返回类型，我们必须明确指定哪个类定义了它。

screens.push_back(s);

return screens.size() - 1;

}
```

### 令某个成员函数作为友元

@首先定义 Window_mgr 类，其中声明 clear 函数，但是不能定义它。在 clear 使用 Screen 的成员之前必须先声明 Screen。<br>

@接下来定义 Screen，包括对于 clear 的友元声明<br>

@最后定义 clear，此时它才可以使用 Screen 的成员<br>

### 函数重载和友元

尽管重载函数的名字相同，但它们仍然是不同的函数。因此如果一个累想把一组重载函数声明成它的友元，它需要对这组函数中的每一个分别声明。<br>

### 友元声明和作用域

声明友元的类的成员调用该友元函数，该函数必须被声明过。<br>

### 类的作用域

每个类都会定义它自己的作用域<br>

作用域和定义在类外部的成员<br>

一个类就是一个作用域。<br>

名字查找与类的作用域<br>

@首先，在名字所在的块中寻找其声明语句，只考虑在名字的使用之前出现的声明。<br>

@如果没找到，继续查找外层作用域<br>

@如果最终没有找到匹配的声明，则程序报错<br>

@编译器处理完类中的全部声明之后才会处理成员函数的定义<br>

用于类成员声明的名字查找<br>

声明中使用的名字，包括返回类型或者参数列表中使用的名字，都必须在使用前确保可见。<br>

### 类型名要特殊处理

一般来讲，内层作用域可以重新定义外层作用域的名字，即使该名字已经在内层作用域中使用过。<br>

成员定义中的普通块作用域的名字查找<br>

@首先，在成员函数内功查找该名字的声明。只有在函数使用之前出现的声明才被考虑<br>

@如果在成员函数内没有找到，则在类内继续查找，这时类的所有成员都可以被考虑<br>

@如果类内也没有找到该名字的声明，在成员函数定义之前的作用域内继续查找<br>

类作用域之后，在外围的作用域中查找<br>

在文件中名字的出现处对其进行解析<br>

## 构造函数再探

对任何 C++的类来说，构造函数都是其中重要的组成部分。<br>

### 构造函数初始值列表

如果没有在构造函数的初始值列表中显式地初始化成员，则该成员将在构造函数体之前执行默认初始化。<br>

构造函数的初始值有时必不可少<br>

如果成员是 const 或者引用的话，必须将其初始化。<br>

```cpp
class ConstRef{

public:

ConstRef(int ii);

private:

int i;

const int ci;

int &ri;

};

//正确的显式地初始化引用和const成员

ConstRef::ConstRef(int ii):i(ii),ci(ii),ri(i){}
```

如果成员是 const、引用，或者属于某种未提供默认构造函数的类类型，我们必须通过构造函数初始值列表为这些成员提供初值。<br>

### 初始化和赋值

@前者直接初始化数据成员<br>

@后者先初始化后赋值<br>

构造函数初始值列表只说明用于初始化成员的值，而不限定初始化的具体顺序<br>

@最好令构造函数初始值的顺序与成员声明的顺序保持一致。而且如果可能的话，尽量避免使用某些成员初始化其他成员。<br>

### 委托构造函数

C++新标准扩展了构造函数初始值的功能，使得我们可以定义所谓的委托构造函数。<br>

一个委托构造函数使用它所属类的其他构造函数执行它自己的初始化过程，或者说它把它自己的一些（或者全部）职责委托给了其他构造函数。<br>

和其他构造函数一样，一个委托构造函数也有一个成员初始值的列表和一个函数体。在委托构造函数内，成员初始值列表只有一个唯一的入口，就是类名本身。和其他成员初始值一样，类名后面紧跟圆括号括起来的参数列表，参数列表必须与类中另外一个构造函数匹配。<br>

```cpp
class Sales_data{

public:

//非委托构造函数使用对应的实参初始化成员

Sales_data(std::string s, unsigned cnt, double price):bookNo(s),units_sold(cnt),revenue(cnt*price){}

//其余构造函数全都委托给另一个构造函数

Sales_data():Sales_data("",0,0){}

Sales_data(std::string s):Sales_data(s,0,0){}

Sales_data(std::istream &is):Sales_data(){read(is,*this);}

};
```

### 默认构造函数的作用

@当对象被默认初始化或值初始化时自动执行默认构造函数。<br>

默认初始化情况如下：<br>

！当我们在块作用域内不使用任何初始值定义一个非静态变量或者数组时<br>

！当一个类本身含有类类型的成员且使用合成的默认构造函数时。<br>

！当类类型的成员没有在构造函数初始值列表中显式地初始化时。<br>

值初始化情况如下：<br>

！在数组初始化的过程中如果我们提供的初始值数量少于数组的大小时。<br>

！当我们不使用初始值定义一个局部静态变量时<br>

！当我们通过书写形如 T（）的表达式显式地请求值初始化时，其中 T 是类型名（vector 的一个构造函数只接受一个实参用于说明 vector 大小，他就是使用一个这种形式的实参来对它的元素初始化器进行值初始化）。<br>

实际中，如果定义了其他构造函数，那么最好也提供一个默认构造函数<br>

使用默认构造函数

### 隐式的类类型转换

@能通过一个实参调用的构造函数定义了一条从构造函数的参数类型向类类型隐式转换的规则<br>

在 Sales_data 类中，接受 string 的构造函数和接受 istream 的构造函数分别定义了从这两种该类型向 Sales_data 隐式转换的规则。<br>

```cpp
string null_book = "9-999-99999-9";

item.combine(null_book);
```

只允许一步类类型转换<br>

编译器只会自动地执行一步类型转换<br>

抑制构造函数定义的隐式转换<br>

在要求隐式转换的程序上下文中，我们可以通过将构造函数声明为 explicit 加以阻止:<br>

```cpp
class Sales_data{

public:

Sales_data() = default;

Sales_data(const std::string &s, unsigned n,double p):bookNo(s),units_sold(n),revenue(p*n){}

explicit Sales_data(const std::string &s):bookNo(s){}

explicit Sales_data(std::istream&);

};
```

@explicit 关键字只允许出现在类内的构造函数声明处。<br>

explict 构造函数只能用于直接初始化<br>

发生隐式转换的一种情况是当我们执行拷贝形式的初始化时（使用=）。此时，我们只能使用直接初始化而不能使用**explicit 构造函数**。<br>

Sales_data item1(null_book); //正确<br>

Sales_data item2 = null_book; //错误，不能将 explicit 构造函数用于拷贝形式的初始化过程<br>

@当我们用 explicit 关键字声明构造函数时，它将只能以直接初始化的形式使用。而且，编译器将不会在自动转换过程中使用该构造函数<br>

为转换显式地使用构造函数

```cpp
item.combine(Sales_data(null_book)); //实参是一个显式构造的Sales_data对象

item.combine(static_cast<Sales_data>(cin)); //static_cast 可以使用explicit的构造函数
```

### 聚合类

聚合类使得用户可以直接访问其成员，并且具有特殊的初始化语法形式。当有一个类满足如下条件，我们可以说他是聚合的：

@所有成员都是 public<br>

@没有定义任何构造函数<br>

@没有类内初始值<br>

@没有基类，也没有 virtual 函数<br>

like this

```cpp
struct Data{

int ival;

string s;

};
```

可以提供一个花括号括起来的成员初始值列表，并用它初始化聚合类的数据成员：<br>

Data val1 = {0,"Anna"};

初始值的顺序必须与声明的一致。<br>

初始值列表的元素个数绝对不能超过类的成员数量<br>

### 字面值常量类

数据成员都是字面值类型的聚合类是字面值常量类。<br>

@数据成员都必须是字面值类型<br>

@类必须含有一个 constexpr 构造函数<br>

@如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式；或者如果成员属于某种类型，则初始值必须使用自己的 constexpr 构造函数<br>

@类必须使用析构函数的默认定义，该成员负责销毁类的对象<br>

### constexpr 构造函数

尽管构造函数不能是 const 的，但是字面值常量类的构造函数可以是 constexpr 函数，事实上，一个字面值常量类必须至少提供一个 constexpr 构造函数<br>

```cpp
class Debug{

public:

constexpr Debug(bool b=true):hw(b),io(b),other(b){}

constexpr Debug(bool h,bool i,bool o):...

constexpr bool any(){return hw||io||i=other;}

private:

bool hw;

bool io;

bool other;

};
```

### 类的静态成员

有时候类需要它的一些成员与类本身直接相关，而不是与类的各个对象保持关联。

### 声明静态成员

我们通过在成员的声明之前加上关键字 static 使得其与类关联在一起。和其他成员一样，静态成员可以是 public 的或 private 的。静态数据成员的类型可以是常量、引用、指针、类类型等<br>

举个栗子

```cpp
class Account{

public:

void calculate() {amount += amount *interestRate;}

static double rate() {return interestRate;}

static void rate(double);

private:

std::string owner;

double amount;

static double interestRate;

static double initRate();

};
```

@静态成员函数不能声明成 const 的，而且我们也不能在 static 函数体内使用 this 指针<br>

### 使用类的静态成员

```cpp
Account::rate() //作用域访问

Account ac1;

Account *ac2 = &ac1;

r = ac1.rate();

r = ac2->rate();
```

成员函数不用通过作用域运算符就能直接使用静态成员。<br>

### 定义静态成员

@﻿ 当在类的外部定义静态成员时，不能重复 static 关键字，该关键字只出现在类内部的声明语句<br>

@和类的所有成员一样，当我们指向类外部的静态成员时，必须指明成员所属的类名。static 关键字则只出现在类内部的声明语句中<br>

@一个静态数据成员只能定义一次<br>

@类似全局变量，静态数据成员定义在任何函数之外。因此一旦它被定义，就将一直存在与程序的整个生命周期中。<br>

```cpp
double Account::interestRate = initRate();
```

静态成员的类内初始化 //6.30

请期待下一篇，进阶，标准库的使用
