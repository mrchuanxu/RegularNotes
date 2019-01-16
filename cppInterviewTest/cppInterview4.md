## 什么是智能指针？为什么要用智能指针？如何打破循环引用的问题？实现一个智能指针呗！对于资源管理有什么作用？
原文再续就书接上一回。<br>
看到这些问题，心里就发毛。什么是智能指针啊？为什么要用智能指针啊？循环引用又是什么鬼？实现？我❌...<br>
### 首先我们来看一下第一个问题，什么是智能指针？
常见的智能指针有几种，一种是共享指针shared_ptr，一种是独享指针unique_ptr，一种是弱指针weak_ptr，一种是很久没用过的auto_ptr(被unique_ptr替代了)。<br>
智能指针也是指针，它也属于指针的范畴，但是它比一般的指针智能，说明了是智能指针，肯定就智能一点。就像现在的智能家居跟普通家居的区别。那么它到底智能到什么程度呢？我们知道，动态内存，也就是我们平常在堆中申请内存的时候，要是我们用了指针，如下<br>
```cpp
T *p = new T();
delete p;
```
就需要进行管理，例如delete，`delete和new`是一对操作，`delete[]和new[]`他两都是一对cp出现，来虐程序员这群单身汪🐶。new这样的操作就是为对象分配空间并返回一个指向该对象的指针。所以返回了一个指针，那么我们就需要管理这个指针，delete就是接受一个动态对象的指针，销毁该对象(调用析构函数，除了内置类型不做处理)，并释放与之关联的内存。<br>
你让一个单身🐶去管理？这不闹着玩吗？<-_<-! 在动态内存的使用，比较容易出现问题，一旦忘记了delete或者在不正确的时间做了不正确的事情，或者在不正确的时间做了正确的事情，那也是不正确，或者在正确的时间做了不正确的事情，就容易发生内存泄漏。哪能怎么办？<br>
所以 **标准库**(记住是标准库提供的)，定义在头文件`<memory>`，提供了智能指针，这为了建设和谐美好社会，贡献了不少。<br>
智能指针行为类似于常规的指针，这里只是类似，因为智能指针会负责自动释放所指向的对象。（其实就是让cp滚远点🐶🐶🐶）<br>
而且指针并不能指出谁拥有了对象，不知道谁拥有所有权，但是智能指针却拥有所有权。<br>
### 一个人的独享，感觉拥有了全世界(unique_ptr独享指针)
```cpp
    unique_ptr<string> p1(new string("hi,world")); // 必须采用直接初始化的形式初始化
    unique_ptr<string> p2(p1); // ❌ 不支持拷贝
    unique_ptr<string> p3;
    p3 = p2; // ❌ 不支持赋值
```
上面的代码，是不是让unique_ptr感觉很适然，我的东西是我的，你不能留副本，仅此一件。他表示的是互斥所有权。一般的指针都支持拷贝赋值操作，但是这里他就把拷贝构造函数和拷贝赋值运算符都`private`了，根本不让你拷贝。<br>
* 一个unique_ptr“拥有”一个对象(它所指向的)，某一个时刻，只能有一个unique_ptr指向一个给定的对象。当unique_ptr被销毁，所指向的对象也被销毁。<br>
* unique_ptr不能拷贝，不能赋值，可以移动(p.release())
```cpp
unique_ptr<string> p1(new string("hi"));
unique_ptr<string> p2(p1.release()); // 将p1置为空，返回指针
cout << *p2 << endl;
unique_ptr<string> p3(new string("hello,world"));
p2.reset(p3.release()); // reset释放了p2原来指向的内存 然后令p2指向p3所指向的对象，然后release()将p3置为空
cout << *p3 << endl; // 输出的都是hi
cout << *p1 << endl; // p1已经被释放了，没有了
```
那么他那么多限制，在标准库的实现又是怎样的呢？来看看下面这一段
```cpp
template<typename T,typename D = default_delete<T> > // default_delete是一个无状态类
class unique_ptr{
    public:
        using pointer = ptr;
        using element_type = T;
        using deleter_type = D;
        constexpr unique_ptr() noexcept;
        constexpr unique_ptr(nullptr_t) noexcept:unique_ptr(){} // 空指针类型
        explicit unique_ptr(pointer p) noexcept; // from pointer
        unique_ptr(pointer p,typename conditional<is_reference<D>::value,D,const D&> del) noexcept; // lvalue
        unique_ptr(pointer p,typename remove_reference<D>::type&& del) noexcept; // rvalue
        unique_ptr(unique_ptr&& x) noexcept;// 右值 移动构造函数
        template<class U,class E>
            unique_ptr(unique_ptr<U,E>&& x)noexcept; // 特例化
        template<class U>
            unique_ptr(auto_ptr<U>&& x)noexcept; // 不抛出异常
        Unique_ptr(const unique_ptr&) = delete; // 不允许拷贝

        unique_ptr& operator=(unique_ptr&& x) noexcept; // 移动赋值运算
        unique_ptr& operator=(nullptr_t) noexcept; // 空指针类型
        template<class U,class E>
            unique_ptr& operator=(unique_ptr<U,E>&& x)noexcept; // 强制类型转换
        unique_ptr& operator=(const unique_ptr&) = delete; // 不允许赋值
};
```
为了不抛出异常，都设置了noexpect，以上包括了右值引用操作，左值引用操作，以及某一构造函数特例化操作。基本囊括而且也解释了为什么不拷贝不赋值。<br>
**release()和reset()** 这两个函数都是将指针的所有权从一个(非const)unique_ptr转移给另一个unique_ptr。<br>
reset()还能好一点，可以释放内存，但是release()就不行了，release()必须有 **接盘侠**，接了要么可以自动负责释放，要么负责手动释放。<br>
接下来我们看看这两个的实现方式<br>
```cpp
void reset(pointer p = pointer()) noexcept;
// 这里有一个默认值
pointer release() noexcept;
// 这里返回一个值
```
release()是返回一个pointer，所以说它需要一个接盘侠。<br>
* unique_ptr 保存一个指针，当他自身被销毁时(例如线程控制流离开unique_ptr的作用域)，使用关联的释放器(deleter)释放所指向的对象<br>
释放器又是什么呢？当一个unique_ptr被销毁，就会调用其自己的释放器销毁所拥有的对象。
```cpp
deleter_type& get_deleter() noexcept;
const deleter_type& get_deleter() const noexcept;
```
1. 局部变量的释放器应该啥也不干<br>
2. 内存池应该将对象归还给内存池，是否销毁它依赖于内存池如何定义。<br>
3. 默认调用delete释放它所指向的对象<br>
管理释放器又分为在运行时绑定和在编译时绑定，这两个区别适用于区别shared_ptr和unique_ptr的，下面讲完shared_ptr会统一讲解，现在只要记住，unique_ptr管理释放器时编译时绑定的。<br>
那怎么传递释放器呢？我们来看一个🌰
```cpp
#include <memory>
#include <iostream>
#include <string>
using namespace std;

class Role{
    public:
        Role(const string &crole):role(crole){
            cout << role << endl;
        }
        ~Role(){
            cout << "delete" << endl;
        }
        void delRole(){
            cout << "delete Role outside" << endl;
        }
    private:
        string role;
};

void outdelRole(Role *r){
    r->delRole();
}

int main(){
    unique_ptr<Role,decltype(outdelRole)*> p1(new Role("trans"),outdelRole);
    return 0;
}
```
输出trans
delete Role outside<br>
这个🌰，充分说明了，我们可以重载释放器，如果是函数的释放器，那么他的参数类型必须是一个objT类型的指针，这样才有删除的意义。decltype是一般用来指明类型的
```cpp
unique_ptr<objT,delT>p(new objT,fcn); // fcn是delT类型对象
```
这样你想怎么删，删什么就由你自个儿来定了。<br>
也可以这样做
```cpp
#include <iostream>
#include <memory>
using namespace std;
class state_deleter {  // a deleter class with state
  int count_;
public:
  state_deleter() : count_(0) {}
  template <class T>
  void operator()(T* p) {
    cout << "[deleted #" << ++count_ << "]\n";
    delete p;
  }
};

state_deleter del;
unique_ptr<int,state_deleter> alpha (new int);
unique_ptr<int,state_deleter> beta (new int,alpha.get_deleter());

// gamma and delta share the deleter "del" (deleter type is a reference!):
unique_ptr<int,state_deleter&> gamma (new int,del);
unique_ptr<int,state_deleter&> delta (new int,gamma.get_deleter());
```
再来看一段比较陷阱的代码
```cpp
unique_ptr<string> p1;
cout << *p1 << endl;
```
这段代码代表p1是一个空指针，那这个空指针，没有指向一个对象，那下面这一段呢？
```cpp
unique_ptr<string> p1();
cout << *p1 << endl;
```
输出的是1，为什么呢？因为`unique_ptr<string> p1()`声明一个无参函数p1，返回的类型是string，所以要是*p1，那只能是1，他是一个函数体<br>
#### 用途
* 为动态分配的内存提供异常安全<br>
unique_ptr可以理解为一个简单的指针(指向一个对象)或一对指针(包含释放器deleter的情况)<br>
* 将动态分配内存的所有权传递给函数<br>
* 从函数返回动态分配的内存<br>
* 从容器中保存指针<br>
⚠️这里有一个get()的用法
```cpp
pointer get() const noexcept;
```
get()是托管一个对象得指针或者空指针
```cpp
unique_ptr<string> p1(new string("hello world"));
string *pstr = p1.get();
cout << *pstr << endl;
```
他与release()不同，它只是托管，get并是将pstr指向了p1指向的对象，但是并没有释放p1的内存，pstr并没有获取到这个智能指针的所有权，只是得到了它的对象。p1还是需要在某个时刻删除托管数据pstr。<br>
再来看一下解引用运算符
```cpp
typename add_lvalue_reference<element_type>::type operator*() const;
```
作用支持指针操作呗
```cpp
unique_ptr<string> p1(new string("hello world"));
cout << *p1 << endl;
```
再看看->运算符
```cpp
pointer operator->()const noexcept;
```
支持指针行为的操作
```cpp
  unique_ptr<C> foo (new C);
  unique_ptr<C> bar;

  foo->a = 10;
  foo->b = 20;

  bar = std::move(foo); // 支持右值移动操作 foo就释放了
```
那好，我们知道整个unique_ptr都会支持指针的行为，那我们看看它的特例化版本。什么是特例化？就是对于特别的🌰进行特别的处理。不同的版本
```cpp
template<class T,class D> class unique_ptr<T[],D>;
```
```cpp
// 用于内置函数
unique_ptr<int[]> make_sequence(int n){
    unique_ptr<int[]> p{new int[n]};
    for(int i = 0;i<n;++i)
        p[i] = i;
    return p; // 返回局部对象
}
```
这里当然要新增加独一[]运算符的作用，也就是重载 []运算符。<br>
```cpp
element_type& operator[](size_t i)const;
```
不同担心匹配问题，我们提供特例化版本只是帮编译器做了匹配的工作而已。<br>
那交换指针？交换也是移动操作呀！
```cpp
template <class T,class D>
void(unique_ptr<T,D>& x,unique_ptr<T,D>& y)noexpect;
```
交换两方的所有权，你要我的，我要你的。当然这是非成员函数，也有成员函数的写法
```cpp
void swap(unique_ptr& x) noexcept;
```
就是`a.swap(b)`酱紫。<br>
### 为什么shared_ptr没有release成员？
