/***
 * 二维平面上有n个点
 * 如何快速计算出两个举例最近的点对
 * 
 * 有两个n*n的矩阵A，B，如何快速求解两个矩阵的乘积C=A*B
 * 
 * 分治思想
 * ***/

#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int> > vec_two_demin; // 构造点的存在

// 暴力法
// 首先进行组合 去掉重复 放入容器
// 进行组合中的计算
// 进行归并排序
// 取出第一个距离最短

int main(){
    vec_two_demin.push_back({1,2});
    cout<<vec_two_demin[0].first<<endl;
    return 0;
}
