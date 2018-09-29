# 模版与泛型编程
面向对象编程（OOP）和泛型编程都能处理在编写程序时不知道类型的情况。不同之处在于：OOP能处理类型在程序运行之前都未知的情况（动态绑定）；而泛型编程中，在编译时就能获知类型了。<br>
其实，容器、迭代器和算法都是泛型编程的🌰 。当我们编写一个泛型程序时，是独立于任何特定类型来编写代码的。**当使用一个泛型程序时，我们提供类型或值，程序实例可在其上运行。** <br>
例如，标准库为每个容器提供了单一的、泛型的定义，如vector。我们可以使用这个泛型的定义来定义很多类型的vector，它们的差异就在于包含的元素类型不同。<br>
**模版是泛型编程的基础。**<br>

模版是C++中泛型编程的基础。一个模版就是一个创建类或函数的蓝图或者说公式。当使用一个vector这样的泛型类型，或者find这样的泛型函数时，我们提供足够的信息，**将蓝图转换为特定的类或函数** 。**这种转换发生在编译时**。<br>
### 定义模版
#### 1. 函数模版
定义一个通用的 **函数模版(function template)** ,而不是每个类型都定义一个新函数。一个函数模版就是一个公式，可用来生成针对特定类型的函数版本。
```cpp
template <typename T> int compare(const T &v1, const T &v2){
  ...
}
```
模版定义以关键字template开始，后面跟一个 **模版参数列表(template parameter list)**，这是一个逗号分割的一个或多个 **模版参数(template parameter)** 的列表，用<>包围起来。<br>
📒 模版参数列表不能为空<br>
模版参数列表的作用很像函数参数列表。函数参数列表定义了若干特定类型的局部变量，但并未指出如何初始化它们。 **在运行时，调用者提供实参来初始化形参。**<br>
##### 实例化函数模版
当我们调用一个函数模版时，编译器（通常）用函数实参来为我们推断模版实参。即，当我们调用compare时，编译器使用实参的类型来确定绑定到模版参数T的类型。
```cpp
cout << compare(1,0) << endl; // T 为int
vector<int> vec1{1,2,3}, vec2{3,4,5};
cout << compare(vec1, vec2) << endl; // T 为vector<int>
```
##### 模版类型参数
我们的compare函数有一个模版 **类型参数（type parameter）**。一般来说，我们可以将类型参数看作类型说明符，就像内置类型或类类型说明符一样使用。特别是，类型参数可以用来指定返回类型或函数的参数类型，以及在函数体内用于变量声明或类型转换：
```cpp
// ⭕️ 返回类型和参数类型相同
template <typename T> T foo(T* p){
  T tmp = *p; // tmp 的类型将是指针p指向的类型
  // ...
  return tmp;
}
```
类型参数前必须使用关键字class或typename：
```cpp
// ⭕️ 在模版参数列表中，typename和class没有什么不同
template<typename T, class U> calc(const T&, const U&);
```
##### 非类型模版参数
除了定义类型参数，还可以在模板中定义 **非类型参数(nontype parameter)**。一个非类型参数表示一个值而非一个类型。我们通过一个特定的类型名而非关键字class或typename来指定非类型参数。
```cpp
template<unsigned N,unsigned M> int compare(const char (&p1)[N], const char (&p2)[M]){ // 不能拷贝数组，所以我们将参数定义为数组的引用。
  return strcmp(p1,p2);
}
```
调用`compare("h1","mom")`<br>
编译器会使用字面常量的大小来代替N和M，从而实例化模版。记住编译器会在一个字符串字面常量的末尾插入一个空字符作为终结符，因此得到如下版本<br>
`int compare(const char (&p1)[3], const char (&p2)[4])`<br>
一个非类型参数可以是一个整型，或者是一个指向对象或函数类型的指针或（左值）引用。绑定到非类型整型参数的实参必须是一个 **常量表达式** 。**绑定到指针或引用非类型参数的实参必须具有静态的生存期** 。<br>
我们 **不能** 用一个普通（非static）局部变量或动态对象作为指针或引用非类型模版参数的实参。指针参数也可以用nullptr或一个值为0的常量表达式来实例化。<br>
在模版定义内，模版非类型参数是一个常量值。在需要常量表达式的地方，可以使用非类型参数。例如，指定数组大小。<br>
📒 非类型模版参数的模版实参必须是常量表达式。
##### inline和constexpr的函数模版
函数模版可以声明为inline或constexpr的，如同非模版函数一样。inline或constexpr说明符放在模版参数列表之后，返回类型之前：
```cpp
// ⭕️ inline说明符跟在模版参数列表之后
template<typename T> inline T min(const T&, const T&);
```
##### 编写类型无关的代码
compare函数说明
* 模版中的函数参数是const的引用。
* 函数体中的条件判断仅使用<比较运算。
使用引用，可用于可拷贝的，不可拷贝的。<br>
关心类型无关和可移植性，可以使用less代替<>运算符
```cpp
// 即使用于指针也正确的compare版本
template <typename T> int compare(const T &v1, const T &v2){
  if(less<T>() (v1,v2)) return -1;
  if(less<T>() (v2,v1)) return 1;
  return 0;
}
```
👨 模版程序应该尽量减少对实参类型的要求<br>
##### 模版编译
当编译器遇到一个模版定义时，它并不生成代码。只有当我们实例化模版的一个特定版本时，编译器才会生成代码。当我们使用（而不是定义）模版时，编译器才会生成代码，这一特性影响了我们如何组织代码以及错误何时被检测到。<br>
通常，当我们调用一个函数时，编译器只需要掌握函数的声明。<br>
📒 函数模板和类模版成员函数的定义通常放在头文件中。<br>
**关键概念：模版和头文件** <br>
模版包含两种名字：
* 那些不依赖于模版参数的名字 // 使用模版时，名字可见
* 那些依赖于模版参数的名字 //
##### 大多数编译错误在实例化期间报告
模版直到实例化时才会生成代码，这一特性影响了我们何时才会获知模版内代码的编译错误。分别在三个阶段<br>
一、编译模版本身时<br>
二、编译器遇到模版使用时。<br>
三、模版实例化时，只有这个阶段才能发现类型相关的错误。<br>
⚠️ 保证传递给模版的实参支持模版所要求的操作，以及这些操作在模版中能正确工作，是调用者的责任。<br>
> ❓ 实例化的定义
>> 当编译器实例化一个模版时，它使用实际的模版参数代替对应的模版参数来创建出模版的一个新“实例”。<br>

> ❓ 编写行为类似标准库 find 算法的模版。函数需要两个模版类型参数，一个表示函数的迭代器参数，另一个表示值的类型。使用你的函数在一个 vector 和一个list中查找给定值。<br>
```cpp
template<typename Iterator, typename Value> Iterator find(Iterator first, Iterator last, const Value& v){
  for ( ; first != last && *first != value; ++first);
	return first;
}
```
> ❓ 为6.2.4节中的print函数编写模版版本，它接受一个数组的引用，能处理任意大小、任意元素类型的数组。
```cpp
template<typename Array>
void print(const Array& arr)
{
	for (const auto& elem : arr)
		std::cout << elem << std::endl;
}
```
> ❓编写一个 constexpr 模版，返回给定数组的大小。
```cpp
template<typename T, typename N> constexpr unsigned size(const T (&arr)[N]){
  return N;
}
```
#### 类模版
