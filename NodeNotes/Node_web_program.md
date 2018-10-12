# 网络编程
Node提供了net、dgram、http、https这四个模块，分别用于处理TCP、UDP、HTTP、HTTPS适用于服务器端和客户端。<br>
## 构建TCP服务
目前大多数应用都是基于TCP搭建而成的。<br>
### TCP
TCP->传输控制协议（Transfer，Control，Protocol）。 <br>
OSI模型->七层->物理层(网路物理硬件)->数据链路层（网络特有的链路接口）->网络层（IP）->传输层（TCP/UDP）->会话层（通信链接/维持会话）->表示层（加密/解密 .etc）->应用层（HTTP,SMTP,IMAP .etc）<br>
TCP是面向链接的协议，其显著的特征是在传输之前需要3次握手形成会话，如图
<br>
只有会话形成之后，服务器端和客户端之间才能互相发送数据。在创建会话的过程中，服务器端和客户端分别提供一个 **套接字**， 这两个套接字共同形成一个链接。服务器端与客户端则通过套接字实现两者之间链接的操作。<br>
### 创建TCP服务器端
```js
var net = require('net');
undefined
var server = net.createServer(function(socket){
... socket.on('data',function(data){
..... socket.write('hello');
..... });
... socket.on('end',function(){
....... console.log('oout');
....... });
... socket.write('welcome');
... });

server.listen(9999,function(){
  console.log('server bound');
});
```
我们通过net.createServer(listener)即可创建一个TCP服务器，listener是链接事件connection的侦听器。
```js
var server = net.createServer();
server.on('connection',function(socket){
  // new connection
});
server.listen(9999);
```
### TCP服务的事件
代码分为服务器事件和事件。<br>
#### 服务器事件
对于通过net.createServer()创建的服务器而言，它是一个EventEmitter实例。<br>
* listening:在调用server.listen()绑定端口或者Domain Socket后触发，简洁写法为 `server.listen(port,listeningListener)`，通过listen()方法的第二个参数传入。<br>
* connection: 每个客户端套接字连接到服务器端时触发，简洁写法为通过`net.createServer()`，最后一个参数传递。<br>
* close: 当服务器关闭时触发，在调用server.close()后，服务器将停止接受新的套接字链接，但保持当前存在的链接，等待所有链接都断开后，会触发该事件。<br>
* error: 当服务器发生异常时，将会触发该事件。比如侦听一个使用中的端口，将会触发一个异常，如果不侦听error事件，服务器将会抛出异常<br>
#### 连接事件
服务器可以同时与多个客户端保持🔗 连接，对于每个连接而言是经典的可写可读Stream对象。Stream对象可以用于服务器端和客户端之间的通信，既可以通过data事件从一端读取另一端发来的数据，也可以通过write()方法从一端向另一端发送数据。<br>
* data: 当一端调用write()发送数据时，另一端会触发事件，事件传递的数据即是write()发送的数据。<br>
* end: 当连接中的任意一端发送了FIN数据时，将会触发该事件。<br>
* connect: 该事件用于客户端，当套接字与服务器端🔗 连接成功时会被触发。<br>
* drain: 当任意一端调用write()发送数据时，当前这端会触发该事件。<br>
* error: 当异常发生时，触发该事件。<br>
* close: 当套接字完全关闭时，触发该事件。<br>
* timeout: 当一定时间后连接不再活跃时，该事件将会被触发，通知用户当前该连接已经被闲置了。<br>
另外，由于TCP套接字是可写可读的Stream对象，可以利用pipe()方法巧妙地实现管道操作。<br>
```js
var net = require('net');
var server = net.createServer(function(socket){
  socket.write('Echo server\r\n');
  socket.pipe(socket);
});
server.listen(1337,'127.0.0.1');
```
⚠️ TCP针对网络中的小数据包有一定的优化策略： **Nagle算法**。如果发送一个字节的内容而不优化，网络中将充满只有极少数有效数据的数据包，将十分浪费网络资源。<br>
Nagle，要求缓冲区的数据达到一定数量或者一定时间后才将其发出，所以小数据包将会被Nagle算法合并，以此来优化网络。这种优化虽然使网络带宽被有效地使用，但是数据有可能被延迟发送。<br>
在Node中，由于TCP默认启用了Nagle算法，可以调用socket.setNoDelay(true)去掉Nagle算法，使得write()可以立即发送数据到网络中。<br>
⚠️ 尽管网络的一端调用write()会触发另一端的data事件，但是并不意味着每次write()都会触发一次data事件，在关闭掉Nagle算法后，另一端可能会将接收到的多个小数据包合并，然后只触发一次data事件。<br>
### 构建UDP服务
用户数据包协议，与TCP一样同属于网络传输层。UDP与TCP最大的不同时UDP不是面向🔗 连接的。TCP中连接一旦建立，所有的会话都基于连接完成，客户端如果要与另一个TCP服务通信，需要另创建一个套接字来完成连接。但在UDP中，一个套接字可以与多个UDP服务通信，他虽然提供面向事务的简单不可靠信息传输服务，在网络差的情况下存在丢包严重的问题，但是由于它无需连接，资源消耗低，处理快速且灵活，所以常常应用在那种偶尔丢一两个数据包也不会产生重大影响的场景，比如音频线、视频等。UDP目前应用很广泛，DNS即是基于它实现的。<br>
#### 创建UDP套接字
创建套接字十分简单，UDP套接字一旦创建，既可以作为客户端发送数据，也可以作为服务器端接收数据。
```js
var dgram = require('dgram');
var socket = dgram.createSocket('udp4');
```
#### 创建UDP服务器端
若想让UDP套接字接收网络消息，只要调用dgram.bind(port,[address])方法对网卡和端口进行绑定即可。
```js
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
server.on('message',function(msg,rinfo){
  console.log('server got:'+msg+'from'+rinfo.address+':'+rinfo.port);
});

server.on('listening',function(){
  var address = server.address();
  console.log('server listening'+address.address+':'+address.port);
});
server.bind(42312);
```
#### 创建UDP客户端
接下来我们创建一个客户端与服务器端进行对话
```js
var dgram = require('dgram');
var message = new Buffer('fuck nodejs');
var client = dgram.createSocket('udp4');
client.send(message,0,message.length,42312,'localhost',function(err,bytes){
  client.close();
});
```
显示为
![udpshow](./img/nodeudp.png "udp client and server")<br>
当套接字对象用在客户端时，可以调用send()方法发送消息到网络中。`socket.send(buf,offset,length,address,[callback])`<br>
buffer,buffer的偏移，buffer的长度，目标端口，目标地址，发送完成后的回调。与TCP套接字的write相比，send方法的参数列表相对复杂，但是它更灵活的地方在于可以随意发送数据到网络中的服务器端，而TCP如果要发送数据给另一个服务器端，则需要重新通过套接字构造新的连接。<br>
#### UDP套接字事件
UDP套接字相对于TCP套接字使用起来更简单，它只是一个EventEmitter的实例，而非Stream的实例<br>
* message: 当UDP套接字侦听网卡端口后，接收到信息时触发该事件，触发携带的数据为消息Buffer对象和一个远程地址信息。<br>
* listening: 当UDP套接字开始侦听时触发该事件。<br>
* close: 调用close()方法时触发该事件，并不再触发message事件。如需再次触发message事件，重新绑定即可。<br>
* error: 当异常发生时触发该事件，如果不侦听，异常将直接抛出，是进程推出。<br>
### 构建HTTP服务
TCP与UDP都属于网络传输层协议，如果要构造高效的网络应用，就应该从传输层进行着手。<br>
但是HTTP和SMTP已经绰绰有余了，Node提供了基本的http和https模块用于HTTP和HTTPS的封装。<br>
实现一个HTTP服务器
```js
var http = require('http');
http.createServer(function(req,res){
  res.writeHead(200,{'Content-type':'text/plain'});
  res.end('hello,world\n');
}).listen(1337,'127.0.0.1');
```
这一段代码能维持的并发量和QPS都是不容小觑。
#### HTTP
应用层协议。在HTTP的两端是服务器和浏览器，即著名的B/S模式。
#####
