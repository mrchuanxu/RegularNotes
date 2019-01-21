#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/***
 * 如何返回一个lambda表达式
 * ？
 * ***/

void biggies(vector<string> &words,vector<string>::size_type sz = 0,ostream &os = cout,char c = ','){
    for_each(words.begin(),words.end(),[&os,c](const string &s){os << s << c;});
}
int main(void){
    auto f = []{return 42;};
    cout << f() << endl;
    vector<string> words{"i","dont","like","you"};
    stable_sort(words.begin(),words.end(),[](const string& a,const string& b){return a.size()>b.size();});
    for(auto iter:words){
        cout << iter << endl;
    }
    // 带参数
    auto func = [](const string& a,const string &b){return b.size()>a.size();};
    if(func("s","no")) cout << "yes" << endl;
    // 使用捕获列表
    // 将输入序列中每个string的长度与biggies函数中的sz做比较
    int sz = 3;
    auto funcsz = [sz](const string &a){return a.size()>sz;};
    if(funcsz("nossss")) cout << "aha" << endl;
    // sz需要个定义
    // find_if寻找第一个长度大于等于sz的元素
   // auto wc = find_if(words.begin(),words.end(),[sz](const string& a){return a.size()>=sz;});
    biggies(words);
    // 值捕获
    size_t v1 = 42;
    auto f2 = [v1]{return v1;};
    auto wc = find_if(words.begin(),words.end(),[=](const string& a){return a.size()>=sz;});
    cout << *wc << endl; // return a iterator
    // 混合使用隐式捕获喝显式捕获
    auto f3 = [](int i){if(i<0) return -i;else return i;};
    cout << f2() << endl;
    return 0;
}

