# Cpp 范型算法，关联容器以及动态内存
**上集讲到，顺序容器，io库，标准库容器是模板类型，用来保存给定类型的对象，**在一个顺序同期中，元素都是按顺序存放的，通过位置来访问。<br>
顺序容器有公共的标准接口：如果两个顺序容器都是提供一个特定的操作，那么这个操作在两个容器中具有相同的接口和含义。所有容器除了array，都提供高效的动态内存管理。<br>
这集，我们来讲泛型算法，关联容器，动态内存，概念及运用！<nr>
标准库容器定义的操作集合惊人的小！标准库并未给每个容器添加大量的功能，而是提供了一组算法，这些算法中大多数独立于任何特定的容器。这些算法是通用的或者说是泛型，它们可用于不同类型的容器和不同类型的元素<br>
泛型算法和关于迭代器的更多细节，将在本章拉开帷幕！<br>
### 泛型算法：
算法，因为实现了一些经典算法的公共接口，如排序和搜索；<br>
泛型，因为可以用于不同类型的元素和多种容器类型（不包括标准库类型，如vector或list，还包括内置数组类型），以及我们将看到的，还嫩惯用语其他类型的序列。<br>
大多数算法都定义在头文件algorithm中。**标准库还在头文件numeric中定义了一组数值泛型算法**<br>
一般情况下，这些算法并不直接操作容器，而是遍历由两个迭代器指定的一个元素范围来进行操作。<br>

### 标准库算法 find
```cpp
auto result = find(vec.cbegin(),vec.cend(),val);
```
如果vec中找到想要的元素，则返回结果指向它，否则返回结果为vec.cend()<br>
find 在数组查找值<br>
```cpp
int ia[] = {...};
val = 42;
int *result = find(begin(ia),end(ia),val);
```
可以在子范围查找<br>
```cpp
auto result = find(ia+1,ia+4,val);
```
迭代器令算法不依赖与容器，但散发依赖于元素类型的操作<br>
count
```cpp
vector<int> vec;
int vin,val = 12;
while(cin>> vin){
    vec.push_back(vin);
 }
auto countdown = count(vec.cbegin(),vec.cend(),val);
```
@泛型算法本身不会执行容器操作，它们只会运行于迭代器之上，执行迭代器的操作。<br>
@算法永远不会改变底层元素的大小<br>
## 初识泛型算法
### 1.只读算法
一些算法只会读取其输入范围内的元素，而从不改变元素。例如find和count<br>
另一个只读算法是accumulate，定义在头文件numeric中。accumulate函数接受三个参数，前两个指出了需要求和的元素的范围，第三个参数是和的初值。<br>
```cpp
int sum = accumulate(vec.cbegin(),vec.cend(),0);
```
### 算法和元素类型
上述accumulate，序列中的元素的类型必须与第三个参数匹配，或者能够转换为第三个参数的类型<br>
```cpp
string sum = accumulate(v.cbegin(),v.cend(),string(""));
```
### equal 操作两个序列的算法
```cpp
equal(roster1.cbegin,roster1.cend(),roster2.cbegin());
```
只要能用 == 来比较两个元素的类型即可。<br>
只接受，第二个序列至少与第一个序列一样长，此算法要处理第一个序列中的每个元素，它假定每个元素在第二个序列中都有一个与之对应的元素<br>
### 写容器算法
一些算法将新值赋予序列中的元素。当我们使用之类算法时，必须注意确保序列的原大小至少不少于我们要求算法写入的元素数目。<br>
### fill
```cpp
fill(vec.cbegin(),vec.cend(),0); //将每个元素重置为0
```
@用一个单一迭代器表示第二个序列的算法都假定第二个序列至少与第一个一样长。<br>
**算法不检查写操作**<br>
一些算法接受一个迭代器来指出一个单独的目的位置。这些算法将新值赋予一个序列中的元素，该序列从目的位置迭代器指向的元素开始。<br>
```cpp
fill_n(vec.begin(),vec.size(),0) // 将所有元素重置为0
```
不能在空容器进行写操作
```cpp
fill_n(vec.begin(),20,0) //错误操作
```
### 介绍back_inserter
一种保证算法有足够元素空间来容纳输出数据的方法是使用插入迭代器。<br>
### 定义在头文件 iterator
接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。当我们通过此迭代器赋值时，赋值运算符会调用push_back 将一个具有给定值的元素添加到容器中：
```cpp
vector<int> vec;
auto it = back_inserter(vec); //通过它赋值会将元素添加到vec中
*it = 42; //vec中现在有一个元素，值为42
```
常常使用back_inserter 来创建一个迭代器，作为算法的目的位置来使用。
```cpp
vector<int> vec;
fill_n(back_inserter(vec),10,0); //插入10个0
```
### 拷贝算法
拷贝算法是另一个向目的位置迭代器指向的输出序列中元素的写入数据的算法。<br>
```cpp
int a1 [] = {1,2,23,3,4,4,44,4,4,4};
int a2 [ sizeof (a1)/sizeof(*a1) ];
```
ret指向拷贝到a2 的尾元素之后的位置
```cpp
auto ret = copy (begin(a1),end(a1),a2);
```
把a1的内容拷贝给a2<br>
replace算法读入一个序列，并将其中所有等于给定值的元素都改为另一个值<br>
replace(ilst.begin(),ilst.end(),0,42); 将所有值为0的元素改为42<br>
```cpp
replace_copy(ilst.cbegin(),ilst.cend(),back_inserter(ivec),0,42) //使用back_inserter 按需要增长目标序列
```
ilst并未改变，ivec 包含ilst的一份拷贝，不过原来在ilst中值为0的元素在ivec中都变为42<br>
### 重排容器元素的算法
sort 调用sort会重排输入序列中的元素，使之有序，它是利用元素类型的<运算符类实现排序。<br>
消除重复单词unique 使得不重复的元素出现在vector的开始部分，然后用erase成员删除<br>
```cpp
sort(vec.begin(),vec.end());
auto end_unique = unique(vec.begin(),vec.end()); 
//unique重排输入范围，使得每个单词只出现一次，排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
vec.erase(end_unique,words.end()); 
```
### 定制操作
很多算法都会比较输入序列中的元素。<br>
向算法传递函数<br>
### 谓词
谓词是一个可调用的表达式，其返回结果是一个能用作条件的值。标注库算法所使用的谓词分为两类：<br>
1.一元谓词（意味着他们只接受单一参数）<br>
2.二元谓词（意味着他们有两个参数） 接受谓词参数的算法对输入序列中的元素调用谓词。因此元素类型必须能转换为谓词的参数类型。<br>
接受一个二元谓词参数的sort版本用这个谓词代替<来比较元素。<br>
举个🌰 :
```cpp
bool isShorter(const string &s1,const string &s2){
return s1.size() < s2.size();
} //返回的结果是一个能用作条件的值
sort(words.begin(),words.end(),isShorter);
```
### 排序算法
stable_sort 按长度重新排序，长度相同的单词维持字典序<br>
### lambda表达式
❓求大于等于一个给定长度的单词有多少<br>
elimDups(vector) 将vector 按字典序排序，删除重复单词<br>
### 介绍lambda
我们可以向一个算法传递任何类别的可调用对象。对于一个对象或一个表达式，如果可以对其使用调用运算符，则称它为可调用的。<br>
一个lambda表达式表示一个可调用的代码单元。<br>
理解为一个未命名的内联函数。<br>
一个lambda表达式具有一个返回类型、一个参数列表和一个函数体。<br>
```cpp
[capture list](parameter list) -> return type {function body}
```
lambda必须使用尾置返回来指定返回类型。<br>
@可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体。<br>
```cpp
auto f = []{return 42;}; //定义一个可调用对象f，不接受参数，返回42
```
**调用 f()**<br>
在lambda中忽略括号和参数列表等价于指定一个空参数列表。在此例中，当调用f时，参数列表是空的。如果忽略返回类型，lambda根据函数体中的代码推断出返回类型。如果函数体知识一个return语句，则返回类型从返回的表达式的类型推断而来。否则返回void<br>

### 向lambda传递参数
与一个普通函数调用类似，调用一个lambda时，给定的实参被用来初始化lambda形参。<br>
lambda不能有默认的参数。<br>
@一个lambda调用的实参数目永远与形参数目相等。一旦形参初始化完毕，就可以执行函数体了。<br>
与isshorter函数完全相同的lambda<br>
```cpp
//@1
[](const string &a,const string &b){ return a.size() < b.size();}<br>
```
使用@1
```cpp
stable_sort(words.begin(),words.end(),@1);  //当stable_sort 需要比较两个元素时，他就会调用给定的这个lambda表达式。
```
使用捕获列表<br>
编写一个可以传递给find_if的可调用表达式。希望这个表达式能将输入序列中的每个string的长度与biggies函数中的sz参数的值作比较<br>
捕获列表指引lambda在其内部包含访问局部变量所需的信息<br>
```cpp
[sz] (const string &a){return a.size() >= sz;}; 
//lambda会捕获sz，并只有单一的string参数。其函数体会将string的大小与捕获的sz的值进行比较
```
@一个lambda只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在函数体中使用该变量<br>
### 调用find_if
```cpp
auto wc = find_if(words.begin(),words.end(),[sz](const string &a){ return a.size() >= sz;});
//这里对find_if调用返回一个迭代器，指向第一个长度不小于给定参数sz的元素。
```
### for_each算法
接受一个可调用对象，并对输入序列中每个元素调用此对象<br>
```cpp
for_each(wc,words.end(), [](const string &s){cout <<s <<"";});
```
捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和在它所在函数之外声明的名字<br>
```cpp
void biggies(std::vector<std::string> &vs, std::size_t sz)
 	
{
 	 
 	elimdups(vs);
 	 
 	std::stable_sort(vs.begin(), vs.end(),
 	[](string const& lhs, string const& rhs) {
 	return lhs.size() < rhs.size(); }
 	);
 	 
 	auto wc = std::find_if(vs.begin(), vs.end(),
 	[sz](string const& s) { return s.size() >= sz; }
 	);
 	 
 	std::for_each(wc, vs.end(),
 	[](const string &s) {
 	std::cout << s << " "; }
 	);
 	}

```
### lambda捕获和返回
当定义一个lambda时，编译器生成一个与lambda对应的新的（未命名的）类类型。目前可以这样理解，当向一个函数传递一个lambda时，同时定义了一个新类型的一个对象：传递的参数就是此编译器生成的类类型的未命名对象。类似的，当使用auto定义一个用lambda初始化的变量时，定义了一个从lambda生成的类型的对象。<br>

@默认情况下，从lambda生成的类都包含一个对应该lambda所捕获的变量的数据成员。类似任何普通类的数据成员，lambda的数据成员也在lambda对象创建时，被初始化。<br>

### 值捕获
类似参数传递，变量的捕获方式也可以是值或引用。<br>
采用值捕获方式，与传值参数类似，采用值捕获的前提是变量可以拷贝。@与参数不同，被捕获的变量的值是在lambda创建时拷贝，而不是调用时拷贝。<br>
```cpp
void fcn1(){
    size_t v1 = 42;
    auto f = [v1] {return v1;}; //将v1拷贝到名为f的可调用对象
    v1 = 0;
    auto j = f(); //j为42；f保存了我们创建它时v1的拷贝
}
```
### 引用捕获
我们定义lambda时，可以采用引用方式捕获变量。
```cpp
void fcn1(){
    size_t v1 = 42;
    auto f = [&v1] {return v1;}; //对象f包含v1的引用
    v1 = 0;
    auto j = f(); //j为0；f2保存了v1的引用，而非拷贝    在lambda返回v1时，它返回的是v1指向的对象的值
}
```
v1之前的&指出v1应该用引用方式捕获。一个以引用方式捕获的变量与其他任何类型的引用的行为类似。当我们在lambda函数体内使用此变量时，实际上使用的是引用所绑定的对象。<br>

引用捕获与返回引用有着相同的问题和限制。如果我们采用引用方式捕获一个变量，就必须确保引用的对象在lambda执行的时候是存在的。<br>
@lambda捕获的都是局部变量，这些变量在函数结束之后就不复存在了。如果lambda可能在函数结束后执行，捕获的引用指向的局部变量已经消失。<br>

例如 希望bigges函数接受一个ostream的引用用来输出数据，并接受一个字符作为分隔符<br>
```cpp
void bigges(vector<string> &words, vector<string> ::size_type sz, ostream &os = cout, char c = ' ' ){
    for_each(words.begin(),words.end(), [&os, c](const string &s){ os<<s<<c;});
}
```
我们不能拷贝ostream对象，因此捕获os的唯一方法就是捕获其引用（或指向os的指针）<br>
@当以引用方式捕获一个变量时，必须保证在lambda执行时变量是存在的。<br>

### 隐式捕获
除了显示列出我们希望使用的来自所在函数的变量外，还可以让编译器根据lambda体中的代码来推断我们要使用那些变量。为了指示编译器推断捕获列表，应在捕获列表中写一个&或=。&告诉编译器采用捕获引用方式，=表示采用值捕获方式。<br>
```cpp
wc = find_if(words.begin(),words.end(), [=] (const string &s){ return s.size() >= sz;});
```
如果我们希望对一部分变量采用值捕获，对其他变量采用引用捕获，可以混合使用隐式捕获和显式捕获
```cpp
void bigges(vector <string> &words, vector<string>::size_type sz, ostream &os = cout, char c=' '){
    for_each(words.begin(), words.end(), [&,c] (const string &s){os<<s<<c;}); //os隐式捕获，引用捕获方式； c显式捕获，值捕获方式
    for_each(words.begin(),words.end(),[=,&os] (const string &s){os<<s<<c;}); //os显式捕获，引用捕获方式；c隐式捕获，值捕获方式
}
```
@当我们混合使用隐式捕获和显示捕获时，捕获列表中的第一个元素必须是一个&或=。<br>
@当混合使用隐式捕获和显式捕获时，显式捕获的变量必须使用与隐式捕获不同的方式。<br>

### 可变lambda
默认情况下，对于一个被拷贝的变量，lambda不会改变其值。如果我们希望能改变一个捕获的变量的值，就必须在参数列表首加上关键字mutable。因此，可变lambda能省略参数列表<br>
```cpp
void fcn3(){
    size_t v1=42;
    auto f = [v1] () mutable {return ++v1;};
    v1 = 0;
    auto j = f(); //j ==43
}
```
@一个引用捕获的变量是否（如往常一样） 可以修改依赖于此引用指向的是一个const类型还是一个非const类型
```cpp
void fcn4(){
    size_t v1=42;
    auto f2 = [&v1] {return ++v1;};
    v1 = 0;
    auto j = f2(); //j == 1
}
```
### 指定lambda返回类型
使用标准库的transform算法和一个lambda来将一个序列中的每个负数替换为其绝对值<br>
```cpp
transform(vi.begin(),vi.end(),vi.begin(), [] (int i) {return i<0 ? -i:i;});
```
前两个表示输入序列，第三个迭代器表示目的位置。<br>
@当我们需要为一个lambda定义返回类型时，必须使用尾置返回类型<br>
```cpp
transform( vi.begin(), vi.end(),vi.begin(), [](int i)->{if(i<0) return -i; else return i;});

count_if(vi.begin(),vi.end(),[](const string &s){return s.size()>6;});
```
使用
```cpp
return  count_if(vi.begin(),vi.end(),[](const string &s){return s.size()>6;});
[&i]()->bool{return i==0?true:!(i--);}
```
### 参数绑定

标准库bind函数（头文件functional）<br>
可以将bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用的对象来“适应” 原对象的参数列表。<br>
```cpp
auto newCallable = bind(callable,arg_list);
```
其中newCallable本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应给定的callable的参数。即，当我们调用newCallable时，newCallable会调用callable，并传递给它arg_list 中的参数<br>
arg_list中的参数可能包含形如_n的名字，其中n是一个整数。 这些参数是“占位符”，表示newCallable的参数，它们占据了传递给newCallable的参数的位置。数值n表示生成的可调用对象中参数的位置<br>
**_1 为newCallable的第一个参数， _2为第二个参数...<br>**
绑定check_size的sz参数<br>
举个简单的例子，我们将使用bind生成一个调用check_size 的对象。用一个定值作为其大小参数来调用check_size<br>
```cpp
auto check6 = bind(check_size,_1,6);
//check6 是一个可调用对象，接受一个string类型的参数，并用此string和值6来调用check_size
```
此调用，只有一个占位符，表示check6只接受单一参数。<br>
使用
```cpp
string s = "hello,world";
bool b1 = check6(s); //调用check_size(s,6)

auto wc = find_if(w.begin(),w.end(), [sz](const string &s)); ==> find_if(w.begin(),w.end(),bind(check_size,_1,sz));
```
此调用生成一个可调用对象，将check_size的第二个参数绑定到sz的值。当find_if对words中的string调用这个对象时，这些对象会调用check_size，将给定的string和sz传递给它。因此，find_if可以有效地对输入序列中每个string调用chek_size，实现string的大小与sz的比较。<br>

### 使用placeholders名字
@名字_n都定义在一个名为placeholders的命名空间中，而这个命名空间本身定义在std命名空间中。<br>
```cpp
using std::placeholder::_1

using namespace std::placeholders;
```
### bind的参数

可以用bind修正参数的值。可以用bind绑定给定可调用对象中的参数或重新安排其顺序。<br>
```cpp
//g是一个有两个参数的可调用对象
auto g = bind(f,a,b,_2,c,_1)
```
生成一个新的可调用对象，它有两个参数，分别用占位符_2,_1表示。<br>
这个新的可调用对象将它自己的参数作为第三个和第五个参数传递给f。f的第一个、第二个和第四个参数分别被绑定到给定的值a,b和c上。<br>

@传递给g的参数按位置绑定到占位符。bind调用会将g(_1,_2) 映射到f(a,b,_2,c,_1)<br>
### 用bind重排参数顺序

以下是用bind重排参数顺序的一个具体例子，我们可以用bind颠倒isShorter的含义：<br>
```cpp
sort(words.begin(),words.end(), isShorter); //按单词由短到长
sort(words.begin(),words.end(),bind(isShorter,_2,_1); //单词由长到短
```
### 绑定引用参数
默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。<br>
但是与lambda类似，有时对有些绑定的参数我们希望以引用方式传递，或是要绑定参数的类型无法拷贝。<br>
@为了替换一个引用方式捕获ostream的lambda<br>
```cpp
for_each(words.begin(),words.end(),[&os,c](const string &s){ os<<s<<c;}); //os 是一个局部变量，引用一个输出流
// c是一个局部变量，类型为char
```
可以很容易地编写一个函数完成相同的工作<br>
```cpp
ostream &print(ostream &os, const string &s, char c){ return os<<s<<c;};
```
我们不能拷贝一个ostream，如果我们希望传递给bind一个对象而不拷贝它，就必须使用标准库ref函数。<br>
```cpp
for_each(words.begin(),words.end(),bing(print,ref(os),_1,' ' ));
```
函数ref返回一个对象，包含给定的引用，此对象是可以拷贝的。标准库中还有一个cref函数，生成一个保存const引用的类。与bind一样，函数ref和cref也定以在头文件functional中<br>
bind接受几个参数？  假设被绑定的函数接受n个参数，那么bind接受n+1个参数<br>
```cpp
bool check_size(const string &s, size_t i){ return i>s.size();}
vector<int> vec = {1,2,3,4,5,6,7}
string s("1221212");
find_if(vec.begin(),vec.end(),bind(check_size,s,_1);
```
### 再探迭代器
插入迭代器：这些迭代器被绑定到一个容器上，可用来向容器插入元素<br>
流迭代器 ：这些迭代器被绑定到输入或输出流上，可用来遍历所关联的IO流<br>
反向迭代器： 这些迭代器向后而不是向前移动。除了forward_list之外的标准库容器都有反向迭代器<br>
移动迭代器：这些专用的迭代器不是拷贝其中的元素，而是移动它们。<br>
### 插入
back_inserter 插后面 copy(lst.cbegin(),lst.cend(),inserter(lst3,lst3.begin()));<br>
front_inserter 插前面 copy(lst.cbegin(),lst.cend(), front_inserter(lst2));<br>
inserter<br>
inserter(c,iter)被调用时，得到一个迭代器，接下类使用它时，会将元素插入到iter原来所指向的元素之前的位置。<br>
### iostream 迭代器
虽然iostream类型不是容器，但标准库定义了可以用与这些IO类型对象的迭代器。 istream_iterator读取输入流，<br>
ostream_iterator是向一个输出流写数据。<br>
ostream_iterator读取输入流，<br>
istream_iterator操作<br>

当创建一个流迭代器时，必须指定迭代器将要读写的对象类型。一个istream_iterator使用>>来读取流<br>
因此，istream_iterator要读取的类型必须定义了输入运算符。当创建一个istream_iterator时，我们可以将它绑定到一个流。<br>
当然我们还可以默认初始化迭代器，这样就创建了一个可以当作尾后值使用的迭代器。<br>
```cpp
istream_iterator<int> int_it(cin); //从cin读取int
istream_iterator<int> int_eof; //尾后迭代器
ifstream in("a.txt");
istream_iterator<string> str_it(in); //从 “a.txt" 读取字符串
```
下面是一个用istream_iterator 从标准输入读取数据，存入一个vector的例子<br>
```cpp
istream_iterator<int> in_iter(cin); //从cin读取int
istream_iterator<int> eof; //istream 尾后迭代器
while(in_iter != eof)vec.push_back(*in_iter++); 
 //后置递增运算符读取流，返回迭代器的旧值 解引用迭代器，获得从流读取的前一个值
 ```
将程序重写为如下形式
```cpp
istream_iterator<int> in_iter(cin),eof; 
vector<int> vec(in_iter,eof); 
//从迭代器范围构造vec
```
### 使用算法操作流迭代器
由于算法使用迭代器操作来处理数据，而流迭代器又至少支持某些迭代器操作，因此我们至少可以用某些算法来操作流迭代器。<br>
```cpp
istream_iterator <int> in(cin),eof;
cout<< accumulate(in,eof,0) <<endl;
```
此调用会计算出从标准输入读取的值的和<br>

istream_iterator允许使用懒惰求值<br>
当我们将一个istream_iterator绑定到一个流时，标准库并不保证迭代器立即从流读取数据。具体实现可以推迟从流中读取数据，直到我们使用迭代器时才真正读取。<br>
### ostream_iterator操作
我们可以对任何具有输出运算符(<<运算符) 的类型定义ostream_iterator。<br>
```cpp
ostream_iterator<T> out(os) 
//out将类型为T的值写到输出流os中
ostream_iterator<T> out(os,d);
 //out 将类型为T的值写到输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数租。
out = val; 
```
我们可以用ostream_iterator来输出值的序列<br>
```cpp
ostream_iterator<int> out_iter(cout," ");
for(auto e:vec)
    *out_iter ++ = e;
cout<<endl;
```
此程序将vec中的每个元素写到cout，每个元素后加一个空格。每次向out_iter赋值时，写操作就会被提交。<br>
可以忽略解引用和递增运算<br>
```cpp
for(auto e :vec)
out_iter = e;
cout<<endl;
```
更简单
```cpp
copy(vec.begin(),vec.end(),out_iter);
cout<<endl;
```
使用流迭代器处理类类型<br>
我们可以为任何定义了输入运算符(>>)的类型创建istream_iterator对象。类似的，只要类型有输出运算符(<<)，我们就可以为其定义ostream_iterator。<br>
```cpp
istream_iterator<Sales_item> item_iter(cin),eof;
ostream_iterator<Sales_item> out_iter(cout,"\n"); 
Sales_item sum = *item_iter++;
while(item_iter != eof){
    if(item_iter -> isbn() == sum.isbn())
        sum+= *item_iter++;
     else{
             out_iter = sum;
             sum = *item_iter++;
}
}
out_iter = sum;

std::ifstream ifs("H:/code/C++/Cpp_Primer_Answers/data/books.txt");
    
 	std::istream_iterator<string> in(ifs), eof;
 	std::vector<string> vec;
 	std::copy(in, eof, back_inserter(vec));

 
 	std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<string>(std::cout, "\n"));
 

vector<int> v;


istream_iterator<int> int_it(cin), int_eof;
 	 
 	copy(int_it, int_eof, back_inserter(v));
 	sort(v.begin(), v.end());
 	 
 	copy(v.begin(), v.end(), ostream_iterator<int>(cout," "));
 	cout << endl;
```
### 反向迭代器
反向迭代器就是在容器中从尾元素向首元素反向移动的迭代器。对于反向迭代器，递增以及递减操作的含义会颠倒过来
rbegin(),rend(),crbegin(),crend();
<br>
## 泛型算法结构
任何算法的最基本特性是它要求其迭代器提供哪些操作。5个迭代器类别<br>
输入迭代器，输出迭代器，前向迭代器，双向迭代器，随机访问迭代器<br>

### 关联容器
关联容器和顺序容器有着根本的不同：关联容器中的元素是按关键字来保存和访问的。与之相对，顺序容器中的元素是按它们在容器中的位置来顺序保存和访问的。
虽然关联容器的很多行为与顺序容器相同，但其不同之处反映了关键字的作用。<br>

@关联容器支持高效的关键字查找和访问。两个主要的关联容器类型是map和set。 <br>
map中的元素是一些关键字-值(key-value) 对：关键字起到索引的作用，值则表示与索引相关联的数据。<br>
set中的每个元素只包含一个关键字；set支持高效的关键字查询操作---检查一个给定关键字是否在set中。<br>
**允许重复关键字的容器的名字中都包含单词multi；<br>**
**不保持关键字按顺序存储的容器的名字都以单词unordered开头。**<br>
unordered_multi_set是一个允许重复关键字，元素无序保存的集合，而一个set则是一个要求不重复关键字，有序存储的集合。<br>
@无序容器使用哈希函数来组织元素。<br>
@类型map和multimap定义在头文件map中；<br>
@set和multiset定义在头文件set中<br>
@无序容器则定义在头文件unordered_map和unordered_set中。<br>
### 关联容器类型
按关键字有序保存元素<br>
**map关联数组：保存关键字-值对**<br>
**set关键字即值，即只保存关键字的容器**<br>
**multimap关键字可重复出现的map**<br>
**multiset关键字可重复出现的set**<br>
### 无序集合
unordered_map 用哈希函数组织的map<br>
unordered_set 用哈希函数组织的set<br>
unordered_multimap 哈希组织的map；关键字可以重复出现<br>
unordered_multiset 哈希组织的set；关键字可以重复出现<br>

### 使用关联容器
map类型通常被成为关联数组(associative array)<br>
### 使用map
```cpp
map<string, size_t> word_count; //string到size_t的空map
string word;
while(cin>>word)
    ++word_count[word]; //提取word的计数器size_t并将其加1
for(const auto &w : word_count)
    cout<< w.first << " occurs"<< w.second << ((w.second>1)?" times":"time:")<<endl;
```
如果word还没在map中，下标运算符会创建一个新元素<br>
@当从map中提取一个元素时。会得到一个pair类型的对象。pair是一个模板类型，保存两个名为first和second的（公有）数据成员<br>
map所使用的pair用first成员保存关键字，用second成员保存对应的值<br>
### 使用set
使用set保存想忽略的单词，只对不在集合中的单词统计出现次数<br>
```cpp
map<string,size_t> word_count; //string 到size_t 
set<string> exclude = {"The","But","And","Or","An","A","the"...};
string word;
while(cin>>word)
       if(exclude.find(word) == exclude.end())
             ++word_count[word]; 
```
### 关联容器的概述
@关联容器支持普通容器操作<br>
@关联容器不支持顺序容器的位置相关操作<br>
@关联容器的迭代器都是双向的<br>
### 定义关联容器
当定义一个map时，必须既指明关键字类型又指明值类型；<br>
定义一个set时，只需指明关键字类型，因为set中没有值。<br>
```cpp
map<string,string> authors={{"james","Chen"},{"jane","wang"}};
```
### 初始化multimap或multiset
一个map或set中的关键字必须是唯一的，即对于一个给定的关键字，只能有一个元素的关键字等于它。<br>
容器multimap和multiset没有此限制，他们都允许多个元素具有相同的关键字。<br>
```cpp
vector<int> ivec;
for(vector<int>::size_type i=0;i!=10;++i){
    ivec.push_back(i);
    ivec.push_back(i); //repeat
}
set<int> iset(ivec.begin(),ivec.end());
multiset<int> miset(ivec.cbegin(),ivec.cend());
```
### 关键字类型的要求
关联容器对于关键字有一些限制。对于有序容器---map、multimap、set以及multiset，关键字类型必须定义元素比较的方法。默认情况下，标准库使用关键字类型的<运算符来比较两个关键字。在集合类型中，关键字类型就是元素类型；在映射类型中，关键字类型是元素的第一部分的类型。<br>
@传递给排序算法的可调用对象必须满足与关联容器中关键字一样的类型要求<br>
#### 有序容器的关键字类型
可以向一个算法提供我们自己定义的比较操作，与之类似，也可以提供自己定义的操作来代替关键字上的<运算符。所提供的操作必须在关键字类型上定义一个严格的弱序（可看作小于等于）<br>
#### 使用关键字类型的比较函数
用来组织一个容器中元素的操作的类型也是该容器类型的一部分。为了指定使用自定义的操作，必须在定义关联容器类型时提供此操作的类型。<br>
例如，我们不能直接定义一个Sales_data的multiset，因为Sales_data没有<运算符。但是可以用compareIsbn函数来定义一个multiset。**此函数在Sales_data对象的ISBN成员上定义了一个严格弱序。**<br>
```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs){
return lhs.isbn()<rhs.isbn();
}
```
为了使用自己定义的操作，在定义multiset时，我们必须提供两个类型：关键字类型Sales_data，以及比较操作类型---应该是一种函数指针类型，可以指向compareIsbn。 当定义此容器类型的对象时，需要提供想要使用的操作的指针。<br>
multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);  bookstore中多条记录可以有相同的ISBN<br>
bookstore中的元素以ISBN的顺序进行排列<br>
#### 不使用decltype
```cpp
bool (*pf)(const Sales_data &lhs, const Sales_data &rhs) = compareIsbn
using F = bool (const Sales_data &lhs, const Sales_data &rhs)
multiset<Sales_data, F*> bookstore( compareIsbn);
```
### pair类型
在介绍关联容器操作之前，我们需要了解名为pair的标准库类型，它定义在头文件utility中。<br>
一个pair保存两个数据成员。<br>
```cpp
pair<string ,string> annon; //save two string
pair<string, size_t> word_count;
pair<string, vector<int>> line; 
pair<string ,string> annon{"james","joyce"};
```
与其他标准库类型不同@pair的数据成员是public的<br>
**两个成员分别命名为first合second。** 
```cpp
cout<< w.first <<"occurs" <<w.second<<endl;
```
@mapde 元素是pair<br>
创建pair对象的函数<br>
```cpp
pair<string, int> process(vector<string> &v){
    if(!v.empty())
         return {v.back(), v.back().size()};   //make_pair(v.back(), v.back().size());
    else
         return pair<string,int>();
}
```
### 关联容器操作
除了顺序容器的类型，关联容器还定义了以下类型<br>
key_type 此容器类型的关键字类型<br>
mapped_type 每个关键字关联的类型；只适用与map<br>
value_type 对于set，与key_type相同<br>
对于map，为pair<const key_type, mapped_type><br>
对与set类型，key_type 和 value_type是一样的；set中保存的值就是关键字<br>
```cpp
set<string>::value_type v1; //v1 is string
set<string>::key_value v2; //v2 is string
map<string, int> ::value_type v3 //v3 is a pair<const string, int>
map<string, int>::key_type v4 /v4 is a string
map<string,int>::mapped_type v5 //v5 is an int
```
只有map类型才能定义mapped_type<br>
### 关联容器迭代器
当解引用一个关联迭代器时，我们会得到一个类型为容器的value_type的值的引用。对于map而言，value_type是一个pair类型，其first成员保存const的关键字，second成员保存值<br>
```cpp
auto map_it = word_count.begin(); 
//获得指向word_count中一个元素的迭代器    *map_it 是指向一个pair<const string, size_t> 对象的引用<br>
cout<<map_it->first;
cout<<" " <<map_it->second;
```
@必须记住，一个map的value_type是一个pair，我们可以改变pair的值，但不能改变关键字成员的值。<br>
#### set的迭代器是const的
虽然set类型同时定义了iterator和const_iterator类型，但两种类型都只允许只读访问set中的元素。与不能改变一个map元素的关键字一样，一个set中的关键字也是const的。可以用一个set迭代器来读取元素的值，但不能修改<br>
```cpp
set<int> iset = {0,1,2,3,4,5,6,7,8,9};
set<int> :: iterator set_it = iset.begin();
if(set_it != iset.end()){
    *set_it = 42; //错误：set中方的关键字是只读的
     cout<<*set_it <<endl; 
}
```
### 遍历关联容器
map和set类型都支持begin和end操作。与往常一样，我们可以用这些函数获取迭代器，然后用迭代器来遍历容器。🌰 :
```cpp
auto map_it = word_count.begin(); //获得一个指向首元素的迭代器
while (map_it != word_count.cend()){   //比较当前迭代器和尾后迭代器
    cout<<map_it->first<<" occurs"<< map_it->second <<" times"<<endl; 
    ++map_it;
}
```
### 添加元素
关联容器的insert成员向容器中添加一个元素或一个元素范围。由于map和set（以及对应的无序类型）包含不重复的关键字，因此插入一个已存在的元素对容器没有任何影响<br>
```cpp
vector<int> ivec = {1,2,3,4,5,6,7,8};
set<int> set2;
set2.insert(ivec.cbegin(),ivec.cend()); //set2有八个元素
set2.insert({1,2,3,4,56,7,8,9}) //set2有9个元素
```
### 向map添加元素
对一个map进行insert操作时，必须记住元素类型是pair。通常，对于想要插入的数据，并没有一个现成的pair对象。可以在insert的参数列表中创建一个pair
```cpp
word_count.insert({word,1});
word_count.insert(make_pair(word,1));
word_count.insert(pair<string,size_t>(word,1));
word_count.insert(map<string,size_t>::value_type(word,1));
```

#### 检测insert的返回值
insert（或emplace）返回的值依赖于容器类型和参数。对于不包含重复关键字的容器，添加单一元素的insert和emplace版本返回一个pair，告诉插入操作是否成功。<br>
```cpp
//统计每个单词在输入中出现次数的一种更烦琐的方法
map<string,size_t> word_count;
string word;
while(cin>>word){
     auto ret = word_count.insert({word,1});
     if(!ret.second)
        ++ret.first->second;
}   //first 是一个迭代器
```
向multiset或multimap添加元素
```cpp
multimap<string,string> authors;
authors.insert({"Barth,john","Sot,ddd"});
authors.insert({"Barth,john","lost in the forest"});
```
对允许重复关键字的容器，接受单个元素的insert操作返回一个指向新元素的迭代器。这里无须返回一个bool值，因为insert总是向这类容器中加入一个新元素。
### 删除元素
关联容器定义了三个版本erase。与顺序容器一样，我们可以通过传递给erase一个迭代器或一个迭代器对来删除一个元素或者一个元素范围。这两个版本的erase与对应的顺序容器的操作非常相似：指定的元素被删除，函数返回void<br>
关联容器提供一个额外的erase操作，他接受一个key_value参数。此版本删除所有匹配给定关键字的元素（如果存在的话），返回实际删除的元素的数量<br>
```cpp
if(word_count.erase(removal_word))
    cout<< removal_word;
```
对于保存不重复关键字的容器，erase的返回值总是1或0.<br>
```cpp
c.erase(k)
c.erase(p)
c.erase(b,e)
```
#### map的下标操作
map和unordered_map同期提供了下标运算符和一个对应的at函数。 **set类型不支持下标。不能对一个multimap或一个unordered_multimap进行下标操作**<br>
**c[k], c.at(k)<br>**
#### 使用下标操作的返回值
map的下标运算，通过关键字获取值<br>
### 访问元素
关联容器提供多种查找一个指定元素的方法。<br>
c.find(k) //返回一个迭代器，指向第一个关键字为k的元素，若k不再容器中，则但会尾后迭代器<br>
c.count(k) 返回关键字等于k的元素的数量，对于不允许重复关键字的容器，返回值永远是0或1<br>
c.lower_bound(k) 返回一个迭代器，指向第一个关键字不小于k的元素<br>
c.upper_bound(k) 返回一个迭代器，指向第一个关键字大于k的元素<br>
c.equal_range(k) 返回一个迭代器pair，表示关键字等于k的元素的范围。若k不存在，pair的两个成员均等于c.end()<br>
lower_bound和upper_bound不适用于无序容器<br>
下标和at操作只适用于非const的map和unordered_map<br>
@对map使用find代替下标操作<br>
@在multimap或multiset中查找元素<br>
当我们遍历一个multimap或multiset时，保证可以得到序列中所有具有给定关键字的元素<br>
一种不同的，面向迭代器的解决方法   lower_bound ?= upper_bound<br>
#### euqal_range函数
此函数接受一个关键字，返回一个迭代器pair。若关键字存在，则第一个迭代器指向第一个与关键字匹配的元素，第二个迭代器指向最后一个匹配元素之后的位置。若未找到匹配元素，则两个迭代器都指向关键字可以插入的位置<br>
```cpp
for(auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first)
          cout<<pos.first->second<<endl;
```
### 无序容器
新标准定义了4个无序关联容器。这些容器不是使用比较运算符来组织元素，而是使用一个哈希函数和关键字类型的==运算符<br>
在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的。<br>
使用无序容器，管理桶<br>
无序容器提供了一组管理桶的函数<br>
### 桶接口
```cpp
c.bucket_count() //正在使用的桶的数目
c.max_bucket_count//容器能容纳的最多的桶的数量
c.bucket_size(n) //第n个桶中有多少个元素
c.bucket(k) //关键字为k的元素在拿个桶里
```

### 桶迭代
local_iterator  可以用来访问桶中元素的迭代器类型<br>
const_local_iterator 桶迭代器的const版本<br>
c.begin(),c.end()<br>
c.cbegin(),c.cend()<br>

### 哈希策略
c.local_factor() //每个桶的平均元素数量，返回float值<br>
c.max_load_factor() //c试图维护的平均桶的大小，返回float 值。c会在需要的时候添加新的桶，以使得load_factor<=max_load_factor<br>
c.rehash(n) 重组存储，使得bucket_count>=n且bucket_count> size/max_load_factor<br>
c.reverse(n)  重组存储，使得c可以保存n个元素不必rehash<br>
﻿无序容器对关键字类型的要求<br>

### 动态内存
**话甘快，就到动态内存，第十二章了，其实从变量，基本类型，字符串，语句，指针引用，函数指针，到io库，lambda捕获变量表达式，不改变容器的泛型算法，顺序容器，关联容器再到依赖于哈希函数性能的无序容器，这些知识点的补充，对于个人技术来说是一个很大的补足，C++我曾经想过放弃，但是每天这样早上补充一下，想一下计算机底层的知识，对我来说还是很有帮助的。**
这一章的最后我会编写一个文本查询程序，主要使用以上所学的知识，这是一个目标<br>
到目前为止，我们编写的程序中所使用的对象都有着严格定义的生存期。<br>
@全局对象在程序启动时分配，在程序结束时销毁。<br>
@局部自动对象，当我们进入其定义所在程序块时被创建，在离开块时销毁。<br>
@局部static对象在第一次使用前分配，在程序结束时销毁<br>
除了自动和static对象外，C++还支持动态分配对象。**动态分配的对象的生存期与它们在哪里创建是无关的，**只有当显式地被释放时，这些对象才会销毁。<br>
动态对象的正确释放被证明是编程中极其容易出错的地方。<br>
为了更安全地使用动态对象，标准库定义了两个智能指针类型来管理动态分配的对象。<br>
当一个对象应该被释放时，指向它的智能指针可以确保自动地释放<br>
@ **静态内存**用来保存局部static对象、类static数据成员以及定义在任何函数之外的变量。<br>
@ **栈内存**用来保存定义在函数内的非static对象<br>
@ **分配在静态或栈内存中的对象由编译器自动创建和销毁**<br>
@ 对于栈对象，仅在其定义的程序块运行时才存在
@ **static对象**在使用之前分配，在程序结束时销毁
除了静态内存和栈内存，每个程序还拥有一个内存池。这部分内存被称作自由空间（free store）或堆（heap）。程序用堆来存储动态分配的对象---即，那些在程序运行时分配的对象<br>
动态对象的生存期由程序来控制，也就是说，当动态对象不再使用时，我们的代码必须显式地销毁它们<br>

### 动态内存与智能指针
动态内存管理是通过一对运算符来完成的：@new 在动态内存中为对象分配空间并返回一个指向该对象的指针，我们可以选择对对象进行初始化<br>
@delete 接受一个动态对象的指针，销毁该对象，并释放与之关联的内存<br>

因为确保在正确的时间释放内存是及其困难的，所以标准库提供了两种智能指针类型来管理动态对象。@智能指针的行为类似常规指针，重要区别是它负责自动释放所指向的对象。新标准库提供的这两种智能指针的区别在与管理底层指针的方式：<br>
@ **share_ptr允许多个指针指向同一个对象**<br>
@ **unique_ptr则“独占”所指向的对象**<br>
@ **weak_ptr，伴随类，是一种弱引用，指向shared_ptr所管理的对象**。<br>
这三种类型都定义在memory头文件中<br>
### shared_ptr类
类似vector，智能指针也是模版。因此，当我们创建一个智能指针时，必须提供额外的信息----指针可以指向的类型。与vector一样，我们在尖括号内给出类型，之后是所定义的这种智能指针的名字<br>
```cpp
shared_ptr<string> p1; //shared_ptr，可以指向string
shared_ptr<list<int>> p2; //shared_ptr, 可以指向int的list
```
默认初始化的智能指针中保存着一个空指针<br>
@智能指针的使用方式与普通指针类似。解引用一个智能指针返回它指向的对象。如果在一个条件判断中使用智能指针，效果检测它是否为空：<br>
```cpp
if(p1 && p1->empty())
    *p1 = "hi";
```
shared_ptr 和 unique_ptr 都支持的操作<br>
shared_ptr<T> sp   空智能指针，可以指向类型为T 的对象<br>
unique_ptr<T> up    <br>
p,*p,p->mem, p.get(), swap(p,q),p.swap(q)<br>

### shared_ptr 独有的操作
make_shared<T>(args)  返回一个shared_ptr, 指向一个动态分配的类型为T 的对象，使用args初始化此对象<br>
shared_ptr<T>p(q)   p是shared_ptr q的拷贝；此操作会递增q中的计数器。q中的指针必须能转换为T*<br>
p = q  p和q都是shared_ptr，所保存的指针必须能相互转换。此操作会递减p的引用计数，递增q的引用计数；若p的引用计数变为0，则将其管理的原内存释放<br>
p.unique()   若p.use_count() 为1， 返回true；否则返回false<br>
p.use_count()   返回p共享对象的智能指针数量；可能很慢，主要用于调试<br>

### make_shared函数
最安全的分配和使用动态内存的方法是调用一个名为make_shared 的标准库函数<br>
此函数的动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr。与智能指针一样，make_shared也定义在头文件memory中<br>
当要用make_shared 时，必须指定想要创建的对象的类型。定义方式与模版类相同。在函数名之后跟一个尖括号，在其中给定类型：<br>
```cpp
shared_ptr<int> p3 = make_shared<int>(42);   //指向一个值为42的int的shared_ptr
shared_ptr<string> p4 = make_shared<string>(10,'9'); // p4指向一个值为“9999999999999”的string
shared_ptr<int> p5 = make_shared<int>();   // p5 指向一个值初始化的int，即值为0
auto p6 = make_shared<vector<string>> ();
```
### shared_ptr 的拷贝和赋值
```cpp
auto p = make_shared<int>(42);//p指向的对象只有p一个引用者
auto q(p); //p和q指向相同对象，此对象有两个引用者
```
### @引用计数
拷贝一个shared_ptr 计数器就会递增<br>
给shared_ptr赋予一个新值或是shared_ptr被销毁（例如一个局部的shared_ptr离开其作用域时）计数器就会递减<br>
shared_ptr自动销毁所管理的对象，还会自动释放相关联的内存<br>
//factory返回一个shared_ptr，指向一个动态分配的对象<br>
```cpp
shared_ptr<Foo> factory(T args){
return make_shared<Foo>(arg);
}
void use_factory(T arg){
shared_ptr<Foo>  p = factory(arg);
return p; //当我们返回p时，引用计数进行了递增操作；
} //p离开了作用域，但它指向的内存不会被释放掉
```

#### 使用了动态生存期的资源的类
1. 程序不知道自己需要使用多少对象<br>
2. 程序不知道所需对象的准确类型<br>
3. 程序需要在多个对象间共享数据<br>

容器类是处于第一种原因而使用动态内存的典型例子<br>
```cpp
Blob<string> b1;
{
Blob<string> b2 = {"a","an","the"};
b1 = b2; //b1和b2共享相同的元素
} // b2 被销毁了，但b2中的元素不能销毁
// b1指向最初由b2创建的元素
```
### 定义StrBlob类
一个管理string的类，此版本命名为StrBlob<br>
实现一个新的集合类型的最简单的方法是使用某个标准库容器类管理元素。采用这种方法，我们可以借助标准库类型来管理元素所使用的内存空间。<br>
但是我们不能在一个Blob 对象内直接保存vector，因为一个对象的成员在对象销毁时也会被销毁。<br>
为了实现我们所希望的数据共享，我们为每个StrBlob设置一个shared_ptr来管理动态分配的vector。 此shared_ptr 的成员将记录有多少个StrBlob共享相同的vector，并在vector的最后一个使用者被销毁时释放vector<br>
```cpp
class StrBlob{
public:
    typedef vector<string> ::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il); //使用初始化列表来初始化其data成员，令他指向一个动态分配的vector。
    size_type size() const {return data->size();}
    bool empty() const { return data->empty();}
    void push_back(const string &t) {data->push_back(t);}
    void pop_back();
    string& front();
    string& back();
private:
    shared_ptr<vector<string>> data;  //如果data[i] 不合法，抛出一个异常
    void check(size_type i , const string &msg) const;
};
```
在此类中我们实现了size,empty和push_back成员。这些成员通过指向底层vector的data成员类完成它们的工作。<br>
```cpp
StrBlob::StrBlob(): data(make_shared<vector<string>>()){}
StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
```
### 元素访问成员函数
pop_back、front和back操作访问vector中的元素。这些操作在试图访问元素之前必须检查元素是否存在。<br>
```cpp
void StrBlob::check(size_type i, const string &msg) const{
    if( i >= data->size())
        throw out_of_range(msg);
}
```
pop_back和元素访问成员函数首先调用check。如果check成功，这些成员函数继续利用底层vector的操作来完成自己的工作<br>
```cpp
string& StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front();
}
string& StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back(){
    check(0,"pop_back on empty StrBlob");
    return data->pop_back();
}
```
### StrBlob的拷贝、赋值和销毁
tips：shared_ptr计数器<br>

#### 直接管理内存
C++语言定义了两个运算符来分配和释放动态内存。运算符new分配内存，delete释放new分配的内存<br>
**相对于智能指针，使用这两个运算符管理内存非常容易出错，随着我们逐步详细介绍这两个运算符，这一点会更为清楚。**<br>
而且自己直接管理内存的类与使用智能指针的类不同，它们不能依赖类对象拷贝、赋值和销毁操作的任何默认定义。因此，使用智能指针的程序更容易编写和调试<br>
#### 使用new动态分配和初始化对象
在自由空间分配的内存是无名的，因此new无法为其分配的对象命名，而是返回一个指向该对象的指针<br>
```cpp
int *pi = new int; //pi指向一个动态分配的、未初始化的无名对象
```
此new表达式在自由空间构造一个int型对象，并返回指向该对象的指针<br>
默认情况下，动态分配的对象是默认初始化的，这意味着内置类型或组合类型的对象的值将是为定义的，而类类型对象将用默认构造函数进行初始化：<br>
```cpp
string *ps = new string;
int *pt = new int;
``` 
#### 直接初始化
```cpp
int *pi = new int(1024);
string *ps = new string(10,'9'); 
vector<int> *pv = new vector<int> {1,2,3,4,5,6,7,8};
```
也可以使用对动态分配的对象进行值初始化，只需在类型名之后跟一对空括号即可：<br>
```cpp
string *ps1 = new string();
int *pi1 = new int();
```
@出于与变量初始化相同的原因，对动态分配的对象进行初始化通常是个好主意<br>
```cpp
auto p1 = new auto(obj); //p指向一个与obj类型相同的对象，该对象用obj进行初始化
```
p1是一个指针，指向从obj自动推断出的类型。若obj是一个int，那么p1就是int*; 若obj是一个string，那么p1是一个string *；依此类推。新分配的对象用obj的值进行初始化。<br>
#### 动态分配的const对象
用new分配const对象是合法的<br>
```cpp
//分配并初始化一个const int
const int *pci = new const int(1024);
//分配并默认初始化一个const的空string
const string *pcs = new const string;
```
### 内存耗尽
一旦一个程序用光了它所有可用的内存，new表达式就会失败。默认情况下，如果new不能分配所要求的内存空间，它会抛出一个类型为bad_alloc的异常。我们可以改变使用new的方式来组织它抛出异常：<br>
```cpp
    int *p1 = new int; //如果分配失败，返回一个空指针，抛出std::bad_alloc
    int *p2 = new (nothrow) int; //如果分配失败，new返回一个空指针
```
bad_alloc和nothrow定义在头文件new中<br>
### 释放动态内存
为了防止内存耗尽，在动态内存使用完毕后，必须将其归还给系统。我们通过delete表达式来将动态内存归还给系统。delete表达式接受一个指针，指向我们想要释放的对象：<br>
```cpp
delete p; //p必须指向一个动态分配的对象或是一个空指针
```
两个动作：1. 销毁给定的指针指向的对象 2. 释放对应的内存<br>
### 指针值和delete
我们传递给delete的指针必须指向动态分配的内存，或者是一个空指针。释放一块并非new分配的内存，或者将相同的指针值释放多次，其行为是未定义的<br>
通常情况下，编译器不能分辨一个指针指向的是静态还是动态分配的对象。类似的，编译器也不能分辨一个指针所指向的内存是否已经被释放了。<br>
虽然一个const对象的值不能被改变，但它本身是可以被销毁的。如同任何其他动态对象一样，想要释放一个const动态对象，只要delete指向它的指针即可<br>
```cpp
const int *pci = new const int(1024);
delete pci; //正确：释放一个const对象
```
动态对象的生存期直到被释放为止。<br>
```cpp
Foo * factory(T arg){
return new Foo(arg); //调用者负责释放此内存
}

void use_factory(T arg){
Foo *p = factory(arg); //若未delete p，p就离开了作用域，但它所指向的内存没有被释放
delete p; //释放了内存
}  
```
@有内置指针（而不是智能指针）管理的动态内存被显式释放前一直都会存在
delete之后重置指针值，这只是提供了有限的保护
p = nullptr

shared_ptr和new结合使用
如前所述，如果我们不初始化一个智能指针，它就会被初始化为一个空指针。
shared_ptr<double> p1; //shared_ptr 可以指向一个double
shared_ptr<int> p2(new int(42)); //p2 指向一个值为42的int
接受指针参数的智能指针构造函数是explicit的（亦即不能被隐式初始化） 因此我们不能将一个内置指针转换为一个智能指针，必须使用直接初始化形式来初始化一个智能指针
shared_ptr<int> = new int(1024); //错误，必须使用直接初始化形式
shared_ptr<int> p1(new int(1024));
相同的原因，一个返回shared_ptr的函数不能在其返回语句中隐式转换一个普通指针
shared_ptr<int> clone(int p){
    return shared_ptr<int>(new int(p));
}
默认情况下，一个用来初始化智能指针的普通指针必须指向动态内存，因为智能指针默认使用delete释放它所关联的对象。我们可以将智能指针绑定到一个指向其他类型的资源的指针上，但是为了这样做，必须提供自己的操作来替代delete。
shared_ptr<T> p(q);  p管理内置指针q所指向的对象；q必须指向new分配的内存且能够转换为T* 类型
shared_ptr<T> p(u)  p从unique_ptr u那里接管了对象的所有权；将u置为空
shared_ptr<T> p(q,d);  p接管了内置指针q所指向的对象的所有权。q必须能转换为T* 类型。p将使用可调用对象d来替代delete
shared_ptr<T>p(p2,d); p是shared_ptr p2的拷贝，唯一的区别是p将用可调用的对象d来代替delete
p.reset()  若p是唯一指向其对象的shared_ptr， reset会释放此对象。若传递了可选的参数内置指针q，会令p指向q，，否则会将p置为空。若还传递了参数d，将会调用d而不是delete来释放q 
p.reset(q)
p.reset(q,d)

不要混合使用普通指针和智能指针
shared_ptr 可以协调对象的析构，但这仅限于其自身的拷贝（也是shared_ptr)之间。这也是为什么我们推荐使用make_shared而不是new的原因。这样我们就能在分配对象的同时就将shared_ptr 与之绑定，从而避免了无意中将同一块内存绑定到多个独立创建的shared_ptr上

void process(shared_ptr<int> ptr){
//使用ptr
}// ptr离开作用域，被销毁
process的参数是船只方式传递的，因此实参会被拷贝到ptr中。拷贝一个shared_ptr会递增引用计数，因此，在process运行过程中，引用计数值至少为2.当process结束时，ptr的引用计数会递减，但不会变为0.因此，当局部变量prt被销毁时，ptr所指向的内存不会被释放
shared_ptr<int> p(new int(42));
process(p);
int i = *p ;
虽然不能传递给process一个内置指针，但可以传递给它一个（临时的）shared_ptr，这个shared_ptr是用一个内置指针显式构造的。但是，这样做很可能会导致错误
int *x(new int(1024)); //⚠️危险，x是一个普通指针，不是一个智能指针
process(x); 错误，不能将int* 转换为一个shared_ptr<int>
process(shared_ptr<int> (x)); //合法！但内存会释放
int j = *x; 未定义，x是一个空悬指针
⚠️ 使用一个内置指针来访问一个智能指针所负责的对象是很危险的，因为我们无法知道对象何时会被销毁
也不要使用get初始化另一个智能指针或为智能指针赋值
智能指针类型定义了一个名为get的函数，它返回一个内置指针，指向智能指针管理的对象。此函数是为了这样一种情况而设计的：我们需要向不能使用智能指针的代码传递一个内置指针。使用get返回指针的代码不能delete此指针。
shared_ptr<int> p(new int(42)); 
int *q = p.get(); //正确，但使用q时要注意，不要让它管理的指针被释放
{ 
shared_ptr<int>(q); //undefined 两个独立的shared_ptr指向相同的内存
}//程序结束，q被销毁，它指向的内存被释放
int foo = *p; //为定义：p指向的内存已经被释放了
@get用来将指针的访问权限传递给代码，你只有在确定代码不会delete指针的情况下，才能使用get。特别是，永远不要用get初始化另一个智能指针或者为另一个智能指针赋值
其他shared_ptr操作
shared_ptr 定义了reset来将一个新的指针赋予一个shared_ptr
p=new int(1024); //错误：不能将一个指针赋予shared_ptr
p.reset(new int(1024)); //正确，p指向一个新对象
与赋值类似，reset会更新引用计数，如果需要的话，会释放p指向的对象！reset成员经常与unique一起使用，来控制多个shared_ptr共享的对象
if(!p.unique())
p.reset(new string(*p));
*p+=newVal;
智能指针和异常
@一个简单的确保资源被释放的方法是使用智能指针。
如果使用智能指针，即使程序块过早结束，智能指针类也能确保在内存不再需要时，将其释放
void f(){
    shared_ptr<int> sp(new in(42)); //分配一个新对象
   //这段代码抛出一个异常，且在f中未捕获
}//在函数结束时shared_ptr自动释放内存

与之相对，当发生异常时，我们直接管理的内存是不会自动释放的。如果使用内置指针管理内存，且在new之后在对应的delete之前发生异常，则内存不会被释放
void f(){
int *ip = new int(42); //动态分配一个对象
//这段代码抛出一个异常，且在f中未捕获
delete ip; //在退出之前释放内存 
}
因为抛出了异常，内存永远不会被释放
﻿智能指针与哑类
包括所有标准库在内的很多C++类都定义了析构函数，负责清理对象使用的资源。但是，不是所有的类都是这样良好定义的。特别是那些为C和C++两种语言设计的类，通常都要求用户显式地释放所使用的任何资源。
那些分配了资源，而又没有定义析构函数来释放这些资源的类，可能会遇到与使用动态内存相同的错误---程序员非常容易忘记释放资源。类似的，如果在资源分配和释放之间发生异常，程序也会发生资源泄漏。
与管理动态内存类似，我们通常可以使用类似的技术来管理不具有良好定义的析构函数的类。例如，假定我们正在使用一个C和C++都使用的网络库，使用这个库的代码可能是这样的
struct destination; //表示我们正在连接什么
struct connection;  //使用连接所需信息
connection connect (destination *); //打开连接
void disconnect(connection); //关闭给定的连接
void f(destination &d){
//获得一个链接；记住使用完就关闭它
connection c = connect(&d);
//使用链接
//如果我们在f退出前忘记调用disconnect，就无法关闭c了
}
以上，如果connection是一个析构函数，就可以在f结束时由析构函数自动关闭连接，但是connection没有析构函数。这个问题与我们上一个程序中使用shared_ptr 避免内存泄漏几乎是等价的。使用shared_ptr 来保证connection 被正确关闭，已被证明是一种有效的方法
使用我们自己的释放操作
@默认情况下，shared_ptr假定它们指向的是动态内存。因此，当一个shared_ptr被销毁时，它默认地对它管理的指针进行delete操作。为了用shared_ptr来管理一个connection,我们必须首先定义一个函数来代替delete。这个删除器deleter函数必须接受单个类型为connection*的参数
void end_connection(connection *p){disconnect (*p);}
当我们创建一个shared_ptr 时，可以传递一个（可选的） 指向删除器函数的参数
void f(destination &d)
{connection c = connect(&d);
shared_ptr<connect> p(&c,end_connection); //使用连接
当f退出时，即使是由于异常而退出，connection会被正确关闭
}
@当p被销毁时，他不会对自己保存的指针执行delete，而是调用end_connection。接下来，end_connection会调用disconnect,从而确保连接被关闭。
@如果f正常退出，那么p的销毁会作为结束处理的一部分。如果发生了异常，p同样会被销毁，从而连接被关闭
智能指针陷阱
@不使用相同的内置指针值初始化（或reset）多个智能指针
@不delete get()返回的指针
@不使用get()初始化或reset另一个智能指针
@如果你使用get() 返回的指针，记住最后一个对应的智能指针销毁后，你的指针就变为无效了
@如果你使用智能指针管理资源不是new分配的内存，记住传递给它一个删除器
unique_ptr
一个unique_ptr “拥有” 它所指向的对象。与shared_ptr 不同，某个时刻只能有一个unique_ptr指向一个给定对象。当unique_ptr被销毁，它所指向的对象也被销毁。
@类似shared_ptr，初始化unique_ptr 必须采用直接初始化形式
unique_ptr<double> p1; //可以指向一个double 的unique_ptr
unique_ptr<int> p2(new int(42)); //p2 指向一个值为42的int
由于一个unique_ptr拥有它指向的对象，因此unique_ptr 不支持普通的拷贝或赋值操作：
unique_ptr<string> p1(new string("sssss");
unique_ptr<string> p2(p1) //错误：unique_ptr不支持拷贝
unique_ptr<string> p3;
p3 = p2； 错误，unique_ptr不支持赋值
unique_ptr操作
unique_ptr<T> u1  空unique_ptr，可以指向类型为T的对象。u1会使用delete来释放它的指针；
unique_ptr<T,D> u2  u2会使用一个类型为D的可调用对象来释放它的指针
unique_ptr<T,D> u(d) 空unique_ptr，指向类型为T的对象，用类型为D的对象d来代替delete
u= nullptr 
u.rellease(); u放弃对指针的控制权，返回指针，并将u置为空
u.reset() 释放u指向的对象
u.reset(q)  如果提供了内置指针q，令u指向这个对象；否则将u置为空
u.reset(nullptr)
虽然我们不能拷贝或赋值unique_ptr，但可以通过调用release或reset将指针的所有权从一个（非const） unique_ptr转移给另一个unique
unique_ptr<string> p2(p1.release());
unique_ptr<string> p3(new string("rrr"));
//将所有权从p3转移给p2
p2.reset(p3.release()); reset 释放了p2原来指向的内存
@调用release会切断unique_ptr和它原来管理的对象间的联系
@release返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值
auto p = p2.release();  用另一个智能指针保存release返回的指针。最后delete p
传递unique_ptr参数和返回unique_ptr
不能拷贝unique_ptr的规则有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr
unique_ptr<int> clone(int p){
return unique_ptr<int>(new int(p)); //正确，从int*创建一个unique_ptr<int>
}
还可以返回一个局部对象的拷贝
unique_ptr<int> clone(int p){
return unique_ptr<int> ret(new int(p)); //正确，从int*创建一个unique_ptr<int>
// ...
return ret;
}
向unique_ptr传递删除器
unique_ptr<objT, delT> p(new objT, fcn);
p会指向个objT类型的对象，并使用一个类型为delT的对象释放objT对象
会调用一个名为fcn的delT类型对象
void f(destination &d)
{
connection c = connect(&d);
unique_ptr<connection,decltype(end_connection)*> p(&c,end_connection);
}
weak_ptr
weak_ptr是一种不控制所指向对象生存期的智能指针，它指向由一个shared_ptr管理的对象。将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放。即使有weak_ptr指向对象，对象还是会释放，因此，weak_ptr的名字抓住了这种智能指针"弱“共享对象的特点
weak_ptr操作
weak_ptr<T> w 空weak_ptr可以指向类型为T的对象
weak_ptr<T> w(sp) 与shared_ptr sp指向相同对象的weak_ptr。T必须能转换为sp指向的类型
w=p  p可以是一个shared_ptr或一个weak_ptr。 赋值后w与p共享对象
w.reset()  将w置为空
w.use_count()   与w共享对象的shared_ptr 的数量
w.expired()  若w.use_count() 为0，返回true，否则返回false
w.lock()  如果expired为true，返回一个空shared_ptr;否则返回一个指向w的对象的shared_ptr
当我们创建一个weak_ptr时，要用一个shared_ptr来初始化它：
auto p = make_shared<int>(42);
weak_ptr<int> wp(p); //wp弱共享p；p的引用计数未改变
本立中wp和p指向相同的对象。由于是弱共享，创建wp不会改变p的引用计数；wp指向的对象可能被释放掉
由于对象可能不存在，我们不能使用weak_ptr直接访问对象，而必须调用lock。此函数检查weak_ptr指向的对象是否仍存在。如果存在，lock返回一个指向共享对象的shared_ptr。与任何其他shared_ptr类似，只要此shared_ptr存在，它所指向的底层对象也就会一直存在。
if(shared_ptr<int> np = wp.lock()){}
检查指针类
作为weak_ptr 用途的一个展示，我们将为StrBlob类定义一个伴随指针类。我们的指针类将命名为StrBlobPtr，会保存一个weak_ptr，指向StrBlob的data成员，这是初始化时提供给它的。通过使用weak_ptr，不会影响一个给定的StrBlob所指向的vector的生存期。但是，可以阻止用户访问一个不再存在的vector的企图
class StrBlobPtr{
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a, size_t sz = 0):wptr(a.data),curr(sz){}
    std::string& deref() const;
    StrBlobPtr& incr();//前缀递增
private:
    //若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>>wptr; //保存一个weak_ptr，
    std::size_t curr; //在数组的当前位置
};
值得注意的是，我们不能将StrBlobPtr绑定到一个const StrBlob对象。这个限制是由于构造接受一个非const StrBlob对象的引用而导致的。
StrBlobPtr的check成员与StrBlob中同名成员不同，它还要检查指针指向的vector是否还存在：
```cpp
std::shared_ptr<std::vector<std::string>>
StrblobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock(); //vector还存在吗？
    if(!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if(i>=ret->size())
        throw std::out_of_range(msg);
    return ret; //否则，返回指向vector的shared_ptr
}
```
由于一个weak_ptr 不参与其对应的shared_ptr的引用计数，StrBlobPtr指向的vector可能已经被释放了。如果vector已销毁，lock将返回一个空指针。
指针操作
定义名为deref和incr的函数，分别用来解引用和递增StrBlobPtr
deref成员调用check，检查使用vector是否安全以及curr是否合法范围内
```cpp
std::string& StrBlobPtr::deref() const
{
auto p = check(curr, "deference past end");
return (*p)[curr]; //(*p) 是对象所指向的vector
}
```
如果check成功，p就是一个shared_ptr，指向StrBlobPtr所指向的vector。表达式（*p）[curr]解引用shared_ptr，指向StrBlobPtr所指向的vector，然后使用下标运算符提取并返回curr位置上的元素
incr成员也调用check:
```cpp
//前缀递增：返回递增后的对象的引用
StrBlobPtr& StrBlobPtr::incr(){
    //如果curr已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr; // 推进当前位置
    return *this;
}
```
当然为了访问data成员，我们指针类必须声明为StrBlob的friend。我们还要为StrBlob类定义begin和end操作，返回一个指向它自身的StrBlobPtr：
对于StrBlob中的友元声明来说，此前置声明是必要的
```cpp
class StrBlob{
    friend class StrBlobPtr;
//返回指向首元素和尾后元素的StrBlobPtr
    StrBlobPtr begin() {return StrBlobPtr(*this);}
    StrBlobPtr end(){ auto ret = StrBlobPtr(*this, data-<size());  return ret;}
};
```
编写程序，逐行读入一个输入文件，将内容存入一个StrBlob中，用一个StrBlobPtr打印出StrBlob中的每个元素
```cpp
#include <iostream>
#include <fstream>
#include "strblob.h"

int main(){
    ifstream ifs("filepath");
    StrBlob sb;
    string s;
    while(getline(ifs,s)){
        sb.push_back(s);
    }
    for (StrBlobPtr sbp = sb.begin(); sbp != sb.end();sbp.incr()){
        cout << sbp.deref() <<endl;
    }
    return 0;
}

strblob.h
#ifndef EX12_19_H
#define EX12_19_H
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>
using namespace std;
class StrBlobPtr;
class StrBlob{
public:
    using size_type = vector<string>::size_type;
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();
    StrBlob():data(make_shared<vector<string>>()){}
    size_type size() const { return data->size();}
    bool empty() const { return data->empty();}

    void push_back(const string& s){ data -> push_back(s);}
    void pop_back(){ check(0,"pop_back on empty StrBlob"); data->pop_back();}
    string& front(){}
    string& back(){}
    const string& front() const{}
    const string& back() const{}
private:
    void check(size_type i, const string& msg) const{
                if(i >= data->size())
                         throw out_of_range(msg);
    };
class StrBlobPtr{
public:
     StrBlobPtr():curr(0){}
     StrBlobPtr(StrBlob &a,size_t sz = 0):wptr(a.data),curr(sz){}
     bool operator != (const StrBlobPtr& p){ return p.curr != curr;}
     string& deref() const{
               auto p = check(curr, "dereference past end");
               return (*p)[curr];
      }
      StrBlobPtr& incr(){
               check(curr,"increment past end of StrBlobPtr");
               ++curr;
               return *this;
      }
private:
     shared_ptr<vector<string>> check(size_t i, const string &msg) const{
       auto ret = wptr.lock();
       if(!ret) throw runtime_error("unbound StrBlobPtr");
       if(i>=ret->size()) throw out_of_range(msg);
       return ret;
       }
      weak_ptr<vector<string>> wptr;
      size_t curr;
};
StrBlobPtr StrBlob::begin(){
      return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end(){
     return StrBlobPtr(*this,data->size());
}
#endif
```
﻿动态数组
﻿new 和 delete 运算符一次分配/释放一个对象，但某些应用需要一次为很多对象分配内存的功能。例如vector和string 都是在连续内存中保存它们的元素，因此，当容器需要重新分配内存时，必须一次性为很多元素分配内存。
为了支持这种需求，C++语言和标准库提供了两种一次分配一个对象数组的方法。C++语言定义了另一种new表达式的语法，可以分配并初始化一个对象数组。标准库中包含一个名为allocator的类，允许我们将分配和初始化分离。使用allocator通常会提供更好的性能和更灵活的内存管理能力。
@大多数应用应该使用标准库容器而不是动态分配的数组。使用容器更为简单、更不容易出现内存管理错误，并且可能有更好的性能。
如前所述，使用容器的类可以使用默认版本的拷贝、赋值和析构操作。分配动态数组的类则必须定义自己版本的操作，在拷贝、复制以及销毁对象时管理所关联的内存

new和数组
为了让new分配一个对象数组，我们要在类型名之后跟一对方括号，在其中指明要分配的对象的数目。
new分配要求数量的对象并（假定分配成功后）返回指向第一个对象的指针：
    int *pia = new int[get_size()]; // pia 指向第一个int
@方括号中的大小必须是整型，但不必是常量
用一个表示数组类型的类型别名来分配一个数组，这样new表达式就不需要方括号
typedef int arrT[42]; // arrT 表示42个int的数组类型
int *p = new arrT; // 分配一个42个int的数组；p指向第一个int  编译器执行：int *p = new int[42];
分配一个数组会得到一个元素类型的指针
虽然我们通常称new T[] 分配的内存为“动态数组”，但这种叫法某种程度上有些误导。当用new分配一个数组时，我们并未得到一个数组类型的对象，而是得到一个元素类型的指针。即使我们使用类型别名定义一个数组类型，new 也不会分配一个数组元素类型的对象。new返回的是一个元素类型的指针
由于分配的内存并不是一个数组类型，因此不能对动态数组调用begin或end。这些函数使用数组维度来返回指向首元素和尾后元素的指针。出于相同的原因，也不能用范围for语句来处理（所谓的） 动态数组中的元素
⚠️ 要记住我们所说的动态数组并不是数组类型，而是元素指针类型！
初始化动态分配对象的数组
默认情况下，new分配的对象不管是单个分配的还是数组中的，都是默认初始化的。可以对数组中的元素进行值初始化，方法是大小之后跟一对空括号。
int *pia = new int[10]; //10个为初始化的int
int *pia2 = new int[10](); //10个值初始化为0的int
string *psa = new string[10]; //10个空string
string *psa2 = new string[10](); //10个空string
在新标准中，我们还可以提供一个元素初始化器的花括号列表
//10个int分别用列表中对应的初始化器初始化
int *pia3 = new int[10]{1,2,3,4,5,6,7,8,9,0};
string *pia3 = new string[10]{"a","an","the",string(3,'x')};
//10个string，前四个用给定的初始化器初始化，剩余的进行值初始化string s4(n,'c') // s4初始化为由连续n个字符c组成的串（直接）
如果初始化器数目大于元素数目，则new表达式失败，不会分配任何内存。在本例中⚠️，new会抛出一个类型为bad_array_new_length的
异常。类似bad_alloc，此类型定义在头文件new中。
虽然我们用空括号对数组中元素进行值初始化，但不能在括号中给出初始化器，这意味着不能用auto分配数组
动态分配一个空数组是合法的
可以用任意表达式来确定要分配的对象的数目：
size_t n = get_size(); //get_size返回需要的元素的数目
int* p = new int[n]; //分配数组保存的元素
for(int *q = p; q != p+n; ++q)

❓char arr[0]; //错误：不能定义长度为0的数组（静态数组）
char *cp = new char[0] //正确：但cp不能解引用

当我们用new分配一个大小为0的数组时，new返回一个合法的非空指针。此指针保证与new返回的其他任何指针都不相同。对与零长度的数组来说，此指针就像尾后指针一样，我们可以像使用尾后迭代器一样使用这个指针。可以用此指针进行比较操作，就像上面循环代码中的那样。
释放动态数组
delete p ; //p必须指向一个动态分配的对象或为空
delete [] pa; //pa必须指向一个动态分配的数组或为空
第二条语句销毁pa指向的数组中的元素，并释放对应的内存。数组中的元素按逆序销毁，即最后一个元素首先被销毁，然后是倒数第二个，以此类推。
智能指针和动态数组
标准库提供了一个可以管理new分配的数组的unique_ptr版本。为了用一个unique_ptr管理动态数组，我们必须在对象类型后面跟一对空括号：
uniqur_ptr<int[]> up(new int[10]); //up指向一个包含10个为初始化int的数组
up.release(); //自动用delete[]销毁其指针
类型说明符中的方括号（<int[]>)指出up指向一个int数组而不是一个int。由于up指向一个数组，当up销毁他管理的指针时，会自动使用delete[]
指向数组的unique_ptr提供的操作，不能使用点和箭头成员运算符。毕竟unique_ptr指向的是一个数组而不是单个对象，因此这些运算符是无意义的。另一方面，当一个unique_ptr指向一个数组时，我们可以使用下标运算符来访问数组中的元素：
for(size_t i = 0; i != 10; ++i)
    up[i] = i; //为每个元素赋予一个新值
指向数组的unique_ptr
unique_ptr<T[]> u u可以指向一个动态分配的数组，数组元素类型为T
unique_ptr<T[]> u(p) u指向内置指针p所指向的动态分配的数组。p必须能转换为类型T*
u[i]  返回u拥有的数组中位置i处的对象
u必须指向一个数组
与unique_ptr 不同，shared_ptr不直接支持管理动态数组。如果希望使用shared_ptr管理一个动态数组，必须提供自己定义的删除器
shared_ptr<int> sp(new int[10],[](int *p){delete[] p;}); //必须提供一个删除器
sp.reset(); //使用我们提供的lambda释放数组，它使用delete[]
如果未提供删除器，这段代码将是为定义的。默认情况下，shared_ptr 使用delete销毁它指向的对象。如果此对象是一个动态数组，对其使用delete所产生的问题与释放一个动态数组指针时忘记[]产生的问题一样。
shared_ptr不直接支持动态数组管理这一特性会影响我们如何访问数组中的元素
//shared_ptr 未定义下标运算符，并且不支持指针的算术运算
for(size_t i = 0; i != 10; ++i)
    *(sp,get*() + i) = i; //使用get获取一个内置指针
shared_ptr 未定下标运算符，而且智能指针类型不支持指针算术运算。因此，为了访问数组中的元素，必须用get获取一个内置指针，然后用它来访问数组元素
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <memory>

int main(){
    const char *c1 = "hello";
    const char *c2 = "world";
    unsigned len = strlen(c1)+strlen(c2)+1;
    char *r = new char[len]();
    strcat_s(r,len,c1); 
    strcat_s(r,len,c2);
    
    string s1 = "hello";
    string s2 = "world";
    strcpy_s(r.len,(s1+s2).c_str());
    delete[] r;
    return 0;
}
//example 12.24
int main(){
    cout<<"long?";
    int size{0};
    cin>>size;
    char *input = new char[size+1]();
    cin.ignore();
    cout<<"input the string";
    cin.get(input,size+1);
    cout<<input;
    delete[] input;
    return 0;
}
```
allocator类
new有一些灵活性上的局限，其中一方面表现在它将内存分配和对象构造组合在了一起。类似的，delete将对象析构和内存释放组合了在一起。我们分配单个对象时，通常希望将内存分配和对象初始化组合在一起。因为在这种情况下，我们几乎肯定知道对象应有什么值。
当分配一大块内存时，我们通常计划在这块内存按需构造对象。在此情况下，我们希望将内存分配和对象构造分离。这意味着我们可以分配大块内存，但只在真正需要时才真正执行对象创建操作（同时付出一定的开销）

allocator类
标准库allocator类定义在头文件memory中，它帮助我们将内存分配和对象构造分离开来。它提供一种类型感知的内存分配方法，它分配的内存是原始的、未构造的。它是一个模版。为了定义一个allocator对象，我们必须指明这个allocator 可以分配的对象类型。当一个allocator对象分配内存时，它会根据给定的对象类型来确定恰当的内存大小和对齐位置：
allocator<string> alloc; //可以分配string的allocator对象
auto const p = alloc.allocate(n);  //分配n个未初始化的string
这个allocate调用为n个string分配了内存
allocator<T> a  定义了一个名为a的allocator对象，他可以为类型为T的对象分配内存
a.allocator(n)  分配一段原始的，未构造的内存，保存n个类型为T的对象
a.deallocate(p,n) 释放从T*指针p中的地址开始的内存，这块内存保存了n个类型为T的对象；p必须是一个先前由allocate返回的指针，且n必须是p穿件时所要求的大小。在调用deallocatr之前，用户必须对每个在这块内存中创建的对象调用destory
a.construct(p,args) p必须是一个类型为T*的指针，指向一块原始内存：arg被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
a.destory(p)  p为T* 类型的指针，此算法对p指向的对象执行析构函数
allocator分配未构造的内存

allocator分配的内存是未构造的。我们按需要在此内存中构造对象。在新标准库中，construct成员函数接受一个指针和零个或多个额外参数，在给定位置构造一个元素。额外参数用来初始化构造的对象。类似make_shared的擦背上个月，这些额外的参数必须与构造的对象的类型相匹配的合法的初始化器
auto q = p; //q指向最后构造的元素之后的位置
alloc.construct(q++); //*q未空字符串
alloc.construct(q++,10,'c'); //*q 为cccccccccc
alloc.construct(q++,"hi"); // *q为hi
⚠️为了使用allocate返回的内存，我们必须用construct构造对象。使用未构造的内存，其行为是为定义的
当我们使用完对象后，必须对每个构造的元素调用destory来销毁它们。函数destory接受一个指针，对指向的对象执行析构函数
while(q!=p)
    alloc.destory(--p); //释放我们真正构造的string
⚠️我们只能对真正构造了的元素进行destory操作
释放内存通过调用deallocate来完成
alloc.deallocate(p,n);
拷贝和填充未初始化内存的算法
伴随算法，定义在头文件memory中
这些函数在给定目的位置创建元素，而不是由系统分配内存给它们
uninitialized_copy(b,e,b2) //从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的未构造的原始内存中。b2指向的内存必须足够大，能容纳输入序列中元素的拷贝
uninitialized_copy_n(b,n,b2) 从迭代器b指向的元素开始，拷贝n个元素到b2开始的内存中。
uninitialized_fill(b,e,t) 在迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝
uninitialized_fill_n(b,n,t) 从迭代器b指向的内存地址开始创建n个对象。b必须指向足够大的未构造的原始内存，能够容纳给定数量的对象

auto p = alloc.allocate(vi.size()*2); //分配比vi中元素所占用空间大一倍的动态内存
auto q = uninitialized_copy(vi.begin(),vi.end(),p); //通过拷贝vi中的元素类构造从p开始的元素
uninitialized_fill_n(q,vi.size(),42); // 将剩余元素初始化为42
﻿文本查询程序


fileQuery.cpp
1.8 KB
