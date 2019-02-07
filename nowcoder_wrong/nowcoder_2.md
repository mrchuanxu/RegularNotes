#### C++语言中，64位环境下double类型数据占8个字节。

类型|32位|64位
|--|--|--|
char|1|1
int|4|4\8
long|4|8
float|4|4
double|8|8
指针|4|8

#### 程序设计
```cpp
#include <iostream>
using namespace std;
 
class A
{
public:
    A()
    {
        printf("A");
    }
};
 
int main()
{
    A *p1 = new A;
    A *p2 = (A *)malloc(sizeof(A));
     // sizeof为1，这条语句创建一个大小为1的A的指针数组，但是没有创建任何A对象，因此不输出A
    return 0;
}
```
输出A，但是没有释放内存。malloc只是分配内存，不调用类的构造函数构建

#### 设C语言中，一个int型数据在内存中占2个字节，则unsigned int数据类型的取值范围为 0-2^16-1
2个字节也就是16位

#### fseek函数的功能就是能将文件的位置指针进行定位，以实现对文件的随机读写，当然文件的顺序读写就更不成问题。

#### %m.ns 输出占m列，但只取字符串左端n个字符。这n个字符输出在m列的右侧，左补空格
```c
int main(void)
{
printf("%s , %5.3s\n","computer","computer");
return 0;
}
```
输出computer,com

#### 0x7FFFFFFFFFFFFFFF+0x8000000000000000=0xFFFFFFFFFFFFFFFF 转为源码 = -1
变量a是一个64位有符号的整数，初始值用16进制表示为：0x7FFFFFFFFFFFFFFF;变量b是一个64位有符号的整数，初始值用16进制表示为：0x8000000000000000。则a+b的结果用10进制表示为多少？

#### 将析构函数设为私有
在C++中，为了让某个类只能通过new来创建（即如果直接创建对象，编译器将报错），应该？<br>
编译器在为类对象分配栈空间时，会先检查类的析构函数的访问性，其实不光是析构函数，只要是非静态的函数，编译器都会进行检查。如果类的析构函数是私有的。则编译器不会在栈空间上为类对象分配内存。因此析构函数设为私有，类对象就无法建立在栈上了，只能在堆上(动态new)分配类对象。

#### 'a'<c<='z'
```c
void main() 
{
char c=’a’;
if ('a'<c<='z') printf ("Low”);
else printf("UP");
}
```
输出LOW，关系运算符具有左结合性。

#### \\、\123 一个标识符 
```c
char s[]="\\123456\123456\t";
printf("%d\n",strlen(s));
```
输出12

2019 02 07