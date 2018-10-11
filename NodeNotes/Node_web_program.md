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
