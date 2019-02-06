### 牛客网刷题错题集
#### C/C++
##### 以下只有在使用时才为该类型变量分配内存的存储类说明是 auto和register<br>
解释：auto根据数据类型分配内存，register在使用时分配CPU寄存器地址
##### 注意看清楚每一行代码
```cpp
#include
using namespace std;
 
int func(int n)
{
    if (n < 1) // ⚠️ 这里如果fcun = 0，那么还会返回1
        return 1;
    else
        return n + func(n - 1);
    return 0;
}
int main()
{
    cout << func(5) << endl;
    return 0;
}
```
##### 下列程序段的输出结果是  0085.6% 这里会四舍五入！！！
```cpp
float k = 0.8567;
printf("%06.1f%%",k*100);
```
6是用六个位置，0是指第一个非零数字前用零填充，.1小数点后保留1位小数，%%输出一个%。<br>

##### 分清楚字符串是常量，不能改变<br>
```cpp
char* s1 = "Hello world";
char s2[] = "Hello world";
s1[2] = 'E';     // 1
s2[2] = 'E';     // 2
*(s1 + 2) = 'E';  // 3
*(s2 + 2) = 'E';  // 4
```
指针指向的那个字符串是常量！！！const char* <br>

* 下面哪种方法不能用于文本加密🔐<br>
1. RSA。是一个支持变长密钥的公共密钥算法，需要加密的文件块的长度也是可变的，非对称短发
2. RC2和RC4.对称算法，用变长密钥对大量数据进行加密🔐
3. DES。对称算法，数据加密标准，速度较快，适用于加密大量数据的场合
4. MD5.严格来说不是加密算法，只能说是摘要算法(单向不可逆，不能用于文本加密🔐，可以用来签名，校验数据的完整性)

##### 对象的数组的数组名永远不可能是指针，这是两个类型，只不过函数传递时，数组名会退化成指针

##### 判断以下程序的输出结果
```cpp
#include <string.h>
#include <stdio.h>

void main()
{
char x[] = "STRING";
x[0] = 0;
x[1] = '\0';
x[2] = '0';
printf("%d %d\n", sizeof(x), strlen(x));
}
```
7,0。strlen根据ascii码为0的字符来判断是否结束，'\0'ascii码是0，0本身的值就是0，'0'不能看成是0。sizeof获得的是字节的大小

##### 继承 64位系统，sizeof(B)是多少
```cpp
class A
{
public:
    void *p1;
private:
    void *p2;
protected:
    void *p3;
};
class B: public A {};
```
继承了全部变量，但是并不是都能访问。3*8=24;

// DATE:2019 2 6