#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <functional>
using namespace std;
using namespace std::placeholders;

/***
 * lambda表达式
 * [capture list](parameter list)->return type{function body;}
 * 参数绑定
 * 标准bind函数
 * 形式 auto newCallable = bind(callable,arg_list);
 * newCallable 本身是一个可调用对象，arg_list是一个逗号分隔的参数列表，对应的callable的参数
 * 占位符_n 表示newCallable的参数，它们占据了传递newCallable的参数的位置。
 * ***/
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}




int main(){
    //vector<string> words;
    // sort(words.begin(),words.end(),isShorter);
    // 传递一个参数
    //sort(words.begin(),words.end(),[](const string &a,const string &b){return a.size()<b.size();});
    auto f = []{return 42;};
    cout<< f() << endl;
    int sz = 10;
    auto func = [sz](const string &a){return a.size()>sz;}; // 值捕获 也有&sz捕获 引用捕获
    cout << func("iamnot") << endl;
    ostream &os = cout;
    auto func_os = [&os,sz](const string &a){ os << a << sz;};
    func_os("mrtrans");
    // 定义返回类型 使用尾置返回
    auto func_ret = [](int i)->int{return i>0?1:-1;};
    cout << func_ret(10)<<endl;

    auto shis = bind(isShorter,_2,_1);
    cout << shis("yes","no")<<endl;

}