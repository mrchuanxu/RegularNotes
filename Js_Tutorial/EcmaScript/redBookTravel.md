# JavaScript 实现
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
# 变量、作用域和内存问题
ECMAScript变量可能包含两种不同的数据类型的值： **基本类型和引用类型值**。基本类型值指的是简单的数据段，而引用类型值指那些可能由多个值构成的对象。<br>
`Undefined,Null,Boolean,Number和String`。这5种基本数据类型是按值访问的，因为可以操作保存在变量中的实际的值。<br>
引用类型的值是保存在内存肿的对象。js不允许直接访问内存中的位置，也就是说不能直接操作对象的内存空间。在操作对象时，实际上是在操作对象的引用而不是实际的对象。为此，引用类型的值是按引用访问的。<br>

