# 面向对象程序设计
面向对象在很多语言都用得比较多。<br>
面向对象程序设计基于三个基本概念：数据抽象、继承和动态绑定。在class那一章节，已经介绍了数据抽象的知识，这次我们介绍继承和动态绑定。<br>
继承和动态绑定对程序的编写有两方面的影响：a.我们可以更容易地定义与其他类相似但不完全相同的新类；b.在使用这些彼此相似的类编写程序时，我们可以在一定程度上忽略掉它们的区别。<br>
### OOP:概述
面向对象程序设计(object-oriented programming)的核心思想是数据抽象、继承和动态绑定。<br>
通过使用 **数据抽象** ，我们可以将类的接口与实现分离；<br>
使用 **继承** ，可以定义相似的类型并对其相似关系建模；<br>
使用 **动态绑定** ，可以在一定程度上忽略类似的区别，而以统一的方式使用它们的对象。<br>
##### 继承
**通过继承(inheritance)联系在一起的类构成一种层次关系。**<br>
通常在层次关系的根部有一个 **基类（base class）**，其他类则直接或间接地从基类继承而来，这些继承得到的类称为 **派生类（derived class）**<br>
基类负责定义在层次关系中所有类共同拥有的成员，而每个派生类定义各自特有的成员。<br>
在C++语言中，基类将类型相关的函数与派生类不做改变直接继承的函数区分对待。对于某些函数，基类希望它的派生类各自定义适合自身的版本，此时基类就将这些函数声明为 **虚函数（virtual function）**。
```cpp
class Quote{
  public:
  std::string isbn() const;
  virtual double net_price(std::size_t n) const;
}
```
派生类必须通过使用 **类派生列表(class derivation list)**明确指出它是从哪个（哪些）基类继承而来的。类派生列表的形式是：首先一个冒号，后面紧跟以逗号分隔的基类列表，其中每个基类前面可以有访问说明符：
```cpp
class Bulk_quote:public Quote{
  public:
  double net_price(std::size_t) const override;
}
```
因为Bulk_quote在它的派生列表中使用了public关键字，**因此我们完全可以把Bulk_quote的对象当成Quote的对象来使用。**<br>
派生类必须在其内部对所有重新定义的虚函数进行声明。派生类可以在这样的函数之前加上`virtual`关键字，但是并不是非得这么做。**C++11新标准允许派生类显式地注明它将使用哪个成员函数改写基类的虚函数，具体措施是在该函数的形参列表之后增加一个`override`关键字。**<br>
##### 动态绑定
通过使用 **动态绑定(dynamic binding)**，我们能用同一段代码分别处理`Quote`和`Bulk_quote`的对象。
```cpp
// 计算并打印销售给定数量的某种书籍所得费用
double print_total(ostream &os,const Quote &item, size_t n){
  // 根据传入item形参的对象类型调用Quote::net_price
  // 或者Bulk_quote::net_price
  double ret = item.net_price(n);
  os<< ...
}
```
动态绑定有时又称为 **运行时绑定(run-time binding)**<br>
📒 在C++语言中，当我们使用基类的引用（或指针）调用一个虚函数时将发生动态绑定。<br>
### 定义基类和派生类
#### 定义基类
```cpp
class Quote{
  public:
  Quote() = default;
  Quote(const std::string &book,double sales_price):bookNo(book),price(sales_price){}
  std::string isbn() const { return bookNo; }
  // 返回给定数量的书籍的销售总额
  // 派生类负责改写并使用不同的折扣计算算法
  virtual double net_price(std::size_t n) const { return n*price; }
  virtual ~Quote() = default; // 对析构函数进行动态绑定
  private:
  std::string bookNo;
  protected:
  double price = 0.0;
}
```
记住作为继承关系中根节点通常会定义一个虚析构函数。<br>
📒 基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此。<br>
##### 成员函数与继承
派生类需要对虚函数这些操作提供自己的新定义以 **覆盖(override)**从基类继承而来的旧定义。<br>
在C++语言中，基类必须将它的两种成员函数区分开来：a. 一种是基类希望其派生类进行覆盖的函数（常常将其定义为虚函数(virtual)，当我们使用指针或引用调用虚函数时，该调用将被动态绑定。） b. 基类希望派生类直接继承而不要改变的函数。<br>
基类通过在其成员函数的声明语句之前加上关键字`virtual`使得该函数执行动态绑定。<br>
@ 任何构造函数之外的非静态函数都可以是虚函数。<br>
@ 关键字`virtual`只能出现在类内部的声明语句之前而不能用于类外部的函数定义。<br>
@ 如果基类把一个函数声明成虚函数，则该函数在派生类中隐式地也是虚函数。<br>
成员函数如果没有被声明为虚函数，则 **其解析过程发生在编译时而非运行时。**<br>
##### 访问控制与继承
派生类可以继承定义在基类中的成员，但是派生类的成员函数不一定有权访问从基类继承而来的成员。（和其他使用基类的代码一样，派生类能访问公有成员，而不能访问私有成员。）<br>
不过在某些时候，基类中还有这样一种成员，基类希望它的派生类有权访问该成员，同时禁止其他用户访问。我们用 **受保护的(protected)**访问运算符说明这样的成员。<br>
❓ 什么是虚成员？<br>
对于某些函数，基类希望它的派生类各自定义适合自身的版本，此时基类就将这些函数声明成虚函数。<br>
❓ protected 访问说明符与private有何区别？<br>
@ protected:基类和其派生类还有友元可以访问。<br>
@ private:只有基类本身和友元可以访问<br>
#### 定义派生类
派生类必须通过使用 **类派生列表(class derivation list)**明确指出它是从哪个（哪些）基类继承而来的。<br>
**public、protected和private。**<br>
派生类必须将其继承而来的成员函数中需要覆盖的那些重新声明，因此，我们的Bulk_quote类必须包含一个net_price成员：
```cpp
class Bulk_quote:public Quote{
  public:
  Bulk_quote() = default;
  Bulk_quote(const std::string&,double,std::size_t,double);
  // 覆盖基类的函数版本以实现基于大量购买的折扣政策
  double net_price(std::size_t) const override;
  private:
  std::size_t min_qty = 0; // 适用折扣政策的最低购买量
  double discount = 0.0; // 以小数表示折扣额
};
```
我们能将公有派生类型的对象绑定到基类的引用或指针上。<br>
大多数类都只继承自一个类，这种形式的继承被称作“单继承”，它构成了本章的主题。<br>
##### 派生类中的虚函数
派生类经常（但不总是）覆盖它继承的虚函数。如果派生类没有覆盖其基类中的某个虚函数，则该虚函数的行为类似于其他的普通成员，派生类会直接继承其在基类中的版本。<br>
派生类可以在它覆盖的函数前使用`virtual`关键字，但不是非得这么做。<br>
