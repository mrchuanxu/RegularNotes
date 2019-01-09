#include <iostream>
#include <set>
#include <map>
#include <queue>
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
 * 实现广度优先遍历
 * 使用队列结合
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
        map<T,multiset<T,greater<T> > >& getGraphs(){
            return graphs;
        }
        void print(map<T,T*>& mapPrev,T& s,T& t);
        void bfs(T& s,T& t);// 广度优先搜索 三个存储记录 最后递归遍历获得最短路径
    private:
        map<T,multiset<T,greater<T> > > graphs;// 这样就生成一个图的邻接表
};
template<typename T>
void graphStorage<T>::bfs(T &s,T &t){
    if(s==t)
        return;
    // 首先记录visited
    map<T,bool> mapViseted;
    map<T,T*> mapPrev; // 记录查询过的节点 并将所有的节点的首个指针指向nullptr
    typename std::map<T,multiset<T,greater<T> > >::iterator mapiter; // 编译器不知道这个是一个类型，可以将此类型名加上！
    for(mapiter = graphs.begin();mapiter!=graphs.end();++mapiter){
        mapPrev[mapiter->first] = nullptr;
        mapViseted[mapiter->first] = false;
    }
    queue<T> qVelem;
    qVelem.push(s);
    mapViseted[s] = true;
    while(qVelem.size()!=0){
        T& w = qVelem.front();
        qVelem.pop();
        typename multiset<T,greater<T> >::iterator setIter;
        for(setIter=graphs[w].begin();setIter!=graphs[w].end();++setIter){
            T q = *setIter;
            if(!mapViseted[q]){// 如果未遍历，就将元素放入prev
                mapPrev[q] = &w; // 存储第一次遍历的节点
                if(q == t){
                    print(mapPrev,s,t);
                    return;
                }
                mapViseted[q] = true; // 将已经遍历的结果继续赋值为true
                qVelem.push(q); // 将队列元素加上
            }
        }
    }
}
template<typename T>
void graphStorage<T>::print(map<T,T*>& mapPrev,T& s,T& t){
    if(mapPrev[t]!=nullptr&&s!=t){
        print(mapPrev,s,*(mapPrev[t])); // 递归遍历
    }
    cout << t << endl;
}

int main(){
    graphStorage<char> gs;
    char arr[] = {'a','b','c','d','e','f','g','h','i','j'};
    gs.addEdge(arr[0],arr[1]);
    gs.addEdge(arr[0],arr[4]);
    gs.addEdge(arr[1],arr[5]);
    gs.addEdge(arr[1],arr[2]);
    gs.addEdge(arr[2],arr[6]);
    gs.addEdge(arr[2],arr[3]);
    gs.addEdge(arr[3],arr[7]);
    gs.addEdge(arr[6],arr[8]);
    gs.addEdge(arr[7],arr[9]);
    gs.bfs(arr[0],arr[9]);
    //map<int,multiset<int,greater<int> > > mgraphs = gs.getGraphs();
    // auto iternum = mgraphs[1].find(2);
    // cout << *iternum << endl;
    // for(auto iter = mgraphs[2].begin();iter!=mgraphs[2].end();++iter){
    //     cout << *iter << endl;
    // }
    return 0;
}