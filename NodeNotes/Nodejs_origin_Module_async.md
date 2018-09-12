## Node简介
首先这本书我看了一遍，所以我现在基本上是二刷，这一次我会详细做一些笔记，并且会运行一个web应用去验证一些代码段，进行异步以及同步编程的示例操作。同时大部分会去做摘录一些重要的语句去做记忆。<br>
**为什么叫node?**
起初，Ryan Dahl称他的项目为Web.js，就是一个web的服务器，但是项目的发展竟然变成了构建网络应用的一个基础框架，由此，在node的基础上可以构建更多的东西，像服务器、客户端、命令行工具等。Node发展为一个强制不共享任何资源的单线程、单进程系统，包含十分适宜的网络的库，为构建大型分布式应用程序提供基础设施，其目标也是成为一个构建快速，可伸缩的网络应用平台。他自身非常简单，通过通信协议来组织许多Node，非常容易通过扩展来达成构建大型网络应用的目的。每一个Node都构成这个网络应用的一个节点。<br>

## Node特点
**异步 I/O**
```js
$.post('url',{title:'nodejs is the best'},function (data){
    console.log('got this');
});
console.log('end post');
```
在这里，其实熟悉异步的用户会知道，got this是在end post之后输出的。在调用$.post()后，后续代码是被立即执行的，而got this的执行时间是不被预期的。我们只知道它将在这个异步请求结束后执行，但并不知道具体的时间点。其实在异步调用中，对于结果值的捕获始终遵循一个原则就是"Don't call me, I will call you"。<br>
那么在node中，异步IO也很常见。例如读取文件<br>
```js
var fs = require('fs');
fs.readFile('/path',function(err,file){
     console.log('read finish');
});
console.log('go read');
```
读出来就是先go read 再read finish<br>
其实在node中，绝大多数的操作都以异步的方式进行调用。在Node中，我们可以语言层面很自然地进行并行I/O操作。
事件与回调函数<br>
通过一个例子来解释一下事件<br>
```js
var http = require('http');
var querystring = require('querystring');

http.createServer(function(req,res){
var postData = '';
req.setEncoding('utf-8');

req.on('data',function(chunk){
postData += chunk;
});
req.on('end',function(){
res.end(postData);
});
}).listen(8080);
console.log('server open');
```
在这里，运行后服务端会启动，这里我们在前端再构建ajax发送事件，后端就会获取，这里我们就只需要关心请求成功时执行相应的业务逻辑即可。
**单线程**
Node保持了Javascript在浏览器中单线程的特点。 而且在Node中，javascript与其余线程是无法共享任何状态的。<br>
好处： 不用像多线程编程那样处处在意状态的同步问题，这里没有死锁的存在，也没有线程上下文交换所带来的性能上的开销。<br>

## 模块机制
js经历了 工具->组件->框架->应用 <br>
CommonJS模块规范<br>
1. 模块引用<br>
```js
var math = require('math');
```
2.模块定义<br>
//math.js
```js
exports.add = function(){
var sum = 0,i=0,args = arguments, l=args.length;
while(i<1){
sum += args[i++];
}
return sum;
};
//mathRequire.js
var math = require('./math');

exports.increment = function(val){
return math.add(val,3);
};
```
## Node的模块实现
Node中引入模块需要经历如下3个步骤<br>
1. 路径分析<br>
2. 文件定位<br>
3. 编译执行<br>
Node中，模块分为两类：一类是Node提供的模块，称为核心模块；另一类是用户编写的模块，称为文件模块<br>
核心模块部分在Node源码的编译过程中，编译进了二进制执行文件<br>
文件模块则是在运行时动态加载，需要完整的路径分析、文件定位、编译执行过程，速度比核心模块慢<br>
**优先从缓存加载**
Node引用的模块都会进行缓存，以减少二次引入时的开销，不同的地方在于，浏览器仅仅缓存文件，而Node缓存的是编译和执行之后的对象<br>
require()方法对相同模块的二次加载都一律采用缓存优先的方式，这是第一优先级。不同之处在于核心模块的缓存检查先于文件模块的缓存检查。<br>
**路径分析和文件定位**
*模块标识符分析*
核心模块，如 http,fs,path等<br>
.或..开始的相对路径<br>
以/开始的绝对路径文件模块<br>
非路径形式的文件模块，如自定义connect模块<br>
**核心模块**
核心模块的优先级仅次于缓存加载<br>
路径形式的文件模块<br>
自定义模块 最慢<br>
模块路径是Node在定位文件模块的具体文件时制定的查找策略，具体表现为一个路径组成的数组。<br>
生成规则<br>
1.当前文件目录下的node_modules<br>
2.父目录下的node_modules<br>
3.父目录的父目录下的node_modules<br>
4.沿路径向上逐级递归，直到根目录下的node_modules<br>

## 模块编译
每个文件模块都是一个对象<br>
对于不同的文件扩展名，其载入方法也有所不同<br>
1. .node文件。用C/C++编写的扩展文件，通过dlopen()方法加载最后编译生成的文件<br>
2. .js文件。 通过fs模块同步读取文件后编译执行<br>
3. .json文件。 通过fs模块同步读取文件后，用JSON.parse()解析返回结果<br>
4. .其余都.js文件载入<br>
每一个编译成功的模块都会将其文件路径作为索引缓存在module._cache对象上，以提高二次引用性能<br>
根据不同的文件扩展名，Node会调用不同的读取方式。<br>
1.javascript模块的编译<br>
事实上，在编译的过程中，Node对获取的JavaScript文件内容进行了头尾包装。在头部添加了（function(exports,require,module,__filename,__dirname){\n, 在尾部添加了\n});<br>
一个正常的Javascript文件会被包装成如下的样子：<br>
```js
      (function(exports,require,module,__filename,__dirname){
                var math = require('math');
                exports.area = function(radius){
                    return Math.PI * radius*radius;
       };
});
```
这样每个模块文件之间都进行了作用域隔离。包装之后的代码会通过vm原生模块的runInThisContext()方法执行（类似eval，只是明确上下文，不污染全局），返回一个具体的function对象。最后将当前模块对象exports属性、require()方法、module（模块对象自身），以及在文件定位中得到的完整文件路径和文件目录作为参数传递给这个function()执行。<br>
至此，require、exports、module的流程已经完整，这就是Node对CommonJS模块规范的实现。<br>
2.C/C++ 模块的编译<br>
3. JSON文件的编译<br>
2.3 核心模块<br>
*javascipt核心模块的编译过程*
**1.转存为C/C++ 代码**<br>
Node采用了V8附带的js2c.py工具，将所有内置的JavaScript代码（src/node.js和lib/*.js) 转换成C++里的数组，生成node_natives.h头文件
```js
namespace node{
    const char node_native[] = {47,47,..};
    ..
    struct _native{
         const char *name;
         const char *source;
         size_t source_len;
   };
    static const struct _native natives[] = {
              {"node",node_native,sizeof(node_native)-1},
              {"dgram",dgram_native,sizeof(dgram_native)-1},
               ...
   };
}
```
**2. 编译JavaScript核心模块**
lib目录下的所有模块文件也没有定义require、module、exports这些变量。在引入Javascript 核心模块的过程中，也经历了头尾包装的过程，然后才执行和导出了 exports对象。<br>
与文件模块有区别的地方在于：获取源代码的方式（核心模块是从内存中加载的）以及缓存执行结果的位置<br>

## 编写核心模块
**C/C++扩展模块**
Javascript 的一个典型弱点就是位运算。只有double型的数据类型，在进行位运算的过程中，需要将double型转换为int型。效率不高
其中*nix下通过g++/gcc等编译器编译为动态链接共享对象文件(.so)<br>
### 前提
GYP项目生成工具<br>
V8引擎C++库： 自身由C++写成，可以实现Js与C++的相互调用<br>
libuv库： Node能够实现跨平台的一个诀窍就是它的libuv库。这个库是夸平台的一层封装，通过它去调用一些底层操作，比自己在各个平台下编写实现高效得多。libuv封装的功能包括事件循环、文件操作等。<br>
### Node内部库
其他库<br>
编写<br>
普通的扩展模块与内建模块的区别在于无须将源代码编译进Node，而是通过dlopen()方法动态加载。所以在编写普通的扩展模块时，无须将源代码写进node命名空间，也不需要头文件。<br>
```js
exports.sayHello = function(){
    return 'hello world';
};
```
新建hello目录作为自己的项目位置，编写hello.cc并将其存储到src目录下。
```js
#include <node.h>
#include <v8.h>
using namespace v8;
Handle<Value> SayHello(const Arguments& args){
    Handle scope;
    return scope.Close(String::New("Hello world"));
}

void  Init_Hello(Handle<Object> target){
    target->Set(String::NewSymbol("sayHello"),FunctionTemplate::New(SayHello)->GetFunction());
}
NODE_MODULE(hello,Init_Hello)//调用该方法将注册方法定义到内存中
```
C/C++扩展模块与内建模块的套路一样，将方法挂载在target对象上，然后通过NODE_MODULE声明即可<br>
C/C++扩展模块的编译 GYP工具使用<br>
C/C++扩展模块加载<br>
### 模块调用栈
Javascript核心模块主要扮演的职责有两类：一类是作为C/C++内建模块的封装层和桥接层，供文件模块调用；一类是纯粹的功能模块，不需要与底层打交道。<br>
### 包与NPM
**异步I/O**<br>
web的含义是网，Node的表现就如它的名字一样，是网络中灵活的一个节点。<br>
**为什么要异步I/O**<br>
1. 用户体验。<br>
浏览器中Javascript在单线程上执行，与UI渲染共用一个线程。
**异步并发**
getData('from_db',function(result){});
getData('from_remote_db',function(result){});
只有后端能快速响应资源，才能让前端的体验变好。
2.资源分配<br>
假设业务场景中有一组互不相关的任务需要完成，现行的主流方法<br>
**单线程串行一次执行**<br>
**多线程并行完成**<br>
多线程的代价在于创建线程和执行期线程上下文切换的开销较大。<br>
单线程性能略差，容易阻塞<br>
Node方案：利用单线程，远离多线程死锁、状态同步等问题；利用异步I/O，让单线程远离阻塞，以更好地利用CPU<br>
示意图

### 异步I/O实现现状
操作系统内核对于I/O只有两种方式：阻塞与非阻塞。阻塞特点调用之后一定要等到系统内核层面完成所有操作后，调用才结束。<br>
阻塞I/O造成CPU等待I/O，浪费等待时间，CPU的处理能力不能得到充分利用。为了提高性能，内核提供了非阻塞I/O。非阻塞I/O的差别为调用之后会立即返回。<br>
**轮询**<br>
轮询确认非阻塞I/O是否完成数据获取<br>
read,
select,
poll,
epoll.该方案是linux下效率最高的I/O事件通知机制，在进入轮询的时候如果没有检查到I/O事件，将会进行休眠，直到事件发生将它唤醒。真实利用了事件通知、执行回调的方式，而不是遍历查询，所以不会浪费cpu，执行效率高。//视图会晚点画出。

### 理想的非阻塞I/O
我们期望的完美的异步I/O应该是应用程序发起非阻塞调用，无须通过遍历或者事件唤醒等方式轮询，可以直接处理下一个任务，只需在I/O完成后通过信号或回调将数据传递给应用程序即可。<br>

Linux下存在这样一种方式，它原生提供的一种异步I/O方式（AIO）就是通过信号或回调传递数据的<br>
### 现实中的异步I/O
@通过让部分线程进行阻塞I/O或者非阻塞I/O加轮询技术来完成数据获取，让一个线程进行计算处理，通过线程之间的通信将I/O得到的数据进行传递，这样就轻松实现了异步I/O<br>
libeio实际上依然采用线程池与阻塞I/O模拟异步I/O。<br>
我们时常提到Node是单线程，这里的单线程仅仅知识JavaScript执行在单线程中罢了。在Node中，无论是*nix还是Windows平台，内部完成I/O任务的另有线程池。
Node的异步I/O<br>
**1.事件循环**<br>
首先，我们着重强调一下Node自身的执行模型——事件循环，正是它使得回调函数十分普遍。<br>
在进程启动时，Node便会创建一个类似与while(true)的循环，每执行一次循环体的过程我们称之为Tick。<br>
每个tick的过程就是查看是否有事件待处理，如果有，就取出事件及其相关的回调函数<br>

## 异步编程
有异步IO，必有异步编程<br>
高阶函数
```js
points.sort(function(a,b){
return b-a;
});
```
通过改动sort()方法的参数，可以决定不同的排序方式，从这里可以看出高阶函数的灵活性<br>
结合node提供的最基本的事件模块可以看到，事件的处理方式正是基于高阶函数的特性来完成的。<br>
```js
var emitter = new events.EventEmitter();
emitter.on('event_foo',function(){
alert("hahah");
});
```
高阶函数es5 forEach().map(),reduce(),reduceRight(),filter(),every(),some()<br>
### 偏函数用法
偏函数用法是指创建一个调用另外一部分--参数或变量已经预置的函数--的函数的用法。<br>
为了解决重复定义的问题，我们引入一个新函数，这个函数可以如工厂一样批量创建一些类似的函数。<br>
```js
var isType = function(type){
return function(obj){
return toString.call(obj) == '[object'+type+']';
}
}
var isString = isType('String');
var isFunction = isType('function');
```
通过指定部分参数来产生一个新的定制函数的形式就是偏函数。<br>
### 异步编程的优势与难点
**优势：**
NOde带来的最大特性莫过于基于事件驱动的非阻塞I/O模型。非阻塞I/O可以使CPU与I/O并不相互依赖等待，让资源得到更好的利用。对于网络应用而言，并行带来的想象空间更大，延展而开的是分布式和云。并行使得各个单点之间能够更有效地组织起来。<br>


Node是为了解决编程模型中阻塞I/O的性能问题的，采用了单线程模型，这导致Node更像一个处理I/O密集问题的能手，而CPU密集型则取决于关键的能耐如何。<br>
@建议，对CPU的耗用不超过10ms，或者将大量的计算分解为诸多的小量计算，通过setImmediate()进行调度。只要合理利用node的异步模型与V8的高性能，就可以充分发挥CPU和I/O资源的优势。<br>
**难点**
﻿Node令异步编程如此风行，这也是异步编程首次大规模出现在业务层面。它借助异步I/O模型及V8高性能引擎，突破单线程的性能瓶颈，让JavaScript在后端达到使用价值。另一方面，它也统一了前后端JavaScript的编程模型。<br>
**1.难点一：异常处理**<br>
try...catch(e) 异步编程并不适用。异步I/O的实现主要包含两个阶段：提交请求和处理结果。这两个阶段中间有事件循环的调度，两者彼此不关联。异步方法则通常在第一个阶段提交请求后立即返回，因为异常并不一定发生在这个阶段，try/catch的功效在此处不会出现任何作用<br>
Node在处理异常上形成了一种约定，将异常作为回调函数的第一个实参传回，如果为空值，则表明异步调用没有异常抛出。<br>
```js
async(function(err,result){});
```
**遵循一些原则**<br>
1. 必须执行调用者传入的回调函数<br>
2.正确传递回异常供调用者判断<br>
```js
var async = function(callback){
process.nextTick(function(){
var results = dosomething;
if(error){
return callback(errors);
}
```

在异步方法的编写中，另一个容易犯的错误是对用户传递的回调函数进行异常捕获。
```js
try{
req.body = JSON.parse(buf,options,reviver);
callback();
}catch(err){
err.body = buf;
err.status = 400;
callback(err);
}
```
**难点二.嵌套过深**<br>
**难点三.阻塞代码**<br>
**难点四.多线程编程**<br>
**难点五.异步转同步**<br>
解决方案
@事件发布/订阅模式 事件监听器模式是一种广泛用于异步编程的模式，是回调函数的事件化。
```js
emitter.on("event1",function(message){
console.log(message);
});//订阅 订阅事件就是一个高阶函数的应用。事件发布/订阅模式可以实现一个事件与多个回调函数的关联，这些回调函数又称为事件侦听器
// 事件侦听器模式也是一种钩子机制，利用钩子导出内部数据或状态给外部的调用者
emitter.emit("event1","I am message");
``` 
@Promise/Deferred模式
@流程控制库
继承events模块
```js
> var events = require('events');
undefined
> function Stream(){
... events.EventEmitter.call(this);
... }
undefined
> util.inherits(Stream,events.EventEmitter);
undefined
> 
```
Node在util模块中封装了继承的方法，所以此处可以很便利地调用。
利用事件队列解决雪崩问题
在时间订阅/发布模式中，通常也有一个once方法，通过它添加的侦听器只能执行一次，在执行后就会将它与事件的关联移除。这个特性常常可以帮助我们过滤一些重复性的事件相应。
雪崩问题：高访问量、大并发量的情况下缓存失效的情景，此时大量的请求同时涌入数据库中，数据库无法同时承受如此大的查询请求，进而往前影响到网站整体的响应速度。
```js
var proxy = new events.EventEmitter();
var status = "ready" //引入状态锁
var select = function(callback){
    proxy.once('selected',callback); //利用once方法，将所有请求的回调都压入时间队列中，利用执行一次就会将监视器移除的特点，保证每一个回调都会被执行一次
    if(status === "ready"){
        status = "pending";
        db.select('SQL',function(results){
               proxy.emit('selected',results);
               status = 'ready';
});
}
```
};//此处可能因为存在侦听器过多引发的警告，需要调用setMaxListeners(0)移除掉警告，或者设更大的警告阀值
多异步之间的协作方案
事件发布/订阅模式有着它的优点。利用高阶函数的优势，侦听器作为回调函数可以随意添加和删除，它帮助开发者轻松处理随时可能添加的业务逻辑。
@可以隔离业务逻辑，保持业务逻辑单元的职责单一。
```js
var count = 0;
var results = {};
var done = function(key,value){
    results[key] = value;
    count ++;
    if(count == 3){
        render(results);
};

fs.readFile(template_path,"utf-8",function(err,template){
    done("template",template);
});
db.query(sql,function(err,data){
done("data",data);
});
l1on.get(function(err,resources){
done("resources",resources);
});
```
由于多个异步场景中回调函数的执行并不能保证顺序，且回调函数之间互相没有任何交集，所以需要借助一个第三方函数和第三方变量来处理异步协作的结果。@通常，我们把这个用于检测次数的变量叫做哨兵变量。
```js
var after = function(times,callback){
    var count = 0,results = {};
return function(key,value){
    results[key] = value;
    count++;
    if(count === times){
        callback(results);
}
};
};
var done = after(times.render);
```
利用发布订阅方式来完成多对多的方案
```js
var emitter = new events.Emitter();
var done = after(times.render);
emitter.on("done",done);
emitter.on("done",other);

fs.readFile(template_path,"utf-8",function(err,template){
    emitter.emit("done","template",template);
});
db.query(sql,function(err,data){
 emitter.emit("done","data",data);
});
l1on.get(function(err,resources){
 emitter.emit("done","resources",resources);
});
```
另一个方案则是来自笔者自己写的EventProxy模块，它是对事件订阅/发布模式的扩充，可以自由订阅组合事件。由于依旧采用的是事件订阅/发布模式，与Node非常契合
```js
var proxy = new EventProxy();
proxy.all("template","data","resources",function(template,data,resources){
//TODO
});
fs.readFile(template_path,"utf-8",function(err,template){
    proxy.emit("template",template);
});
db.query(sql,function(err,data){
 proxy.emit("done","data",data);
});
l1on.get(function(err,resources){
 proxy.emit("resources",resources);
});
```
EventProxy 提供了一个al()方法来订阅多个事件，当每个事件被触发之后，侦听器才会执行<br>
tail()方法： 侦听器在满足条件时执行一次后，如果组合事件中的某个事件被再次触发，侦听器会用最新的数据继续执行<br>
all()方法： 侦听器在满足条件之后只会执行一次<br>
EventProxy提供了after() 方法来实现事件在执行多少次后执行侦听器的单一事件组合订阅方式<br>
```js
proxy.after("data",10,function(datas){}); //执行10次data事件后，执行侦听器。
```
### EventProxy原理
EventProxy来自于Backbone的事件模块，Backbone的事件模块是Model、View模块的基础功能，在前端有广泛的使用。它在每个非all事件触发时都会触发一次all事件
```js
trigger : function(eventName){
    var list,calls,ev,callback,args;
    var both = 2;
    if(!(calls = this._callbacks)) return this;
    while(both --){
    ev = both ? eventName: 'all'；
   ...
   ```
EventProxy则是将all当做一个事件流的拦截层，在其中注入一些业务来处理单一事件无法解决的异步处理问题。类似的扩展方法还有all(),tail(),after(),not()和any()<br>
EventProxy的异常处理<br>
EventProxy在事件发布/订阅模式的基础上还完善了异常处理<br>
EventProxy实践过程<br>
```js
exports.getContent = function(callback){
var ep = new EventProxy();
ep.all('tpl','data',function(tpl,data){
callback(null,{
template:tpl,
data:data
});
});
ep.fail(callback);
fs.readFile('template.tpl','utf-8',ep.done('tpl'));
db.get('some sql',ep.done('data'));
};
```
### Promise/Deferred模式
使用事件的方式时，执行流程需要被预先设定。即便时分之，也需要预先设定，这就是发布/订阅模式的运行机制所决定的。
**普通的Ajax调用**
```js
$.get('/api',{
    success:onSuccess,
    error:onError,
    complete
});
```
在上面的异步调用中，必须严谨地设置目标。那么是否有一种先执行异步调用，延迟传递处理的方式呢？
**Promise/Deferred模式
```js
$.get('api').success(onSuccess).error(onError).complete(onComplete);
```
这使得即使不调用success()、error()等方法，Ajax也会执行，这样的调用方式比预先传入回调让人觉得舒适一些。<br>
在原始的API中，一个事件只能处理一个回调，而通过Deferred对象，可以对事件加入任意的业务处理逻辑。<br>
```js
$.get('/api').success(onSuccess).success(onSuccess1);
```
异步的广度使用使得回调、嵌套出现，但是一旦出现深度的嵌套，就会让编程的体验变得不愉快，而Promise/Deferred模式在一定程度上缓解了这个问题。<br>
Promises/A\B\C\D相继出现<br>
### 1.Promises/A<br>
Promise/Deferred模式其实包含两部分，即Promise和Deferred。<br>
Promises/A的行为<br>
**Promise操作对单个异步操作做出了这样的抽象定义**<br>
@Promise操作只会处在3中状态的一种：未完成态、完成态和失败态<br>
@Promise的状态只会出现从未完成态或失败态转化，不能逆反。完成态和失败态不能相互转化<br>
@Promise的状态一旦转化，就不能被更改
![Promise的状态转化示意图](http://www.ous.im/img/Deferred.png)<br>
在API的定义上。Promise/A提议是比较简单的。一个Promise对象只要具备then()方法即可。但是对于then方法，要求如下：<br>
@接受完成态、错误态的回调方法。在操作完成或出现错误时，将会调用对应方法<br>
@可选地支持progress事件回调作为第三个方法<br>
@then() 方法只接受function对象，其余对象将被忽略<br>
@then() 方法继续返回Promise对象，以实现链式调用<br>
then方法定义如下：
```js
then(fulfilledHandler,errorHandler,progressHandler)
```
为了演示Promises/A提议，这里我们尝试通过继承Node的events模块来完成一个简单的实现
```js
var Promise = function(){
    EventEmitter.call(this);
};

util.inherits(Promise,EventEmitter);
Promise.prototype.then = function(fulfillHandler,errorHandler,progressHandler){
    if(typeof fulfillHandler === 'function'){
        this.once('success',fulfillHandler);
    }
        if(typeof errorHandler === 'function'){
        this.once('success',errorHandler);
    }
        if(typeof progressHandler === 'function'){
        this.once('success',progressHandler);
    }
    return this;
};
```
这里看到then()方法所做的事情是将回调函数存放起来。为了完成整个流程，还需要触发执行这下回调函数的地方，实现这些功能的对象通常被称为Deferred,即延迟对象<br>
```js
var Deferred = function(){
    this.state = 'unfulfilled';
    this.promise = new Promise();
};

Deferred.prototype.resolve = function(obj){
    this.state = 'fulfilled';
    this.promise.emit('success',obj);
};

Deferred.prototype.reject = function(err){
    this.state = 'failed';
    this.promise.emit('error',err);
};

Deferred.prototype.progress = function(data){
    this.promise.emit('progress',data);
};
```
这里的方法之间的对应关系如图
![状态与方法之间的对应关系](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1536032270806&di=13f812890fe28251645d009af8b7825a&imgtype=0&src=http%3A%2F%2Fpic4.zhimg.com%2Fv2-a90a6c703c051370aee8311ec00ef4a5_b.jpg)<br>
其中完成态为resolve，失败态为reject<br>
利用Promise/A提议的模式，我们可以对一个典型的相应对象进行封装
```js
res.setEncoding('utf-8');
res.on('data',function(chunk){
    console.log('BODY:'+chunk);
});

res.on('end',function(){
    //Done
});
res.on('error',function(err){
    //Error
});
```
上述代码可转化为：
```js
res.then(function(){},function(err){},function(chunk){});
``` 
要实现上述褥子简单的API，只需要简单地改造一下即可
```js
var promisify = function(res){
    var deferred = new Deferred();
    var result = '';
    res.on('data',function(chunk){
        console.log('BODY:'+chunk);
        deferred.progress(chunk);
    });

    res.on('end',function(){
        deferred.resolve(result);
        //Done
    });
    res.on('error',function(err){
        deferred.reject(err)
        //Error
    });
    return deferred.promise;
}
```
这里返回deferred.promise的目的是为了不让外部程序调用resolve()和reject()方法，更改内部状态的行为交由定义者处理。
```js
promisify(res).then(function(){},...)
```
Promise/Deferred整体关系示意图如下<br>
![Promise/Deferred整体关系示意图](./img/deferred_promise.png)

**Promise参考文档**<br>
https://juejin.im/post/5a31d21e5188257dd239a7cc
**深入理解Promise和Deferred**<br>
https://www.jianshu.com/p/0e1c9bec17ad
与事件发布/订阅模式相比，Promise/Deferred模式的API接口和抽象模型都十分简洁，从图中可以看出，它将业务不可变的部分封装在Deferred部分，将可变部分交给了Promise。<br>
Q模块是Promise/A规范的一个实现，可以通过npm install q进行安装使用。<br>

```js
/**
* Create a Node-style callback that will resolve or reject the deferred
* promise.
*@ return a nodeback
*/
defer.prototype.makeNodeResolver = function(){
    var self = this;
    return function(error,value){
        if(error){
            self.reject(error);
        }else if(arguments.length > 2){
            self.resolve(array_slice(arguments,1));
        }else{
            self.resolve(value);
        }
    };
};
```
可以看到这里是一个高阶函数的使用，makeNodeResolver返回一个Node风格的回调函数。对于fs.readFile()的调用，将会演化为
```js
var readFile = function(file,encoding){
    var deferred = Q.defer();
    fs.reafFile(file,encoding,deferred.makeNodeResolver());
    return deferred.promise;
}
```
定义之后的调用如下
```js
readFile('foo.txt','utf-8').then(function(data){
    // success case
},function(err){
    // failed case
});
```
Promise通过封装异步调用，实现了正向用例和反向用例的分离以及逻辑处理延迟，这使得回调函数相对优雅。<br>
Q通过Promise()可以实现延迟处理，以及通过多次调用then()附加更多结果处理逻辑.<br>
@ Promise 需要封装，但是强大，具有很强的侵入性。<br>
@ 纯粹的函数则较为轻量，但功能相对弱小。<br>
#### Promise中的多异步协作
多个异步调用
```js
Deferred.prototype.all = function(promise){
    var count = promises.length;
    var that = this;
    var results = [];
    promises.forEach(function(promise,i){
        promise.then(function(data){
            count--;
            results[i] = data;
            if(count === 0){
                that.resolve(results);
            }
        },function(err){
            that.reject(err);
        });
    });
    return this.promise;
}
```
🌰 ：
```js
var promise1 = readFile('q.txt');
var promise2 = readFile('r.txt');
var deferred = new Deferred();
deferred.all([promise1,promise2]).then(function(results){
// success data
},function(err){
// error data
});
```
这里的all()方法抽象多个异步操作。但是有缺陷，一个失败，全盘皆输。
#### Promise的进阶知识
Promise 的秘诀其实在于对队列的操作。<br>
解决同步调用问题的答案也就是采用Deferred模式。<br>
Pyramid of Doom -- 恶魔金字塔
##### 支持序列执行的Promise
链式调用

