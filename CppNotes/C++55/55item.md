## Effective C++ 55 items
### View C++ as a federation of languages
C,Object-Oriented C++, Template C++, STL<br>
高效编程守则随着这四个联邦政府的状况而变化。<br>
### Prefer const,enum and inline to #define
对于单纯常量，最好以const对象以enum替换#define<br>
对于形似函数的宏（macros）最好改用inline函数替换#define<br>
`#define`在预处理器，编译器与预处理器协同工作，但宁可编译器替换预处理器。<br>
### Use const when possible
const不能调用non-const
### Make sure that objects are initialized when they are used
初始化 a(int num):num(num);
### Know what functions C++ silently writes and calls
析构函数，构造函数，copy函数，copy assignmant函数
### Expilictly disallow the use of compiler-generated functions you do not want
声明为private
