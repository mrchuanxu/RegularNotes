# 面向对象的JavaScript
### 动态类型语言和鸭子类型
静态类型语言在编译时便已确定变量的类型，而动态语言的变量类型要到程序运行的时候，待变量被赋予某个值之后，才会具有某种类型。
#### 鸭子类型
指导我们只关注对象的行为，而不关注对象本身，也就是HAS-A，而不是IS-A
```js
var duck = {
    duckSinging:function(){
        console.log("gagagag");
    }
};
var chicken = {
    duckSinging:function(){
        console.log("gagaga");
    }
};
var choir = [];
var joinChoir = function(animal){
    if(animal && typeof animal.duckSinging === 'function'){
        choir.push(animal);
        console.log("welcome in");
        console.log("num",choir.length);
    }else{
      console.log("something wrong");}
};
```
### 多态
> 对象的多态性 把不变的部分隔离开来。把可变的部分各自封装起来
```js
var makeSound = function(animal){
    animal.sound();
};
var Duck = function(){}
Duck.prototype.sound = function(){
    console.log("gagaga");
};
var Chicken = function(){}
Chicken.prototype.sound = function(){
    console.log("jijiji");
};

ƒ (){
    console.log("jijiji");
}
makeSound(new Duck())
VM1590:6 gagaga
```
#### 多态
在js中，并不需要诸如向上转型之类的技术来取得多态的效果
##### 使用继承得到多态效果
继承包括实现继承和接口继承
```js
class A{}
class B extends A{}
```
### 封装
封装的目的是将信息隐藏。包括封装数据和封装实现，封装类型和封装变化<br>
依赖变量的作用域来实现封装特性，而且只能模拟出public和private这两种封装性。<br>
```js
```

##### 所有数据都是对象
基本类型 undefined,number,boolean,string,function,object<br>
##### 要得到一个对象，不是通过实例化类，而是找到一个对象作为原型并克隆它
在js中没有类的概念。
```js
function Person(name){
  this.name = name;
}
Person.prototype.getName = function(){
  return this.name;
}
var person = new Person('eleven');
var objectFactory = function(){
    var obj = new Object,Constructor=[].shift.call(arguments);
    obj.__proto__ = Constructor.prototype;
    var ret = Constructor.apply(obj,arguments);
    return typeof ret === 'object'?ret:obj;
};
var a = objectFactory(Person,'eleven');
```
这里的Person并不是类，而是函数构造器，JS的函数既可以作为普通函数被调用，也可以作为构造器被调用。<br>
当使用new运算符来调用函数时，此时的函数就是一个构造器。用new运算符来创建对象的过程，实际上也只是先克隆Object.prototype对象，再进行一些其他额外操作的过程。<br>
##### 对象会记住它的原型
实际上__proto__就是对象跟“对象构造器的原型”联系起来的纽带。`obj.__proto__ = Constructor.prototype;`手动给obj对象设置正确的__proto__的指向。指向Person.prototypr,而不是原来的Object.prototype<br>
##### 如果对象无法响应某个请求，它会把这个请求委托给它的构造器的原型
```js
var obj = {name:'eleven'};
var A = function(){};
A.prototype = obj;
var a = new A();
console.log(a.name);
```
冒泡往原型链⛓️ 以上查找。
### 原型链⛓️ 的未来
es6 带来class，但是背后仍然是通过原型机制来创建对象
```js
class Animal{
  constructor(name){
    this.name = name;
  }
  getName(){
    return this.name;
  }
}
class Dog extends Animal{
  constructor(name){
    super(name);
  }
  speak(){
    return "woof";
  }
}
var dog = new Dog("Scamp");
```

