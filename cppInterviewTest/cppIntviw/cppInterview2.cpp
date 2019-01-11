#include <iostream>
using namespace std;

const char* err_message(const int i){
    return "range_error";
} // 常量 静态分配的 很安全 存放range_error的内存区域不会消失

constexpr int isqrt_helper(int sq,int d,int a){
    return sq <= a?isqrt_helper(sq+d,d+2,a):d;
}

constexpr int isqrt(int x){
    return isqrt_helper(1,3,x)/2-1;
}

// 字面值常量类型
struct Point{
    int x,y,z;
    constexpr Point up(int d){ // 这是一个函数
        return {x,y,z+d};
    }
    constexpr Point move(int dx,int dy){
        return {x+dx,y+dy};
    }
};
// 含有constexpr构造函数的类称为字面值常量类型，构造函数必须足够简单才能声明成constexpr
int main(){
    cout << sizeof("hi,bro") << endl;
   // char *p = "ppp"; // 老代码编译不过
    // p[1] = 'e';
    char pp[] = "ppp";
    pp[0] = 'r';
    const char *ctr = "headline";
    const char *cctr = "headline"; // 指向的是同一个地址
    if(ctr==cctr){
    cout << "one\a\n" << endl;
    }
    char ap[] = "abdnsls"
    "ADADDADADD";
    cout << ap << endl;
    // 值不发生改变
    const int v[] = {1,2,3,4};
    cout << v[1] << endl;
    const char ctrc = 'c';
    char const* pc = &ctrc;
    const char *pcc = &ctrc;
    int x1 = 7;
    constexpr int x2 = 3;
    constexpr int x3 = x2;

    constexpr int s1 = isqrt(9);
    constexpr int s2 = isqrt(234); 
    const int x = 7;
    const string s = "abcs";
    constexpr int xx = x;
    constexpr string ss = s;
    constexpr Point origo{0,0,1};
    // constexpr int z = origo.x;
    // cout << z << endl;

    // constexpr Point a[]{
    //     origo,Point{1,1},Point{2,2},origo.move(3,3)
    // };
    constexpr const char *p1 = "asdf";
    constexpr const char *p2 = p1;
    //constexpr const char *p2 = p1+2; // 编译器不知道这类地址的常量值是多少
    constexpr char c = p1[2];
    return 0;

}
