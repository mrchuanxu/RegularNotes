本次笔记记录第8，9章，IO库与顺序容器。<br>

第8章，介绍基本的IO库设施。除了使用标准库读写与控制台窗口相关联的流之外，我们还将学习其他一些库类型，可以帮助我们读写命名文件以及完成到string对象的内存I/O操作。<br>
其实，标准库的核心是很多容器类和一族泛型算法，这些设施能帮助我们编写简洁高效的程序。标准库会去关注那些薄记操作的细节，特别是内存管理，这样我们的程序就可以将全部注意力投入到需要求解的问题上。<br>
第九章将更多地介绍vector相关内容，这一章会涉及其他顺序容器。<br>
# IO库
C++语言不直接处理输入输出，而是通过一族定义在标准库中的类型类处理IO。这些类型指出哦才能够设备读取数据、向设备写入数据的IO操作，设备可以是文件、控制台窗口等。还有一些类型允许内存IO，即，从string读取数据，向string写入数据<br>
IO库定义了读写内置类型值的操作。此外，一些类，如string，通常也会定义类似的IO操作，来读写自己的对象。<br>
**我们的程序已经使用了很多IO库设施。<br>**
istream,ostream,cin,cout,cerr,>>,<<,getline函数<br>
## IO类
到目前为止，我们已经使用过的IO类型和对象都是操纵char数据的。默认情况下，这些对象都是关联到用户的控制窗台的。<br>
为了支持不同类型的io处理操作，istream定义了用于读写流的基本类型，fstream定义了读写命名它<br>
### IO对象无拷贝或赋值
```cpp
ofstream out1,out2;
```
我们不能拷贝或对IO对象赋值<br>
这次我写了一个读写文件的C++程序，以下为代码演示并注释<br>
```cpp
#include <iostream>

class iostrm{
public:
iostrm(){}
istream& inputStream(istream& istrm){
string buf;
while(is >> buf)
cout<< buf<<endl;
istrm.clear(); //对流进行复位！
return istrm;
}
}
```
### 条件状态
IO操作一个与生俱来的问题是可能发生错误。一些错误是可恢复的，而其他错误则发生在系统深处，已经超出了 应用程序可以修正的范围。IO类的一些函数，可以帮助我们访问和操纵流的条件状态。<br>
strm::iostate strm一种IO类型，iostate是一种机器相关的类型，提供了表达条件状态的完整功能。<br>
strm::badbit strm::badbit用来指出流已崩溃<br>
strm::failbit  strm::failbit用来指出一个IO操作失败<br>
strm::eofbit  strm::eofbit用来指出流到达了文件结束<br>
strm::goodbit 用来指出流未处于错误状态。此值保证为零<br>
s.eof() 若流s的eofbit置位，则返回true<br>
s.fail() 若s的failbit或badbit置位，则返回true<br>
s.good =>有效状态<br>
s.clear() 将流s中所有条件状态位复位，将流的状态设置为有效。返回void<br>
s.clear(flags) 根据给定的flags标志位，将流s中对应状态位复位。flags的类型为strm::iostate。返回void 同 s.setstate(flags)<br>
s.rdstate() 返回流s的当前状态，返回值类型为strm::iostate<br>
### 查询流的状态
IO库定义了一个与机器无关的iostate类型，它提供了表达流状态的完整功能。这个类型应作为一个位集合来使用。<br>
badbit表示系统级的错误，如不可恢复的读写错误。通常情况下，一旦badbit被置位，如期望读取数值却读出一个字符等错误。这种问题通常是可以修正的，流还可以继续使用。如果到达文件结束位置，eofbit和failbit都会被置位。goodbit的值为0，表示流为发生错误。如果badbit、failbit和eofbit任一个被置位，则检测流状态的条件会失败。<br>
标准库还定义了一组函数来查询这些标志位的状态。操作good在所有错误位均 未置位的情况下返回true，而bad、fail和eof则在对应错误被置位时返回true。此外，在badbit被置位时，fail也会返回true。这意味着，使用good或fail是确定eof和bad操作只能表示特定的错误。<br>
### 管理条件状态
流对象的rdstate成员返回一个iostate值，对应流的当前状态。setstate操作将给定条件位置位，表示发生要了对应错误。clear成员是一个重载的成员：它有一个不接受参数的版本，而另一个版本接受一个iostate类型的参数。<br>
clear不接受参数的版本清除（复位）所有错误标志位。执行clear()后，调用good会返回true。我们可以这样使用这些成员：<br>
```cpp
auto old_state = cin.rdstate(); //记住cin的当前状态
cin.clear();  //使cin有效
process_input(cin);  //使用cin
cin.setstate(old_state); //将cin置为原有状态
```
带参数的clear版本接受一个iostate值，表示流的新状态。为了复位单一的条件状态位，我们首先用rdstate读出当前条件状态，然后用位操作将所需位复位来生成新的状态。例如，下面的代码将failbit和badbit复位，但保持eofbit不变：
```cpp
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
```
### 管理输出缓冲
每个输出流都管理一个缓冲区，用来保存读写的数据。例如，如果执行下面的代码<br>
```cpp
os<<"please enter a value:";
```
文本串可能立即打印出来，但也有可能被操作系统保存在缓冲区中，随后再打印。有了缓冲机制，操作系统就可以将程序的多个输出操作组合为单一的系统级写操作。由于设备的写操作可能很耗时，允许操作系统将多个输出操作组合为单一的设备写操作可以带来很大的性能提升<br>
导致缓冲刷新（即，数据真正写到输出设备或文件）的原因有很多<br>
@程序正常结束，作为main函数的return操作的一部分，缓冲刷新被执行。<br>
@缓冲区满时，需要刷新缓冲，而后新的数据才能继续写入缓冲区<br>
@我们可以使用操纵符如endl来显示刷新缓冲区<br>
@在每个输出操作之后，我们可以用操纵符unitbuf设置流的内部状态，来清空缓冲区。默认情况下，对cerr是设置unitbuf的，因此写到cerr的内容都是刷新的。<br>
@一个输出流可能被关联到另一个流。在这种情况下，当读写被关联的流时，关联的流的缓冲区会被刷新。例如，默认情况下，cin和cerr都关联到cout。因此，读写cin或写cerr都会导致cout的缓冲区被刷新<br>
### 刷新输出缓冲区
我们已经使用过操纵符endl，它完成换行并刷新缓冲的工作。IO库中还有两个类似的操纵符：flush和ends。flush刷新缓冲区，但不输出任何额外的字符；ends向缓冲区插入一个空字符，然后刷新缓冲区：<br>
```cpp
cout<<"hi!"<<endl;
cout<<"hello"<<flush;
cout<<"hi"<<endl;
```
### unitbuf操纵符
如果想在每次输出操作后都刷新缓冲区，我们可以使用unitbuf操纵符。它告诉流在接下来的每次写操作之后都进行一次flush操作。而nounitbuf操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制：<br>
```cpp
cout<<unitbuf; //所有输出操作后都会立即刷新缓冲区 任何输出都立即刷新，无缓冲
cout<<nounitbuf; // 回到正常的缓冲方式
```
### 如果程序崩溃，输出缓冲区不会被刷新
如果程序异常终止，输出缓冲区是不会被刷新的。当一个程序崩溃后，它所输出的数据很可能停留在输出缓冲区中等待打印。<br>
当调试一个已经崩溃的程序时，需要确认那些你认为已经输出的数据确实已经刷新了。否则，可能将大量时间浪费在追踪代码为什么没有执行上，而实际上代码已经执行了，只是程序崩溃后缓冲区没有被刷新，输出数据被挂起没有打印而已。<br>
### 关联输入和输出流
当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。标准库将cout和cin关联在一起，因此下面语句<br>
```cpp
cin>>ival;
```
导致cout的缓冲区被刷新。<br>
@交互式系统通常应该关联输入流和输出流。这意味着所有输出，包括用户提示信息，都会在读操作之前被打印出来。<br>
tie有两个重载的版本：一个版本不带参数，返回指向输出流的指针。如果本对象当前关联到一个输出流，则返回的就是指向这个流的指针，如果对象未关联到流，则返回空指针。tie的第二个版本接受一个指向ostream的指针，将自己关联到此ostream。即，x.tie(&o) 将流x关联到输出流o<br>
我们既可以将一个istream对象关联到另一个ostream，也可以将一个ostream关联到一个另一个ostream:<br>
```cpp
cin.tie(&cout);  //仅仅是用来展示：标准库将cin和cout关联一起 old_tie指向当前关联到cin的流
ostream *old_tie = cin.tie(nullptr); //cin不再与其他流关联  将cin与cerr关联；这不是一个好主意，因为cin应该关联到cout
cin.tie(&cerr); // 读取cin 会刷新cerr而不是 cout
cin.tie(old_tie); //重建cin和cout间的正常关联
```
每个流同时最多关联到一个流，但多个流可以同时关联到同一个ostream<br>
### 文件的输入输出
头文件fstream定义了三个类型来支持文件IO: ifstream从一个给定文件读取数据，ofstream向一个给定文件写入数据，以及fstream可以读写给定文件。<br>
这些类型提供的操作与我们之前使用过的对象cin和cout的操作一样。特别是我们可以用IO运算符(<<和>>)来读写文件，可以用getline从一个ifstream读取数据。<br>
除了继承自iostream类型的行为之外，fstream中定义的类型还增加了一些新的成员来管理与流关联的文件。我们可以对fstream、ifstream和ofstream 对象调用这些操作，但不能对其他IO类型调用这些操作。<br>

fstream fstrm; 创建一个未绑定的文件流。fstream是头文件fstream中定义的一个类型。<br>
fstream fstrm(s); 创建一个fstream，并打开名为s的文件。s可以是string类型，或者是一个指向c风格字符串指针。这些构造函数都是explicit的。<br>
fstream fstrm(s,mode); 按指定的mode打开文件<br>
fstrm.open(s);<br>
fstrm.close();<br>
fstrm.is_open();<br>
### 使用文件流对象
```cpp
ifstream in(ifile); //构造一个ifstream并打开给定文件 ifile是一个string的输入流
ofstream out; // 输出文件流未关联到任何文件
```
**用fstream代替iostream&**<br>
在要求使用基类型对象的地方，我们可以用继承类型的对象来替代。这意味着，接受一个iostream类型引用（或指针）参数的函数，可以用一个对应的fstream（或sstream）类型来调用。也就是说，如果一个函数接受一个ostream&参数，我们在调用这个函数时，可以传递给它一个ofstream对象，对istream和ifstream也是如此。<br>
### 成员函数open和close
为了将文件流关联到另外一个文件，必须首先关闭已经关联的文件。<br>
```cpp
out.open(ifile+".copy");
if(out)//判断
in.close();
in.open(ifile+"2");
```
### 自动构造和析构
考虑到这样一个程序，它的main函数接受一个要处理的文件列表。这种程序可能会又如何的循环。<br>
//对每个传递给程序的文件执行循环操作<br>
```cpp
for(auto p = argv +1;p != argv+argc; ++p){
ifstream input(*p);
if(input){
    process(input);
}else{
cerr <<"couldn't open:"+string(*p);
}
```
@当一个fstream对象被销毁时，close会自动被调用<br>
```cpp
class readfile{
public:
string readf(const string &s){
ifstream in(s);
vector<string> vfile;
vector<string> vec;
string buf;
while(getline(in,buf)){
vfile.push_back(buf);
}
while(in>>buf){
vec.push_back(buf);
}
}
```
### 文件模式
﻿每一个流都有一个关联的文件模式(file mode)，用来指出如何使用文件。<br>
in,out,app,ate,trunc,binary<br>
@只可以对ofstream或fstream对象设定out模式<br>
@只可以对ifstream或fstream对象设定in模式<br>
@只有当out也被设定时才可设定trunc模式<br>
@只要trunc没被设定，就可以设定app模式。在app模式下，即使没有显式指定out模式，文件也总是以输出方式被打开。<br>
@ate和binary模式可用于任何类型的文件流对象，且可以与其他任何文件模式结合使用。<br>
每个文件流类型都定义了一个默认的文件模式，当我们未指定文件模式时，就使用此默认模式。与ifstream关联的文件默认以in模式打开；与ofstream关联的文件默认以out模式打开；与fstream关联的文件默认以in和out模式打开。<br>
以out模式打开文件会丢弃已有数据<br>
默认情况下，当我们打开一个ofstream时，文件的内容会被丢弃。阻止一个ofstream清空给定文件内同的方法是同时指定app模式：<br>

每次调用open时都会确定文件模式<br>
对于一个给定流，每当打开文件时，都可以改变其文件模式<br>
```cpp
 #include <fstream>
 	#include <iostream>
 	 
 	#include "exercise7_26.h"
 	 
 	using std::ifstream; using std::ofstream; using std::endl; using std::cerr;
 	 
 	int main(int argc, char **argv)
 	{
 	ifstream input(argv[1]);
 	ofstream output(argv[2]); //将输出文件名作为第二个参数传递给main函数
 	 
 	Sales_data total;
 	if (read(input, total))
 	{
 	Sales_data trans;
 	while (read(input, trans))
 	{
 	if (total.isbn() == trans.isbn())
 	total.combine(trans);
 	else
 	{
 	print(output, total) << endl;
 	total = trans;
 	}
 	}
 	print(output, total) << endl;
 	}
 	else
 	{
 	cerr << "No data?!" << endl;
 	}
 	 
 	return 0;
 	}
```
### string流
sstream头文件定义了三个类型来支持内存IO，这些类型可以向string写入数据，从string读取数据，就像string是一个IO流一样<br>
istringstream从string读取数据，ostringstream想string写入数据，头文件stringstream can do both<br>
```cpp
sstream strm
sstream strm(s)
strm.str()
strm.str(s)
istringstream record(line);//将记录绑定到刚读入的行
record >> info.name; //读取名字
record >> word; //读取line的后面的单词
ostringstream 
ostringstream a,b;  b<<""<<nums; //将nums存入b
```
## 顺序容器
元素在顺序容器中的顺序与其加入容器时的位置相对应。标准库还定义了几种关联容器，关联容器中元素的位置由元素的关键字值决定。<br>
所有容器类都共享公共的接口，不同容器按不同方式对其进行扩展。这个公共接口使容器的学习更加容易---我们基于某种容器所学习的内同也都适用于其他容器。每种容器都提供了不同的性能和功能的权衡。<br>
@一个容器就是一些特定类型对象的集合。<br>
顺序容器为程序员提供了控制元素存储和访问顺序的能力。这种顺序不依赖于元素的值，而是与元素加入容器时的位置相对应。<br>
@向容器添加或从容器中删除元素的代价<br>
@非顺序访问容器中元素的代价<br>
以下几种容器要记住，而且其中有大部分操作都是一样的，有一些不同，是根据容器的性质决定的。<br>
@vector 可变大小数组。支持快速随机访问。在尾部之外的位置插入或删除元素可能很慢。<br>
@deque 双端队列。支持快速随机访问。在头尾位置插入/删除速度很快。<br>
@list 双向链表。只支持双向顺序访问。在list中任何位置进行插入/删除操作速度都很快<br>
@forward_list 单向链表。只支持单向顺序访问。在链表任何位置进行插入/删除操作速度很快。<br>
@array 固定大小数组。 支持快速随机访问。不能添加或删除元素。<br>
@string 与vector相似的容器，但专门用于保存字符。随机访问快。在尾部插入/删除速度快<br>
除了固定大小的array外，其他容器都提供高效、灵活的内存管理。<br>
@forward_list 和array 是新C++ 标准增加的类型。<br>
forward_list的设计目标是达到与最好的手写的单向链表数据结构相当的性能。因此，forward_list没有size操作。因为保存或计算其大小就会比手写链表多出额外的开销。<br>
@通常，使用vector 是最好的选择，除非你有很好的理由选择其他容器<br>
### 容器概览
容器类型上的操作形成了一种层次：<br>
@某些操作是所有容器类型都提供的<br>
@另外一些操作仅针对顺序容器、关联容器、无序容器<br>
@还有一些操作只适用于一小部分容器<br>
每个容器都定义在一个头文件中，文件名与类型名相同。<br>
```cpp
list<Sales_date> //保存Sales_data对象的list
deque<double> //保存double的deque
```
### 对容器可以保存的元素类型的限制<br>
顺序容器几乎可以保存任意类型的元素。特别是，我们可以定义一个容器，其元素的类型是另一个容器。
```cpp
vector<vector<string>> lines;
```
顺序容器构造函数的一个版本接受容器大小参数，它使用了元素类型的默认构造函数。但某些类没有默认构造函数。我们可以定义一个保存这种类型对象的容器，但我们在构造这种容器的时候不能只传递给它一个元素数目参数：<br>
```cpp
vector<noDefault> v1(10,init); //假定noDefault 是一个没有默认构造函数的类型，这里提供了元素的初始化器，正确
```
### 容器操作
类型别名<br>
iterator  此容器类型的迭代器类型<br>
const_iterator 可以读取元素，但不能修改元素的迭代器类型<br>
size_type 无符号整数类型，足够保存此种容器类型最大可能容器的大小<br>
difference_type 带符号整数类型，足够保存两个迭代器之间的距离<br>
value_type 元素类型<br>
reference 元素的左值类型，与value_type & 含义相同<br>
const_reference 元素的const左值类型（即，const value_type&)<br>
构造函数<br>
```cpp
C c;
C c1(c2); //拷贝
C c(b,e); //构造c，将迭代器b和e指定的范围内的元素拷贝到c
C c(a,b,c,c,c,c...) //初始化
```
赋值与swap<br>
```cpp
c1=c2;
c1={a,b,c...};
a.swap(b);
swap(a,b);
```
大小
```cpp
c.size()
c.max_size();
c.empty();
```
添加/删除元素<br>
@在不同容器中，这些操作的接口都不同<br>
```cpp
c.insert(args);
c.emplace(inits);
c.erase(args);
c.clear()
```
关系运算符<br>
==，!=,
<,>,<=,>=
获取迭代器<br>
c.begin(), c,end(),
c.cbegin(),c.cend() //返回const_iterator
反容器的额外成员<br>
reverse_iterator  按逆序寻址元素的迭代器<br>
const_reverse_iterator 不能修改元素的逆序迭代器<br>
c.rbegin(),c.rend() 返回指向c的尾元素和首元素之前位置的迭代器<br>
c.crbegin(),c.crend() 返回const_reverse_iterator<br>
## 迭代器
forword_list 迭代器不支持递减运算符(--)<br>
### 迭代器范围
一个迭代器范围由一对迭代器表示，两个迭代器分别指向同一个容器中的元素或者是尾元素之后的位置。<br>
### [begin,end)
使用左闭合范围蕴涵的编程假定<br>
如果begin == end 则范围为空<br>
若不等，则范围至少包含一个元素，且begin指定该方位中的第一个元素<br>
我们可以对begin递增若干次，使得begin == end<br>
### 容器类型成员
```cpp
list<string>::iterator iter; //iter是通过list<string>定义的一个迭代器类型
vector<int>::diference_type count; //count是通过vector<int>定义的一个difference_type类型
```
### begin和end成员
实际上有两个名为begin的成员。一个是const成员，返回容器的const_iterator类型。另一个是非常量成员，返回容器的iterator类型。rbegin、end和rend的情况类似。当我们对一个非常量对象调用这些成员时，得到的是返回iterator的版本。只有在对一个const对象调用这些函数时，才会得到一个const版本。与指针和引用类似，可以将一个普通的iterator转换成对应的const_iterator，但反之不行。<br>
```cpp
list<string>::iterator it5 = a.begin()
list<string>::const_iterator it6 = a.begin()
auto it7 = a.begin();
auto it8 = a.cbegin();
```
@当不需要写访问时，应使用cbegin()和cend()<br>

### 容器定义和初始化
每个容器类型都定义了一个默认构造函数。除了array之外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素初始值的参数。<br>

### 容器定义和初始化
C c; 默认构造函数。如果C是一个array，则c中元素按默认方式初始化；否则c为空<br>
C c1(c2),
C c1=c2,
C c{a,b,c,d...},
C c(b,e),
C seq(n),
C seq(n,t),
将一个容器初始化为另一个容器的拷贝。<br>
将一个新容器创建为另一个容器的拷贝的方法有两种：可以直接拷贝整个容器，或者（array除外） 拷贝由一个迭代器指定的元素范围<br>
为了创建一个容器为另一个容器的拷贝，两个容器的类型及其元素类型必须匹配。不过，当传递迭代器参数来拷贝一个范围时，就不要求容器类型是相同的了。而且，新容器和原容器中的元素类型也可以不同，只要能将要拷贝的元素转换为要初始化的容器的元素类型即可。<br>
```cpp
list<string> authors = {"Milton","Shakespeare","Austen"};
vector<const char*> articles = {"a","an","the"};
list<string> list2(authors); //正确，类型匹配
deque<string> authList(authors) //错误，容器类型不匹配
vector<string> words(articles); //错误： 容器类型不匹配

forward_list<string> words(articles.begin(),articles.end()); //正确： 可以将const char*元素转换成string
```
@当将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同<br>
```cpp
deque<string> authList(authors.begin().begin(),it); //拷贝元素，直到（但不包括）it指向的元素
```
### 列表初始化
在新标准中，我们可以对一个容器进行列表初始化<br>
如果我们不提供元素初始值，则标准库会创建一个值初始化器<br>
```cpp
vector<int> ivec(10,-1); 
list<string> svec(10,"hi");
forward_list<int> ivec(10);
deque<string> svec(10);
```
@只有顺序容器的构造函数才接受大小参数，关联容器并不支持。<br>
标准库array具有固定大小<br>
与内置数组一样，标准库array的大小也是类型的一部分。当定义一个array时，除了指定元素类型，还要指定容器的大小<br>
```cpp
array<int,42>  //类型为： 保存42个int的数组
array<string,10> //类型为： 保存10个string的数组
为了使用array类型，我们必须同时指定元素类型和大小
array<int,10>::size_type i; //数组类型包括元素类型和大小
```
@由于大小是array类型的一部分，array不支持普通的容器构造函数。<br>
```cpp
array<int,10> ia1;
array<int, 10> ia2 = {0,1,2,3,4,5,6,7,8,9};
array<int,10> ia3 = {42};
```
值得注意的是，虽然我们不能对内置数组类型进行拷贝或对象赋值操作，但array并无此限制<br>
```cpp
int digs[10] = {1,2,3,4,5,6,7,8,9,0};
int cpy[10] = digs; //错误，内置数组不支持拷贝或赋值
array<int,10> digits = [1,2,3,4,5,6,7,8,9,0};
array<int,10> copy = digits; //正确： 只要数组类型匹配即合法
```
@大小是array类型的一部分<br>
如何从一个list<int> 初始化一个vector<double>?从一个vector<int>又该如何创建？<br>
```cpp
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <list>

using namespace std;

class vec{
private:
list<int> ilst(5,4);
vector<int> ivc(5,5);
//from list<int> vector<double>
public:
void flv(list<int> &lst,vector<double> &vect){
vect(lst.begin(),lst.end());
for(auto d : vect) cout<< i <<"\n"<<endl;
}
void vtv(vector<int> &vect,vector<double> &dvec){
dvec(vect.begin(),vect.end());
for(auto i:devc) cout<<i<<"\n"<<endl;
}
}
```

### 赋值和swap
赋值运算符将其左边容器中的全部元素替换为右边容器中元素的拷贝：<br>
```cpp
c1 = c2; //将c1的内容替换为c2中元素的拷贝
c1 = {a,b,c}; //赋值后，c1大小为3
```
第一赋值运算后，左边容器将与右边容器相等。如果两个容器原来大小不同，赋值运算后两者的大小都与右边容器的原大小相同。第二个赋值运算后，c1的size变为3，即花括号列表中值的数目。<br>
@与内置数组不同，标准库array类型允许赋值。<br>
array = {0}; //错误：不能将一个花括号列表赋予数组<br>
@容器赋值运算<br>
```cpp
c1 = c2;
c={a,b,c...};
swap(c1,c2) //交换c1 和 c2中的元素。c1 与c2 必须具有相同的类型。swap通常比从c2 向c1 拷贝元素快得多
c1.swap(c2)
```
**assign不适用于关联容器和array**<br>
seq.assign(b,e) 将seq中的元素替换为迭代器b和e所表示的范围中的元素。迭代器b和e不能指向seq中的元素<br>
seq.assign(il)   将seq中的元素替换为初始化列表il中的元素<br>
seq.assign(n,t) 将seq中的元素替换为n个值为t的元素<br>
使用assign 仅限顺序容器（除array）<br>
赋值运算符要求左边和右边的运算对象具有相同的类型。它将右边运算对象中所有元素拷贝到左边运算对象中。<br>
@顺序容器除array还定义了一个名为assign 的成员，允许我们从一个不同但相容的类型赋值，或者从容器的一个子序列赋值。
@assign操作用参数所指定的元素（的拷贝）替换左边容器中的所有元素。<br>
实例： 用assign 实现将一个vector中的一段char*值赋予一个list中的string:<br>
```cpp
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;//错误： 容器类型不匹配
names.assign(oldstyle.cbegin(),oldstyle.end()); // 正确：可以将const char *转换为string
```
assign的第二个版本接受一个整型值和一个元素值。<br>
```cpp
list<string> slist1(1);
slist1.assign(10,"hiya!"); //10个元素，每个都是“hiya”
```
### 使用swap
swap操作交换两个相同类型容器的内容。
```cpp
vector<string> svec1(10);
vector<string> scev2(24);
swap(svec1,svec2);
```
元素不会被移动的事实意味着，除string外，指向容器的迭代器、引用和指针在swap操作之后都不会失效。他们仍指向swap操作之前所指向的那些元素
@与其他容器不同，swap两个array会真正交换他们的元素。<br>
```cpp
list<const char *> lst(10,'h');
vector<string> vec;
vec.assign(lst.cbegin(),lst.end());
```
### 容器大小操作
size 返回容器中元素的数目<br>
empty 返回布尔值<br>
maz_size返回一个大于或等于该类型容器所能容纳的最大元素数的值<br>
forward_list 支持max_size 和empty，但不支持size<br>

### 关系运算符
关系运算符左右两边的运算对象必须是相同类型的容器，且必须保存相同类型的元素<br>
@容器的关系运算符使用元素的关系运算符完成比较<br>
@只有当其元素类型也定以了相应的比较运算符时，我们才可以使用关系运算符类比较两个容器<br>
如果元素类型不支持所需运算符，那么保存这种元素的容器就不能使用相应的关系运算。<br>
```cpp
vector<Sales_data> storeA,storeB;
if(storeA < storeB) //错误，Sales_data 没有<运算符
比较list与vector

list<int>      li{ 1, 2, 3, 4, 5 };
vector<int>    vec2{ 1, 2, 3, 4, 5 };
vector<int>    vec3{ 1, 2, 3, 4 };

cout << (vector<int>(li.begin(), li.end()) == vec2 ? "true" : "false") << endl;
cout << (vector<int>(li.begin(), li.end()) == vec3 ? "true" : "false") << endl;
```
### 顺序容器操作
1.向顺序容器添加元素<br>

除了array外，所有标准库容器都提供灵活的内存管理。在运行时可以动态添加或删除元素来改变容器大小。<br>
array不支持这些操作<br>
forward_list 有自己专有版本的insert和emplace，不支持push_back和emplace_back<br>
vector 和 string不支持push_front和emplace_front<br>
c.push_back(a);<br>
c.emplace_back(a);<br>
c.push_front(a);<br>
c.emplace...<br>
c.insert(p,a) 迭代器p指向的元素之前创建一个值为t的元素。返回指向新添加的元素的迭代器<br>
c.emplace(p,a)<br>
c.insert(p,n,a) 在迭代器p指向的元素之前插入n个值为a的元素。返回指向新添加的第一个元素的迭代器。若n为0，返回p<br>
c.insert(p,b,e) 在迭代器b和e指定的范围内的元素插入到迭代器p指向的元素之前。b和e不能指向c中的元素。返回指向新添加的第一个元素的迭代器。<br>
若范围为空，则返回p<br>
c.insert(p,il) il是一个花括号包围的元素值列表。将这些给定值插入到迭代器p指向的元素之前。返回指向新添加的第一个元素的迭代器；<br>
若列表为空，返回p<br>
@向一个vector，string或deque 插入元素会使所有指向容器的迭代器、引用和指针失效。<br>
### 删除元素
顺序容器的删除操作<br>
这些操作会改变容器的大小，所以不使用与array<br>
forward_list 有特殊版本的erase<br>
forward_list 不支持pop_back；vector和string不支持pop_front<br>
c.pop_back(); c.pop_front(); c.erase(p)//删除迭代器p所指定的元素，返回一个指向被删元素之后元素的迭代器，若p指向尾元素，则返回为后off-the-end迭代器。若p是尾后迭代器。若p是尾后迭代器，则函数行为未定义<br>

c.erase(b,e) //返回一个指向最后一个被删元素之后元素的迭代器，若e本身就是尾后迭代器，则函数也返回尾后迭代器。<br>
c.clear() //删除c中的所有元素，返回void<br>
### 特殊的forward_list
lst.before_begin() //返回指向链表首元素之前不存在的元素的迭代器，此迭代器不能解引用。cbefore_begin()返回一个const_iterator<br>
lst.cbefore_begin()<br>
lst.insert_after(p,t) //在迭代器p之后的位置插入元素。<br>
lst.insert_after(p,n,t) //t是一个对象，n是数量<br>
lst.insert_after(p,b,e) //b和e代表范围的一对迭代器。<br>
lst.insert_after(p,il) //il是花括号列表。返回一个指向最后一个插入元素的迭代器。如果范围为空，则返回p。若p为尾后迭代器，则函数行为未定义<br>

emplace_after(p,args) 使用args指定位置之后创建一个元素。返回一个指向这个新元素的迭代器。若p为尾后迭代器，则函数行为未定义<br>
lst.erase_after(p)<br>
lst.erase_after(p,e) //删除p指向的位置之后的元素，或删除从b之后知道（但不包含） e之间的元素。返回一个指向被删元素之后元素的迭代器，若不存在这样的元素，则返回尾后迭代器。如果p指向lst的尾元素或者是一个尾后迭代器，则函数未定义。<br>

### 改变容器大小。
resize()<br>
容器操作可能使迭代器失效<br>
向容器中添加元素和从容器中删除元素的操作可能会使指向容器的元素的指针、引用或迭代器失效。一个失效的指针、引用或迭代器将不再表示任何元素。使用失效的指针、引用或迭代器是一种严重的程序设计错误，很可能引起与使用未初始化指针一样的问题<br>
@如果在一个循环中插入/删除deque、string或vector 中的元素，不要缓存end返回的迭代器<br>
必须在每次插入操作后重新调用end()， 而不能在循环开始前保存它返回的迭代器<br>
```cpp
forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
auto pre = flst.before_begin();
auto curr = flst.begin();
while(curr != flst.end()){
if(*curr % 2){
curr = flst.insert_after(pre,*curr);
++curr;
++pre;
}else{
flst.erase_after(pre);
++curr;
++pre;
}
}
```
在第316页的程序中，向下面语句这样调用insert是否合法？如果不合法，为什么？
iter = vi.insert(iter, *iter++);<br>
不合法。因为参数的求值顺序是未指定的。<br>

vector对象是如何增长的<br>

为了支持快速随机访问，vector将元素连续存储----每个元素紧挨着前一个元素存储<br>

### 管理容量的成员函数

capacity 操作告诉我们容器在不扩张内存空间的情况下可以容纳多少个元素。reserve 操作允许我们通知容器它应该准备保存多少元素<br>

shrink_to_fit 只适用于vector 和 string<br>

c.shrink_to_fit()  请将capacity() 减少为与size() 相同大小<br>

c.capacity() 不能重新分配内存空间的话，c可以保存多少元素<br>

c.reserve(n) 分配至少能容纳n个元素的内存空间<br>

reserve并不改变容器中元素的数量，它仅影响vector预先分配多大的内存空间<br>

resize只改变容器中元素的数目，而不是容器的容量。我们同样不能使用resize来减少容器预留的空间<br>

size指它已经保存的元素的数目。<br>

capacity则是在不分配新的内存空间的前提下他最多可以保存多少元素<br>

### 额外string操作
1.构造string的其他方法<br>
string s(cp,n)  s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符<br>
string s(s1,pos2) s是string s2 从下标pos2开始的字符的拷贝。若pos2>s1.size(),构造函数的行为未定义<br>
string s(s2,pos2,len2) s是string s2从下标pos2开始len2个字符的拷贝。若pos2 > s2.size(), 构造函数的行为未定义。不管len2的值是多少，构造函数至少拷贝s2.size() - pos2个字符<br>
```cpp
const char *cp = "hello,world!!!";
char noNull[] = {'H','i'};
string s1(cp); //直到遇到空字符
string s2(noNull,2);
```
### substr操作
s.substr(pos,n) 返回一个string，包含s中从pos开始的n个字符的拷贝。pos的默认值为0。n的默认值为s.size()-pos，即拷贝从pos开始的所有字符<br>
#### 改变string的其他方法
string类型支持顺序容器的赋值运算符以及assign、insert和erase操作。<br>
@定义额外的insert和erase版本<br>
#### 修改string操作
s.insert(pos,args) 在pos之前插入args指定的字符。pos可以是一个下标或一个迭代器。接受下标的版本返回一个指向s的引用；接受迭代器的版本返回指向第一个插入字符的迭代器<br>
s.erase(pos,len) 删除从位置pos开始的len个字符。如果len被省略，则删除从pos开始直至s末尾的所有字符，返回一个指向s的引用。<br>
s.assign(args) 将s中的字符替换为args指定字符。返回一个指向s的引用<br>
s.append(args) 将args追加到s。返回一个指向s的引用<br>
s.replace(range,args) 删除s中范围range内的字符，替换为args指定的字符。range或者是一个下标和一个长度，或者是一对指向s的迭代器。返回一个指向s的引用。<br>
#### string搜索操作
string类提供了6个不同的搜索函数，每个函数都有四个重载版本。<br>
find函数完成最简单的搜索。它查找参数指定的字符串，若找到，则返回第一个匹配位置的下标，否则返回npos<br>
标准库将npos定义为一个const string::size_type类型，并初始化值为-1.<br>
```cpp
string numbers("01234567"),name("r2d2");
auto pos = name.find_first_of(numbers);
```
如果要是搜索第一个不在参数中的字符，我们应该调用find_first_not_of。<br>
s.find(args)<br>
s.rfind(args) args中最后一次出现的位置<br>
s.find_first_of(args) 在s中查找args中任何一个字符第一次出现的位置<br>
s.find_last_of(args)最后一次出现的位置<br>
s.find_first_not_of(args) 第一个不在args中的字符<br>
s.find_last_not_of(args) 在s中查找最后一个不在args中的字符<br>
compare函数<br>
类似strcmp<br>
数值转换<br>
字符串中常常包含表示数值的字符<br>
新标准引入了多个函数，可以实现数值数据与标准库string之间的转换：<br>
```cpp
int i = 42;
string s = to_string(i); //将整数i转换为字符表示形式
double d = stod(s);  //将字符串s转换为浮点数

string s2 = “pi = 3.14";
d = stod(s2.substr(s2.find_first_of("+-.0123456789")));
//结果d = 3.14
#include <iostream>
 	#include <vector>
 	#include <string>
 	 
 	using namespace std;
 	 
 	int sum_of_int(const vector<string>& v)
 	{
 	int sum = 0;
 	for (auto i : v)
 	{
 	sum += stoi(i);
 	}
 	return sum;
 	}
 	 
 	float sum_of_float(const vector<string>& v)
 	{
 	float sum = 0;
 	for (auto i : v)
 	{
 	sum += stof(i);
 	}
 	return sum;
 	}
 	 
 	int main()
 	{
 	vector<string> v = { "1", "2", "3", "4.5" };
 	cout << sum_of_int(v) << endl;
 	cout << sum_of_float(v) << endl;
 	return 0;
 	}

#include <iostream>
 	#include <string>
 	#include <vector>
 	 
 	using namespace std;
 	 
 	class date
 	{
 	private:
 	unsigned year, month, day;
 	 
 	public:
 	date(const string& s)
 	{
 	if (s.find_first_of("/") != string::npos)
 	convert1(s);
 	else if (s.find_first_of(",") != string::npos)
 	convert2(s);
 	else if (s.find_first_of(" ") != string::npos)
 	convert3(s);
 	else
 	year = 1900, month = 1, day = 1;
 	}
 	 
 	void print()
 	{
 	cout << "day:" << day << " " << "month: " << month << " " << "year: " << year << endl;
 	}
 	 
 	private:
 	void convert1(const string& s)
 	{
 	day = stoi(s.substr(0, s.find_first_of("/")));
 	month = stoi(s.substr(s.find_first_of("/") + 1, s.find_last_of("/") - s.find_first_of("/")));
 	year = stoi(s.substr(s.find_last_of("/") + 1, 4));
 	}
 	void convert2(const string& s)
 	{
 	convert_month(s);
 	day = stoi(s.substr(s.find_first_of("123456789"), s.find_first_of(",") - s.find_first_of("123456789")));
 	year = stoi(s.substr(s.find_last_of(',') + 1, 4));
 	}
 	void convert3(const string& s)
 	{
 	convert_month(s);
 	day = stoi(s.substr(s.find_first_of("123456789"), s.find_first_of(" ") - s.find_first_of("123456789")));
 	year = stoi(s.substr(s.find_last_of(' ') + 1, 4));
 	}
 	 
 	void convert_month(const string& s)
 	{
 	if (s.find("Jan") < s.size()) month = 1;
 	if (s.find("Feb") < s.size()) month = 2;
 	if (s.find("Mar") < s.size()) month = 3;
 	if (s.find("Apr") < s.size()) month = 4;
 	if (s.find("May") < s.size()) month = 5;
 	if (s.find("Jun") < s.size()) month = 6;
 	if (s.find("Jul") < s.size()) month = 7;
 	if (s.find("Aug") < s.size()) month = 8;
 	if (s.find("Sep") < s.size()) month = 9;
 	if (s.find("Oct") < s.size()) month = 10;
 	if (s.find("Nov") < s.size()) month = 11;
 	if (s.find("Dec") < s.size()) month = 12;
 	}
 	};
 	 
 	int main()
 	{
 	date d1("9/5/1990");
 	date d2("January 7,1970");
 	date d3("Jan 11 1942");
 	 
 	d1.print();
 	d2.print();
 	d3.print();
 	 
 	return 0;
 	}
```


## 容器适配器
标准库定义了三个顺粗容器适配器: stack,deque 和priority_queue<br>
适配器是一个通用概念。容器、迭代器和函数都有适配器<br>
本质上，一个适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。<br>
一个容器适配器接受一种已有的容器类型，使其行为看起来像一种不同的类型。<br>
### 栈适配器
stack<int> intStack<br>
#### LIFO
s.pop()  删除栈顶元素，但不返回该元素的值  <br>
s.push(item)<br>
s.emplace(args)<br>
s.top() 返回栈顶元素<br>
### 队列适配器
#### FIFO
queue<int> q   FIFO<br>
q.pop() 返回首元素，但不删除元素<br>
q.front() //返回首元素或尾元素，但不删除<br>
q.back() //只适用于queue<br>
q.top() // 返回最高优先级元素，但不删除该元素<br>
q.push(item) <br>
q.emplace(args);<br>
至此，顺序容器与io库已经摘录完毕，请期待下一章节关联容器<br>

