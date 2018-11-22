### JavaScript 实现
完整的JavaScript实现应该由以下三个不同的部分组成<br>
> 核心（ECMAScript）由ECMA-262定义，提供核心语言功能
> 文档对象模型（DOM）提供访问和操作网页内容的方法和接口
> 浏览器对象模型（BOM）提供与浏览器交互的方法和接口
#### 延迟脚本
```html
<script defer="defer" src="a.js"></script>
```
在`<script>`元素中设置defer属性，相当于告诉浏览器立即下载，但延迟执行。<br>
defer只适用于外部脚本文件。
##### 异步脚本
```html
<script async src="a.js"></script>
```
async只适用于外部脚本文件，并告诉浏览器立即下载文件<br>
但是与defer不同的是，标记async的脚本并不保证按照制定它们的先后顺序执行。<br>
#### 区分大小写
ECMAScript中的一切（变量、函数名和操作符）都区分大小写<br>
#### 严格模式
"use strict"
```js
function doSomething(){
  "use strict";
}
```
动态类型语言，运行时才知道类型<br>
没有重载<br>
### 变量、作用域和内存问题
#### 基本类型和引用类型的值
ECMAScript变量可能包含两种不同的数据类型的值： **基本类型和引用类型值**。基本类型值指的是简单的数据段，而引用类型值指那些可能由多个值构成的对象。<br>
`Undefined,Null,Boolean,Number和String`。这5种基本数据类型是按值访问的，因为可以操作保存在变量中的实际的值。<br>
引用类型的值是保存在内存肿的对象。js不允许直接访问内存中的位置，也就是说不能直接操作对象的内存空间。在操作对象时，实际上是在操作对象的引用而不是实际的对象。为此，引用类型的值是按引用访问的。<br>
##### 动态属性
定义基本类型值和引用类型值的方式是类似的：创建一个变量并为该变量赋值。<br>
当这个值保存到变量中以后，对不同类型值可以执行的操作则大相径庭。<br>
* 对于引用类型的值<br>
我们可以为其添加属性和方法，也可以改变和删除其属性和方法。
```js
var Person = new Object();
undefined
Person.name = "Trans"
"Trans"
```
* 对于基本类型的值<br>
我们不可以给其添加属性，会出现undefined<br>
##### 复制变量值
副本，赋值 **基本类型**<br>
复制操作结束后，两个变量实际上将引用同一个对象。因此，这个对象改变，两个值也会发生改变。一个值改变，另一个值也会跟着改变。**引用类型** <br>
##### 传递参数
ECMAScript中的所有函数的参数都是按值传递的。即，把函数外部的值复制给函数内部的参数，就和把值从一个变量复制给另一个变量一样。 **参数只能按值传播**<br>
```js
function setName(obj){
    obj.name = "Trans"
    obj = new Object()
    obj.name = "Mr"
}
var person = new Object()
setName(person)
person.name

"Trans"
```
始终是按值传播，局部不会改变！<br>
##### 检测类型
`typedef a, a instanceof constructor`
#### 执行环境及作用域
每个执行环境都有一个与之关联的变量对象，环境中定义的所有变量和函数都保存在这个对象中。<br>
全局执行环境被认为是window对象。因此所有全局变量和函数都是作为window对象的属性和方法创建的。<br>
```js
name = "mrtrans"
"mrtrans"
window.name
"mrtrans"
```
每个函数都有自己的执行环境。当一个执行流进入一个函数时，函数环境会被推入一个环境栈中。而在函数执行之后，栈将其环境弹出，把控制权返回给之前的执行环境。<br>
当代码在一个环境中执行时，会创建变量对象的一个 **作用域链**。<br>
作用域链的用途，保证对执行环境有权访问的所有变量和函数的有序访问。<br>
冒泡延续到全局执行环境；全局执行环境的变量对象始终都是作用域链中的最后一个对象。<br>
##### 延长作用域链
其他办法延长作用域链。当执行流进入下列任何一个语句时，作用域链就会得到加长。<br>
* try-catch语句的catch块；<br>
* with语句<br>
这两个语句都会在作用域链的前端添加一个变量对象。@对with语句来说，会将指定的对象添加到作用域链中。@对catch语句来说，会创建一个新的变量对象，其中包含的是被抛出的错误对象的声明。<br>
```js
function buildurl(){
   var qs = '?debug=true'
   with(location){
       var url = href+qs
       }
    return url
}
```
##### 没有块级作用域
#### 垃圾回收
引用计数，跟踪记录的每个值被引用的次数。<br>
垃圾收集器是周期性运行的，会产生性能问题。<br>
用=null解除引用。<br>
##### 小结
* 基本赖姓值在内存中占据固定大小的空间，因此被保存在栈内存中<br>
* 从一个变量向另一个变量复制基本类型的值，会创建这个值的一个副本<br>
* 引用类型的值是对象，会保存在堆内存中<br>
* 包含引用类型值的变量实际上包含的不是对象本身，而是一个指向该对象的指针<br>
* 从一个变量向另一个变量复制引用类型的值，复制的其实是指针，因此两个变量最终都指向同一个对象。<br>
* 标记清除，给当前不实用的值加上标记，然后再回收其内存。<br>
### 引用类型
* 使用对象<br>
* 创建并操作数组<br>
* 理解基本的JavaScript类型<br>
* 使用基本类型和基本包装类型<br>
引用类型的值（对象）是 **引用类型** 的一个实例，在ECMAScript中，引用类型是一种数据结构，用于将数据和功能组织在一起。<br>
尽管ECMAScript从技术上讲是一门面向对象的语言，但它不具备传统的面向对象语言所支持的类和接口基本结构。引用类型有时候也被称为对象定义，因为它们描述的是一类对象所具有的属性和方法。<br>
虽然引用类型与类看起来相似，但它们并不是相同的概念。<br>
```js
var person = new Object();
```
### Object类型
```js
var person = {
  name:'trans',
  age:90
}
var person={}
person.name = 'trans'
person.age = 80
person['name']
"trans"
```
### Array类型
```js
var colors = new Array();
var colors20 = new Array(20);
var colorsStr = new Array("red","blue","green"); // length
var colorsStrs = ["red","blue","green"];
colorsStr[1];
```
#### 检测数组
`Array.isArray(value)`方法，确定数组。<br>
#### 转换方法
```js
colors.toString()
colorts.valueOf()
colors.join(",") // red,blue,green
colors.join("||") // red||blue||green
```
#### 栈方法
ECMAScript数组也提供了一种让数组的行为类似于其他数据结构的方法。LIFO(Last-In-First-Out,后进先出)<br>
push()和pop() 栈<br>
队列FIFO(First-In-First-Out)<br>
shift()和push(),unshift()->推入两项<br>
#### 重排序方法
reverse()和sort()<br>
`colors.reverse()`
#### 操作方法
```js
colors.concat("yellow",["black","brown"]);
colors // red,green,blue,yellow,black,brown
colors.slice(1,4);
colors.splice(2,0,"red","green") // 从当前数组的位置2开始插入字符串"red"和"green"
colors.splice(2,1,"red","green") // 会删除当前数组位置2的项，然后再从位置2开始插入字符串"red"和"green" 
```
#### 位置方法
indexOf(?)<br>
#### 迭代方法

### 面向对象的程序设计
#### 理解对象
创建自定义对象的最简单方式就是创建一个Object的实例，然后再为它添加属性和方法。
```js
var person = new Object();
person.name = "trans"
person.SayName = function(){
  console.log(this.name);
}
```
对象字面量语法
```js
var person = {
  name:"trans",
  SayName:function(){
    console.log(this.name);
  }
}
```
修改属性默认的特性`Object.defineProperty()`方法，接收三个参数：属性所在的对象、属性的名字和一个描述符对象。描述符对象的属性必须是：`configurable、enumerable、writable和value`。设置其中的一或多个值，可以修改对应的特性值。
```js
var person = {};
Object.defineProperty(person,"name",{
  writable:false,
  value:"modifiedName"
});
console.log(person.name);
```
设置name为只读属性，不能赋值改变。<br>
configurable属性同理。设置为false之后就会有限制，不能设置修改。<br>
##### 访问器属性
访问器属性不包含数据值；它们包含一对儿getter和setter函数。访问会调用getter函数。写入会调用setter函数并传入新值。<br>
使用`Object.defineProperty()`来定义访问器属性。<br>
```js
var book = {
  _year:2004,
  edition:1
};
Object.defineProperty(book,"year",{
  get:function(){
    return this._year;
  },
  set:function(newValue){
    if(newValue > 2004){
      this._year = newValue;
      this.edition += newValue - 2004;
    }
  }
});
book.year = 2005
console.log(book.edition);
```
#### 定义多个属性
`Object.defineProperties()`
```js
var book = {};
Object.defineProperties(book,{
  _year:{
    value:2004
  },
  edition:{
    value:1
  }，
  year:{
    get:function(){
      return this._year
    },
    set:function(newValue){
      ...
    }
  }
})；
```
#### 创建对象
工厂模式，构造函数模式，原型模式，动态原型模式，寄生构造函数模式，稳妥构造函数模式。
#### 继承
原型链，借用构造函数，组合继承，原型式继承，寄生式继承，寄生组合式继承
设计模式将会有专门的文章解读！敬请期待！<br>
