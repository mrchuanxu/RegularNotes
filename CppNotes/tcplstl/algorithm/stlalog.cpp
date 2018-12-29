/***
 * 谓词是一个高级用法
 * 掌握谓词
 * 在stl算法中很有帮助
 * 举个具体的例子
 * 
 * mismatch() 查找两个序列中第一对不匹配的元素，返回指向这两个元素的迭代器。重点是两个序列
 * 
 * ***/
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> vnum = {1,2,3,4,5,6,7,7,8,9};
    for_each(vnum.begin(),vnum.end(),[](int &x){++x;});
    for(auto iter = vnum.begin();iter!=vnum.end();++iter){
        cout << *iter << endl;
    }
    assert(all_of(vnum.begin(),vnum.end(),[](double x){return 0<x;}));
    for(auto iter = vnum.begin();iter!=vnum.end();++iter){
        cout << *iter << endl;
    }
    // 以上就是谓词所指的🌰 

    return 0;
}