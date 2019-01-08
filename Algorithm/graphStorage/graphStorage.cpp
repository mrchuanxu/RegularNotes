#include <iostream>
#include <set>
#include <map>
using namespace std;


/***
 * 这是一个图
 * 图有两种存储方式
 * 一种是邻接矩阵
 * 一种是邻接表
 * 两种不同的存储方式
 * 邻接矩阵比较损耗空间，但是查询的速度比较快
 * 邻接表就是将空间缩小，但是查询的速度比较慢，可以改进，使用二叉查找树或者平衡二叉树或者跳表改变O(logn)
 * 所以
 * 这里的实现是使用邻接表实现
 * 
 * ***/

template<typename T>
class graphStorage{
    public:
        graphStorage(){
        }
        void addEdge(T &start,T &end){ // 无向图，一条边存两次
            graphs[start].insert(end);
            graphs[end].insert(start);
        }
    private:
        int _n; // n个顶点
        map<T,multiset<T,greater<T> > > graphs;// 这样就生成一个图的邻接表
};

int main(){
    char *ch = new char[100];
    delete []ch;
    graphStorage<int> gs;
    int start = 1;
    int end = 2;
    gs.addEdge(start,end);
    return 0;
}