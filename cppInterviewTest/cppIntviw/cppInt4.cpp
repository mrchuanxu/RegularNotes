#include <iostream>

using namespace std;

int i = 42; // 全局变量
static char ctr = 'c'; // static静态存储区的全局变量
static int cc = 23;

int func(){
    static int ifunc = 44;
    cout << &ifunc << endl;
    return ifunc++; 
}

int funcc(){
    static int ifunc = 44;
    cout << &ifunc << endl;
    return ifunc++;
}
static int funcs(){
    int ifuncc = 42;
    return ifuncc;
}

class Node{
    public:
        int comium = 43;
        static int inum;
        static const int iinum = 90;
        static const char ci = 't';
};
int Node::inum = 45;

class Quote{
    public:
    int cfuncc(const int &t) const{
        int s = t;
        cout << s << endl;
        x = 34;
        return t;
    }
    private:
       mutable int x = 42;
};
class TestStatic{
    public:
        constexpr TestStatic(int _num = 4):num(_num){
            cout << num << endl;
        }
        static void set_default() const;
    private:
        //static int count;
        int num;
        static TestStatic teststat;
};
TestStatic TestStatic::teststat(1);
void TestStatic::set_default(){
    teststat = {2};
    cout << teststat.num << endl;
}

// int TestStatic::count = 42;
int main(){
    TestStatic testStat(9);
    testStat.set_default();
    constexpr int i = 9;
    cout << i << endl;
   return 0;
}