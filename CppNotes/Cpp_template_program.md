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
**类模版（class template）** 是用来生成类的蓝图。与函数模版不同之处是，编译器不能为类模版推断模版参数类型。为了使用类模版，我们必须在模版名后的尖括号中提供额外信息---用来代替模版参数的模版实参列表。<br>
##### 定义类模版
🌰 实现之前的StrBlob的模版版本。并命名为Blob，意指它不再针对string。模版会提供对元素的共享（且核查过的）访问能力。
```cpp
template <typename T> class Blob{
  public:
      typedef T value_type;
      typedef typename std::vector<T>::size_type size_type;
      // 构造函数
      Blob();
      Blob(std::initializer_list<T> il);
      // Blob 中的元素数目
      size_type size() const { return data->size(); }
      bool empty() const { return data->empty(); }
      // 添加和删除元素
      void push_back(const T &t) { data->empty(); }
      // 移动版本
      void push_back(T &t) {data->push_back(std::move(t)); }
      void pop_back();
      // 元素访问
      T& back();
      T& operator[](size_type i); // 下标运算
      private:
      std::shared_ptr<std::vector<T>> data;
      // 若data[i] 无效，则抛出msg
      void check(size_type i, const std::string &msg) const;
      };
```
##### 实例化类模版
当使用一个类模版时，我们必须提供额外信息。额外信息是 **显式模版实参（eplicit template argument）**列表，它们被绑定到模版参数，编译器使用这些模版实参来实例化出特定的类。<br>
🌰 
```cpp
Blob<int> ia;    // 空Blob<int>
Blob<int> ia2 = {0,1,2,3,4};  // 有5个元素的Blob<int>
```
编译器会实例化出一个与下面定义等价的类
```cpp
template<> class Blob<int>{
  typedef typename std::vector<int>::size_type size_type;
  Blob();
  Blob(std::initializer_list<int> il);
  // ..
  int& operator[](size_type i);
  ...
}
```
对我们指定的每一种元素类型，编译器都会生成一个不同的类（独立的类）。<br>
```cpp
Blob<string> names;
Blob<double> prices;
```
##### 在模版作用域中引用模版类型
类模版的名字不是一个类型名。类模版用来实例化类型，而一个实例化的类型总是包含模版参数的。<br>
一个类模版中的代码如果使用了另一个模版，通常不将一个实际类型（或值）的名字用作其模版实参。相反的，我们通常将模版自己的参数当作被使用模版的实参。例如，我们的data成员使用两个模版，vector和shared_ptr。我们知道，无论何时使用模版都必须提供模版实参。
```cpp
std::shared_ptr<std::vector<T>> data;
```
实例化就成
```cpp
shared_ptr<vector<string>> data;
```
##### 类模版的成员函数
与其他类相同，我们既可以在类模版内部，也可以在类模版外部为其定义成员函数，且定义在类模版内的成员函数被隐式地声明为内联函数。<br>
类模版的成员函数本身是一个普通函数。但是类模版的每个实例都有其自己版本的成员函数。因此，类模版的成员函数具有和模版相同的模版参数。<br>
```cpp
ret-type StrBlob::member-name(parm-list);
template <typename T> ret-type Blob<T>::member-name(parm-list);
```
##### check和元素访问成员
定义一个check成员
```cpp
template <typename T> void Blob<T>::check(size_type i, const std::string &msg) const{
  if(i>=data->size())
      throw std::out_of_range(msg);
}
```
下标运算符和back函数用模版参数指出返回类型
```cpp
template <typename T> T& Blob<T>::back(){
  check(0,"back on empty Blob");
  return data->back();
}
template <typename T> T& Blon<T>::operator[](size_type i){
  // 如果i太大，check会抛出异常，阻止访问一个不存在的元素
  check(i,"subscript out of range");
  return (*data)[i];
}
```
在原StrBlob类中，这些运算符返回string&。而模版版本则返回一个引用，指向用来实例化Blob的类型。<br>
pop_back函数
```cpp
template <typename T> void Blob<T>::pop_back(){
  check(0,"pop_back on empty Blob");
  data->pop_back;
}
```
##### Blob构造函数
```cpp
template <typename T> Blob<T>::Blob():data(std::make_shared<std::vector<T>>()){

}
```
类似的，接受一个initializer_list参数的构造函数将其类型参数T作为initializer_list参数的元素类型。
```cpp
template<typename T> Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>> (il)){}
```
类似默认构造函数，此构造函数分配一个新的vector。<br>
```cpp
Blob<string> articles = {"a","b","c"};
```
##### 类模版成员函数实例化
默认情况下，一个类模版的成员函数只有当程序用到它时才进行实例化
```cpp
// 实例化Blob<int> 和接受initializer_list<int> 的构造函数
Blob<int> squares = {1,2,3,4,5,6,7,8,9,0};
// 实例化Blob<int>::size() const
...
```
##### 在类代码内简化模版类名的使用
当我们使用一个类模版类型时必须提供模版实参，但这一规则有一个例外。在类模版的作用域中，我们可以直接使用模版名而不提供实参。<br>
```cpp
// 若试图访问一个不存在的元素，BlobPtr抛出一个异常
template <typename T> class BlobPtr{
  public:
  BlobPtr():curr(0){ }
  BlobPtr(Blob<T> &a,size_t sz=0):wptr(a.data),curr(sz){}
  T& operator*() const{ auto p = check(curr, "deference past end");
  return (*p)[curr]; //  ( *p) 为本对象指向的vector
  }
  ...
}
```
##### 在类模版外使用类模版名
当我们在类模版外定义其成员时，必须记住，我们并不在类的作用域中，直到遇到类名才表示进入类的作用域。
```cpp
// 后置：递增/递减对象但返回原值
template <typename T> BlobPtr<T> BlobPtr<T>::operator++(int){
  // 此处无须检查；调用前置递增时会进行检查
  BlobPtr ret = *this; // 保存当前值
  ++*this; // 推进一个元素；前置++检查递增是否合法。
  return ret; // 返回保存的状态
}
```
由于返回类型位于类的作用域之外，我们必须指出返回类型是一个实例化的BlobPtr，它所用类型与类实例化所用类型一致。在函数体内，我们已经进入类的作用域，因此在定义ret时无须重复模版实参。如果不提供模版实参，则编译器将假定我们使用的类型与成员实例化所用类型一致。因此，ret的定义与如下代码等价：
```cpp
BlobPtr<T> ret = *this;
```
📒 在一个类模版的作用域内，我们可以直接使用模版名而不必指定模版实参。<br>
##### 类模版和友元
当一个类包含一个友元声明时， **类与友元各自是否是模版是相互无关的**。a. 如果一个类模版包含一个非模版友元，则友元被授权可以访问所有模版实例。b. 如果友元自身是模版，类可以授权给所有友元模版实例，也可以只授权给特定实例。<br>
##### 一对一友好关系
类模版与另一个（类或函数）模版间友好关系的最常见的形式是建立对应实例及其友元间的友好关系。例如，我们的Blob类应该将BlobPtr类和一个模版版本的Blob相等运算符定义为友元。<br>
为了引用（类或函数）模版的一个特定实例，我们必须首先声明模版自身。一个模版声明包括模版参数列表：
```cpp
// 前置声明，在Blob中声明友元所需要的
template <typename> class BlobPtr; 
template <typename> class Blob; // 运算符==中的参数所需要的
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> class Blob{
  // 每个Blob实例将访问权限授予相同类型实例化的BlobPtr和相等运算符
  friend class BlobPtr<T>;
  friend bool operator==<T> (const Blob<T>&, const Blob<T>&);
  ...
} 
```
我们首先将Blob、BlobPtr和operator==声明为模版。这些声明是operator==函数的参数声明以及Blob中的友元声明所需要的。<br>
友元的声明用Blob的模版形参作为它们自己的模版实参。
```cpp
Blob<char> ca; // BlobPtr<char>和operator==<char>都是本对象的友元
```
BlobPtr<char> 的成员可以访问ca（或任何其他Blob<char>对象）的非public部分，但ca对ia（或任何其他Blob<int>对象）或Blob的任何其他实例都没有特殊访问权限。<br>
##### 通用和特定的模版友好关系
一个类也可以将另一个模版的每个实例都声明为自己的友元，或者限定特定的实例为友元：
```cpp
// 前置声明，在将模版的一个特定实例声明为友元时要用到
template <typename T> class Pal;
class C{ // C是一个普通的非模版类
    friend class Pal<C>; // 用类C实例化的Pal是C的一个友元
    // Pal2的所有实例都是C的友元；这种情况无须前置声明
    template <typename T> friend class Pal2;
};
template <typename T> class C2{ // C2本身是一个类模版
    // C2的每个实例将相同实例化的Pal声明为友元
    friend class Pal<T>; // Pal的模版声明必须在作用域之内
    // Pal2的所有实例都是C2的每个实例的友元，不需要前置声明
    template <typename X> friend class Pal2;
    // Pal3是一个非模版类，它是C2所有实例的友元
    friend class Pal3; // 不需要Pal3的前置声明
}
```
为了让所有实例成员友元，友元声明中必须使用与类模版本身不同的模版参数。<br>
##### 令模版自己的类型参数成为友元
```cpp
template <typename T> class Bar{
  friend T; // 将访问权限授予用来实例化Bar的类型
  ...
}
```
##### 模版类型别名
```cpp
typedef Blob<string> StrBlob;
```
新标准允许我们为类模版定义一个类型别名
```cpp
template<typename T> using twin = pair<T,T>;
twin<string> authors; // authors是一个pair<string,string>
```
一个模版类型别名是一族类的别名
```cpp
twin<int> win_loss;  // win_loss是一个pair<int,int>
```
当我们定义一个模版类型别名时，可以固定一个或多个模版参数
```cpp
template <typename T> using partNo = pair<T,unsigned>;
partNo<string> books; // books 是一个pair<string,unsigned>
partNo<Vehicle> cars; // cars是一个pair<Vehicle,unsigned>
partNo<Student> kids; // kids是一个pair<Student, unsigned>
```
first，second<br>
##### 类模版的static成员
```cpp
template <typename T> class Foo{
  public:
     static std::size_t count(){ return ctr; }
     // 其他接口成员
  private:
     static std::size_t ctr;
     // 其他实现成员
}
```
```cpp
Foo<string> fs;
Foo<int> fi,fi2,fi3;
```
每个Foo实例都有自己的static成员实例。模版类中的每个static数据成员必须有且仅有一个定义。但是，**类模版的每个实例都有一个独有的static对象**。因此，与定义模版的成员函数类似，我们将static数据成员也定义为模版<br>
```cpp
template <typename T> size_t Foo<T>::ctr = 0; // 定义并初始化ctr
```
与非模版类的静态成员相同，我们可以通过类类型对象来访问一个类模版的static成员，也可以使用作用域运算符直接访问成员。
```cpp
Foo<int> fi; // 实例化Foo<int>类和static数据成员ctr
auto ct = Foo<int>::count(); // 实例化Foo<int>::count
ct = fi.count(); // 使用Foo<int>::count
ct = Foo::count(); // ❌ 不知道使用那个？
```
一个static成员函数只有在使用时才会实例化。
函数模版 `template <typename T> T functionName(){}`<br>
类模版 `template <typename T> class className{}`<br>
#### 模版参数
##### 模版参数与作用域
模版参数遵循普通的作用域规则。一个模版参数名的可用范围是其声明之后，至模版声明或定义结束之前。与任何其他名字一样，模版参数会隐藏外层作用域中声明的相同名字。<br>
```cpp
typedef double A;
template <typename A, typename B> void f(A a,B b){
  A tmp = a; // tmp的类型为模版参数A的类型，而非double
  double B; // ❌ 重声明模版参数B
}
```
正常的名字隐藏规则决定了A的typedef被类型参数A隐藏。因此，tmp不是一个double，其类型是使用f时绑定到类型参数A的类型。
##### 模版声明
模版声明必须包含模版参数
```cpp
template <typename T> int compare(const T&, const T&);
template <typename T> class Blob;
```
三个calc都指向相同的函数模版
```cpp
template <typename T> T calc(const T&, const T&);
...
```
##### 使用类的类型成员
:: 作用域运算符<br>
告诉编译器是一个类型 typename
```cpp
template <typename T> typename T::value_type top(const T& c){
  if(!c.empty())
      return c.back();
  else
      return typename T::value_type();
}
```
typename 指明其返回类型并在c中没有元素时生成一个值初始化的元素返回给调用者。<br>
##### 默认模版实参
只有当它右侧所有参数都有默认实参时，它才可以有默认实参。<br>
```cpp
template <typename T, typename F = less<T>> int compare(const T &v1, const T &v2, F f = F()){
  ...
}
bool i = compare(0,42); // 使用less；i为-1
Sales_Data item1(cin), item2(cin);
bool j = compare(item1,item2,compareIsbn);
```
##### 模版默认实参与类模版
尖括号指出类必须从一个模版实例化而来。<br>
特别是，如果一个类模版为其所有模版参数都提供了默认实参。且我们希望使用这些默认实参，就必须在模版名之后跟一个空尖括号对：
```cpp
template <class T = int> class Numbers{
  public:
      Numbers(T v = 0):val(v){}
      // 对数值的各种操作
  private:
     T val; 
};
Numbers<long double> lots_of_precision;
Numbers<> averages_precision; // 空<>表示我们希望使用默认类型
```
#### 成员模版
一个类（无论是普通类还是类模版）可以包含本身是模版的成员函数。这种成员被称为 **成员模版(member template)**
##### 普通（非模版）类的成员模版
```cpp
// 函数对象类，对给定指针执行delete
class DebugDelete{
  public:
      DebugDelete(std::ostream &s = std::cerr):os(s){
        // 与任何函数模版相同，T的类型由比编译器推断
        template <typename T> void operator()(T* p) const{
          os<< "deletint unique_ptr" << std::endl;
          delete p;
        }
  private:
      std::ostream &os;
      }
};
```
##### 类模版的成员函数
对于类模版，我们也可以为其定义成员模版。在此情况下，类和成员各自有自己的、独立的模版参数。<br>
```cpp
template <typename T> class Blob{
  template <typename It> Blob(It b,It e);
  // ...
}
```
希望支持不同类型序列的迭代器，因此将构造函数定义为模版。<br>
成员模版是函数模版。<br>
```cpp
template <typename T> template <typename It> Blob<T>::Blob(It b,It e):data(std::make_shared<std::vector<T>>(b,e)){}
```
##### 实例化与成员模版
为了实例化一个类模版的成员模版，我们必须同时提供类和函数模版的实参。<br>
```cpp
int ia[] = {1,2,3,4,5,6,7};
vector<long> vi = {0,1,2,3,4,5,6,7};
list<const char*> w = {"now","is","the","time"};
// 实例化Blob<int> 类及其接受两个int*参数的构造函数
Blob<int> a1(begin(ia),end(ia)); // 构造函数自己实例化推断结果为int*    Blob<int>::Blob(int*,int*);
...
```
#### 控制实例化
显式实例化
```cpp
extern template declaration; // 实例化声明
template declaration; // 实例化定义
```
declaration 是一个类或函数声明，其中所有模版参数已被替换为模版实参
```cpp
extern template class Blob<string>;  // 声明
template int compare(const int&, const int&); // 定义
```
由于编译器在使用一个模版时自动对其实例化，因此extern声明必须出现在任何使用此实例化版本的代码之前<br>
⚠️ 对每个实例化声明，在程序中的某个位置必须有其显式的实例化定义。<br>
##### 实例化定义会实例化所有成员
📒 在一个类模版的实例化定义中，所用类型必须能用于模版的所有成员函数。<br>
#### 效率与灵活性
删除器。
##### 在运行时绑定删除器
shared_ptr，必须能直接访问其删除器。即，删除器必须保存为一个指针或一个封装了的指针的类。<br>
reset可以赋予此shared_ptr另一种类型的删除器。通常，类成员的类型在运行时是不能改变的。因此，不能直接保存删除器。<br>
```cpp
// del的值只有在运行时才知道；通过一个指针来调用它
del?:del(p):delete p; // del(p)需要运行时跳转del的地址
```
##### 在编译时绑定删除器
unique_ptr    `del(p)`
### 模版实参推断

cpp primer 2018102 finish 600page by trans<br>
接下来是实践的时刻！😂 


