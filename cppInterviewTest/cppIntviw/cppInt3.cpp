#include <iostream>

using namespace std;

static int i = 6;
int inum = 42;

int func(){
    static int ifunc = 44;
    return ifunc++; 
}

int funcc(){
    int ifunc = 44;
    return ifunc++;
}
// static 成员
class Date{
    int d,m,y;
    static Date default_date;
    public:
        Date(int dd,int mm =0,int yy =0);
        static void set_default(int dd,int mm,int yy);
};
Date::Date(int dd,int mm,int yy){
    d=dd?dd:default_date.d;
    m=mm?mm:default_date.m;
    y=yy?yy:default_date.y;
}
Date Date::default_date{16,12,1770};

void Date::set_default(int dd,int mm,int yy){ // 定义中不用重复关键字static
    default_date = {dd,mm,yy};
}
// 一个static类成员是静态分配的，而不是每个类对象的一部分。一般来说，static成员声明充当类外定义的声明。
class Node{
    static int node_count;
};

int Node::node_count = 0;
// 但是在类内声明初始化static成员也是可能的，条件是static成员必须是整型或枚举类型的const或字面值类型的constexpr，且初始化器必须是一个常量表达式
class Curious{
    public:
        static const int c1 = 7;
        // static int c3 = 11; // ❌ 非const
        // 不是常量也不行
        static constexpr float c5 = 7.0; // 类内初始化成员不是整型，要用constexpr
};
// 唯一定义，不能再定义，不能重复初始化器
// 一个类外定义的static数据或函数成员在整个程序中只能唯一定义
// template中只有真正用到才会被编译器告知未定义
int main(){
   for(int i = 0;i<10;i++){
       cout <<"func:" << func() << endl;
       cout << "funcc:" <<funcc() << endl;
   }
    return 0;
}