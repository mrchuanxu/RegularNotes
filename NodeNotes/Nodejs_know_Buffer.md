# 理解Buffer
需要处理大量二进制数据，JavaScript自有的字符串远远不能满足需求，于是有了Buffer。<br>
### Buffer 结构
Buffer是一个像Array的对象，但它主要用于操作字节。下面我们从模块结构和对象结构的层面来认识它。<br>
#### 模块结构
Buffer是一个典型的Javascript与C++结合的模块，它将性能相关部分用C++实现，将非性能相关的部分用JavaScript实现
如图

**Buffer所占用的内存不是通过V8分配的，属于堆外内存。** 由于V8垃圾回收性能的影响，将常用的操作对象用更高效和专有的内存分配回收策略来管理是个不错的思路。<br>
Buffer在Node进程启动时就已经加载了，所以无需通过require()即可直接使用。<br>
##### Buffer 对象
Buffer对象类似数组，它的元素为16进制的两位数，即0-255的数值。
```js
var str = "node";
var buf = new Buffer(str,'utf-8');
console.log(buf);
buf.length;
buf[0]; // 元素值是一个0-255的随机值
buf[1] = 100; // 如果给元素赋值小于0，就将该值逐次加256，直到得到一个0-255之间的整数。如果大于就逐次减256，直到得到一个0-255之间的整数。如果是小数，就舍弃小数部分，只保留整数部分。
```
<Buffer 6e 6f 64 65>
不同编码的字符串占用的元素个数各不相同。<br>
Buffer受Array类型的影响很大，可以访问length属性获得长度。亦可以通过下标访问刚刚初始化的Buffer元素<br>
##### Buffer内存分配
Buffer对象的内存分配不是在V8的堆内存中，而是在Node的C++层面实现内存的申请的。因为处理大量的字节数据不能采用需要一点内存就向操作系统申请一点内存的方式，这可能造成大量的内存申请的系统调用，对操作系统的有一定的压力。<br>
为了高效地使用申请来的内存，Node采用了slab分配机制。slab是一种动态内存管理机制。<br>
slab就是一块申请好的固定大小的内存区域。<br>
* full: 完全分配状态<br>
* partial: 部分分配状态<br>
* empty: 没有被分配的状态<br>
当我们需要一个Buffer对象，可以通过`new Buffer(size)`。<br>
Node以8KB为界限来区分Buffer是大对象还是小对象：`Buffer.poolSize = 8*1024;` <br>
##### 分配小Buffer对象
如果指定Buffer的大小小于8KB，Node会按照小对象的方式进行分配。Buffer的分配过程中主要使用一个局部变量pool作为中间处理对象，处于分配状态的slab单元都指向它。<br>
```js
var pool;
function allocPool(){
  pool = new SlowBuffer(Buffer.poolSize);
  pool.used = 0;
};
```
如图
`new Buffer(1024);`<br>
这次构造将会去检查pool对象，如果pool没有被创建，将会创建一个新的slab单元指向它`if(!pool || pool.length - pool.used < this.length) allocPool();`<br>
同时当前Buffer对象的parent属性指向该slab，并记录下是从这个slab的哪个位置（offset）开始使用的，slab对象自身也记录被使用了多少字节。
```js
this.parent = pool;
this.offset = pool.used;
pool.used += this.length;
if(pool.used & 7) pool.used = (pool.used + 8)& ~7;
```
如图
这时候的slab状态为partial。<br>
创建buffer会判断slab剩余空间，不够就再重新构造新的slab，会造成剩余空间的浪费。<br>
同一个slab可能分配给多个Buffer对象使用，只有这些小buffer对象在作用域释放并都可以回收时，slab的8KB空间才会被回收。<br>
##### 分配大Buffer对象
如果需要超过8KB的Buffer对象，将会直接分配一个SlowBuffer对象作为slab单元，这个slab单元将会被这个大Buffer对象独占。
```js
this.parent = new SlowBuffer(this.length);
this.offset = 0;
```
上面提到的Buffer对象都是js层面的，能够被V8的垃圾回收标记回收。但是其内部的parent属性指向的SlowBuffer对象却来自于Node自身C++中的定义，是C++层面上的Buffer对象，所用内存不在V8的堆中。<br>
##### 小结
简而言之，真正的内存是在Node的C++层面提供的，js层面只是使用它。当进行小而频繁的Buffer操作时，采用slab的机制进行预先申请和事后分配，使得js到操作系统之间不必有过多的内存申请方面的系统调用。对于大块的Buffer而言，则直接使用C++层面提供的内存，而无需细腻的分配操作。
### Buffer的转换
Buffer对象可以与字符串之间相互转换。支持<br>
`ASCII,UTF-8,UTF-16LE/UCS-2,Base64,Binary,Hex`;<br>
#### 字符串转Buffer
字符串转Buffer对象主要是通过构造函数完成的：`new Buffer(str,[encoding]);`<br>
通过构造函数转换的Buffer对象，存储的只能是一种编码类型。encoding参数不传递时，默认按UTF-8编码进行转码和存储。<br>
一个Buffer对象可以存储不同编码类型的字符串转码的值，调用write()方法可以实现该目的`buf.write(string,[offset],[length],[encoding])`;<br>
需要小心的是。每种编码所用的字节长度不同，将Buffer反转回字符串时需要谨慎处理。<br>
#### Buffer转字符串
`buf.toString([encoding],[start],[end])`<br>
#### Buffer不支持的编码类型
`Buffer.isEncoding(encoding)`;// 此函数可以用来判断编码是否支持转换<br>
iconv-lite采用纯js实现，性能较好
```js
var iconv = require('iconv-lite');
// Buffer 转字符串
var str = iconv.decode(buf,'win1251');
var buf = iconv.encode('sssssssss','win1251');
```
唔得？唔得就❓啦。单字节就输出❓，多字节就输出❔<br>
### Buffer的拼接
Buffer在使用场景中，通常是以一段一段的方式传输。
```js
var fs = require('fs');
var rs = fs.createReadStream('test.md');
var data = '';
rs.on('data',function(chunk){
  data += chunk;
});
rs.on('end',function(){
  console.log(data);
});
```
一旦遇到宽字节，就很多❓。
#### 乱码如何产生
由于限定了Buffer对象的长度为11，因此，只读流需要读取7次才能完成整段读取，所以应为buf.toString()默认以UTF-8为编码，中文字在UTF-8下占3个字节。所以会将剩下的以乱码形式显示。
#### setEncoding()与string_decoder()
`readable.setEncoding(encoding)`该方法的作用是让data事件中传递的不再是一个Buffer对象，而是编码后的字符串。<br>
```js
var rs = fs.createReadStream('test.md',{highWaterMark:11});
rs.setEncoding('utf-8');
```
在调用setEncoding()时，可读流对象在内部设置了一个decoder对象，每次data事件都通过该decoder对象进行Buffer到字符串的解码，然后传递给调用者。是故设置编码后，data不再收到原始的Buffer对象。但是这依旧无法解释为何设置编码后乱码的问题被解决掉了，因为无论如何转码，总是存在宽字节字符串被截断的问题。<br>
其实是因为decoder，所以乱码问题得以解决。<br>
#### 正确拼接Buffer
下面就剩将多个小Buffer对象拼接为一个Buffer对象，然后通过iconv-lite一类的模块来转码这种方式。+=的方式显然不行，那么正确的Buffer拼接方法如下
```js
var chunks = []; // 用一个数组来存储
var size = 0;
res.on('data',function(chunk){
    chunks.push(chunk); // 拼接一起
    size+=chunk.length;
});
res.on('end',function(){
  var buf = Buffer.concat(chunks,size); // 调用Buffer.concat()方法生成一个合并的Buffer对象
  var str = iconv.decode(buf,'utf-8');
  console.log(str);
});
```
### Buffer与性能
提高字符串到Buffer的转换效率，可以很大程度地提高网络吞吐率。<br>
通过预先转换静态内容为Buffer对象，可以有效地减少CPU的重复使用，节省服务器资源。在Node构建的web应用中，可以选择将页面中的动态内容和静态内容分离，静态内容部分可以通过预先转换为Buffer的方式，使性能得到提升。由于文件自身是二进制数据，所以不需要改变内容的场景下，尽量只读取Buffer，然后直接传输，不做额外的转换，避免损耗。<br>
fs.createReadStream()的工作方式就是在内存中准备一段Buffer，然后在fs.read()读取时逐步从磁盘中将字节复制到Buffer中。完成一次读取时，则从这个Buffer中通过slice()方法取出部分数据作为一个小Buffer对象，再通过data时间传递给调用方。如果用完就 **重新分配**，有剩余，就继续使用<br>
```js
// 为分配一个新的Buffer对象的操作
var pool;
function allocNewPool(poolSize){
  pool = new Buffer(poolSize);
  pool.used = 0;
};
```
理想状况下，每次读取的长度就是用户指定的highWaterMark。但是有可能读到了文件结尾，或者文件本身就没有指定的highWaterMark那么大，这个预先指定的Buffer对象将会有部分剩余，不过好在这里的内存可以分配给下一次读取时使用。pool是常驻内存的，只有当pool单元剩余数量小于128（kMinPoolSpace）字节时，才会重新分配一个新的buffer对象。
```js
if(!pool || pool.length - pool.used < kMinPoolSpace){
  // discard old pool
  pool = null;
  allocNewPool(this._readableState.highWaterMark);
}
```
* highWaterMark设置对Buffer内存的分配和使用有一定影响。<br>
* highWaterMark设置过小，可能导致系统调用次数过多。（该值越大。读取速度越快）<br>
文件流读取基于BUffer分配，Buffer则给予SlowBuffer分配，这可以理解为两个唯独的分配策略。<br>
由于fs.createReadStream()内部采用fs.read()实现，将会引起对磁盘的系统调用，对于大文件而言，highWaterMark的大小决定会触发系统调用和data时间的次数。<br>
### 总结
这么大一篇幅，只想说明 **字符串和Buffer之间有实质上的差异**。Buffer是二进制数据，字符串与Buffer之间存在编码关系。
