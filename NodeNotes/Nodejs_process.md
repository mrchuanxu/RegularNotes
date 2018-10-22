# 玩转进程
Node在选型时决定在V8引擎之上构建，也就意味着它的模型与浏览器类似。我们的JavaScript将会运行在单个进程的单个线程上。它带来的好处是：程序状态是单一的，在没有多线程的情况下，没有锁、线程同步问题，操作系统在调度时也因为较少上下文的切换，可以很好地提高CPU的使用率。<br>
但是！单进程单线程并非完美的结构，如今CPU基本均是多核的，真正的服务器（非VPS）往往还有多个CPU。一个Node进程只能利用一个核，这将抛出Node实际应用的第一个问题 ❓ 如何充分利用多核CPU服务器？<br>
另外，由于Node执行在单线程上，一旦单线程上抛出的异常没有被捕获，将会引起整个进程的崩溃。所以又来问一个问题 ❓ 如何保证进程的健壮性和稳定性?<br>
在这两个问题中，前者只是利用率不足，后者对于实际产品化带来一定的顾虑。<br>
**这是重点，所以需要标记！！！** 从严格的意义上而言，Node并非真正的单线程架构，Node自身还有一定的I/O线程存在，这些线程由底层libuv处理，这部分线程对于JavaScript开发者而言是透明的，只在C++扩展开发时才会关注到。<br>
### 服务模型变迁
石器时代（同步）->青铜时代（复制进程）->白银时代（多线程）->黄金时代（事件驱动）。
### 多进程架构
理想状态下每个进程各自利用一次CPU，一次实现多核CPU的利用。所幸，Node提供了child_process模块，并且也提供了child_process.fork()函数以供我们实现进程的复制。<br>
```js work.js
 > var http = require('http');
undefined
> http.createServer(function(req,res){
... res.writeHead(200,{'Content-Type':'text/plain'});
... res.end('hello,world');
... }).listen(Math.round(1+Math.random()*1000),'127.0.0.1');
```
```js master.js
> var fork = require('child_process').fork;
undefined
> var cpus = require('os').cpus();
undefined
> for(var i = 0;i<cpus.length;i++){
    fork('./work.js'); // 通过fork()复制的进程都是一个独立的进程，这个进程中有着独立而全新的V8的实例。fork()进程是昂贵的。
    // 好在Node通过事件驱动的方式在单线程上解决了大并发的问题，这里启动多个进程只是为了充分将CPU资源利用起来，而不是为了解决并发问题。
}
```
`ps aux | grep work.js`查看进程数<br>
Master-worker模式，主进程和工作进程，典型的分布式架构中用于并行处理业务的模式，具备较好的可伸缩性和稳定性。主进程不负责具体的业务处理，而是负责调度或管理工作进程，它是趋向于稳定的。<br>
#### 创建子进程
child_process模块给予Node可以随意创建子进程(child_process)的能力。<br>
> spawn():启动一个子进程来执行命令<br>
> exec():启动一个子进程来执行命令，与spawn()不同的是其接口不同，它有一个回调函数获知子进程的状况。<br>
> execFile():启动一个子进程来执行可执行文件<br>
> fork(): 与spawn()类似，不同点在于它创建Node的子进程只需指定要执行的js文件模块即可。<br>
spawn()与exec()、execFile()不同的是，后两者创建时可以指定timeout属性设置超时时间，一旦创建的进程运行超过设定的时间将会被杀死。<br>
exec()与execFile()不同的是，exec()适合执行已有的命令，execFile()适合执行文件。
```js
var cp = require('child_process')
cp.spwan('node',['work.js']);
cp.exec('node worker.js',function(err,stdout,stderr){
 // some code
});
cp.execFile('work.js',function(err,stdout,stderr){

});
cp.fork('./work.js');
```
#### 进程间通信
在Master-Worker模式中，要实现主进程管理和调度工作进程的功能，需要主进程和工作进程之间的通信。对于child_process模块，创建好了子进程，然后与父子进程间通信是十分容易的。<br>
在前端浏览器中跟，JS主线程与UI渲染共用同一个线程。 **执行js的时候，UI渲染是停滞的，渲染UI时，js时停滞的**，两者相互阻塞。<br>
WebWorker拯救你！<br>
主线程与工作线程之间通过onmessage()和postMessage()进行通信，子进程对象则由send()方法实现主进程向子进程发送数据，message事件实现收听子进程发来的数据，与API在一定程度上相似。通过消息传递内容而不是共享或直接操作相关资源，这是较为轻量和无依赖的做法<br>
### 集群，cluster
