### View C++ as a federation of languages
C,Object-Oriented C++, Template C++, STL<br>
高效编程守则随着这四个联邦政府的状况而变化。<br>
### Prefer const,enum and inline to #define
对于单纯常量，最好以const对象以enum替换#define<br>
对于形似函数的宏（macros）最好改用inline函数替换#define<br>
`#define`在预处理器，编译器与预处理器协同工作，但宁可编译器替换预处理器。<br>
