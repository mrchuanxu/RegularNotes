
#include <iostream>
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

int main(){
    cout << jd2.state[0] << endl;
    cout << sizeof(Readout) << endl;
    return 0;
}