#### 如果你想列出当前目录以及子目录下的所有扩展名为".txt"的文件
* find . -name "*.txt"
* find . ".txt"查找".",".txt"这两个目录
* ls只能显示当前目录的文件

#### Linux下查看服务程序占用的端口命令是？
netstat -apn
* ps - aux 查看所有进程
* watch 可以帮你监测一个命令的运行结果
* isof是一个列出当前系统打开文件的工具

#### Linux是一种自由软件的主要理由Linux的源代码是公开的

#### Linux 64，运行结果
```c
int intValue = 1024;
char str[] = “Tencent”;
const char* ch = str;
sizeof(intValue) = __a__;
sizeof(str) = ___b__;
sizeof(ch) = __c___;
```
int 4个字节固定，指针 8个字节，char 1个字节，short int 2个字节，float 4个字节，double 8个字节，long 8个字节，unsigned long 8个字节，long long 8个字节

#### 为了将当前目录下的归档文件myftp.tgz解压缩到/tmp目录下，用户可以使用命令
tar xvzf myftp.tgz -C /tmp<br>
解压到指定目录下，所以在待解压文件名后加上-C参数，这是代表后面要加解压路径

#### uncompress 解压缩Z文件 压缩compress

#### chown chmod 更改权限
从左至右，1-3位数字代表文件所有者的权限，4-6位数字代表同组用户的权限，7-9数字代表其他用户的权限。 <br>
而具体的权限是由数字来表示的，读取的权限等于4，用r表示；写入的权限等于2，用w表示；执行的权限等于1，用x表示； <br>
通过4、2、1的组合，得到以下几种权限：0（没有权限）；4（读取权限）；5（4+1 | 读取+执行）；6（4+2 | 读取+写入）；7（4+2+1 | 读取+写入+执行）<br>

#### 命令：[-z””]&&echo 0 ||echo 1的输出是什么
```
bogon:~ transcheung$ [ -z "" ] && echo 0 || echo 1
0
bogon:~ transcheung$ [ -z "" ] && echo 5 || echo 4
5
bogon:~ transcheung$ [ -z "" ] && echo 9 || echo 4
9
bogon:~ transcheung$ [ -z "" ] && echo 9 || echo 0
9
bogon:~ transcheung$ [ -z "cccc" ] && echo 9 || echo 1
1
bogon:~ transcheung$ [ -z "cccc" ] && echo 9 || echo 6
6
```
z先判断是否无值，成功再执行echo。

#### 用户线程和内核线程的调度
* 内核线程一直处于内核态的轻量级进程，LWT，根本不会切换到用户态
* 一个协程阻塞，其他都会阻塞
* 协程调度不进入内核态
* 内核线程的跟进程调度一样，可以利用多核优化

#### ls>c 命令产生的输出为当前路径下的所有文件名，没有c文件就先生成

#### 在某特定文件夹内查找内容含有"abc"的文件 grep "abc" *

#### 现在将/目录下的www文件权限改为只有主用户有执行的权限的有
* chmod 100 /www
* chmod u+x ,g-x,o-x /www

#### 终止一个前台进程可能用到的命令和操作 kill和ctrl+c
halt命令关闭系统

#### socket描述符
* socket 存在两种方式 阻塞和非阻塞
* 系统调用read从socket中读取数据时，当read返回0的时候，表示socket中数据读取完毕
* 如果socket设置成非阻塞模式，当socket的输入缓冲区没有可读数据时，read操作会返回错误
* 在阻塞socket上调用write函数发送数据，函数返回时，可能错误，会返回-1，并不代表发出去了

#### 在一台Linux服务器上通过rpm方式安装了dhcp软件包，下列关于dhcp服务器配置文件“dhcpd.conf”说法正确的是
* dhcpd.conf文件缺省不存在，需要手工建立
* dhcpd.conf文件的配置可以参考模板文件“dhcpd.conf.sample”进行
