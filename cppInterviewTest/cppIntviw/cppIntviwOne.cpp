
#include <iostream>
#include <vector>
#include <array>
#include <assert.h>

using namespace std;

struct Address{
    const char* name;
    int number;
    char state[2];
    const char *street;
};
// 可以用点运算符获取每个成员，并且赋值
void f(){
    Address jd;
    jd.name = "Mr trans";
    jd.number = 34;
    jd.state[0] = 'N';
    jd.state[1] = 'J';
    jd.street = "baoan";
}

Address jd2 = {
    "trans",12,{'n','m'},"baoan"
};

struct Readout{
    int value;
    char hour;
    char seq;
};
// 一般来说，一个struct出现了就马上能用了！无须等到该类型声明全部完成
struct Link;
struct List{
    Link *pre;
    Link *suc;
    List *member_of;
    int data;
};

struct Link{
    Link *head;
};

struct Points{
    vector<int> elem;
    Points(int p0){elem.push_back(p0);}
    Points(int p0,int p1){elem.push_back(p0);}
};
struct Point{
    int x,y;
};

using Array = array<Point,3>;

Array points{1,2,3,4,5,6}; // 这里要注意一下，不同的编译器，需要的初始化应该不一样
// array有个明显的优势，首先它是一种真正的对象类型，可以执行赋值操作，其次他不会隐式地转换成指向元素的指针
Array shift(Array a,Point p){
    for(int i = 0;i!=a.size();++i){
        cout << "x:" <<a[i].x << "y:" << a[i].y << endl;
    }
    cout << a.size() << endl;

    return a;
}

// union 是一种特殊的struct，它的所有成员都分配在同一个地址空间上。因此，一个union实际占用的空间大小就与其最大的成员一样。
// 也就是说，当我控制type访问s和t的时候，要是永远都不同时访问，那么这两个值s和i就最好放在一个内存空间内，也就是这样
enum Type{str,num};
struct Entry{
    char *name;
    Type t;
    char *s;
    int i;
};
// 改成
union Value{
    char *s;int i;
};
struct Entry2{
    char *name;
    Type t;
    Value v; //  这样就不用浪费了空间
};

// 使用union就是为了让数据更加紧密，从而提高程序的性能
// union的尺寸与他最大成员一样大
// union是一种特殊的struct 而struct是一种特殊的class。
union U2{
    int a;
    const char *p;
};
struct Linka{
     int num;
     char c;
     char pctr[2];
};
union Linkb{
    int next;
    char a;
};

int main(){
   // Array ax =  shift(points,{1,2});
    // U2 x1;
    // U2 x2{7};
    // cout << x2.p << endl;
    // Linka la = {1,'p',{'k','o'}};
    cout << sizeof(Linkb) <<endl;
    int i = 42;
    Linkb lb;
    lb.next = 42;
    lb.a = 'p';
    cout << lb.a << endl;
    return 0;
}