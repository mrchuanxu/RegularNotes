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
        void dfs(T& s,T& t);
    private:
        map<T,multiset<T,greater<T> > > graphs;// 这样就生成一个图的邻接表
        void recurDfs(T &s,T &t,map<T,T*>& mapPrev,map<T,bool>& isVisited); // 递归需要什么呢？递归深度遍历其实使用的是栈的思想 同样是对邻接表的深入 
        bool found = false;
};
template<typename T>
void graphStorage<T>::bfs(T &s,T &t){
    if(t==s) return;
    // 首先我先定义几个存储，用作迭代的思想
    // 因为是template 所以我用到了map
    map<T,bool> isVisited;
    map<T,T*> mapPrev; // 存储反向节点
    // 先把元素确定一下 false和nullptr
    typename std::map<T,multiset<T,greater<T> > >::iterator gIter;
    for(gIter = graphs.begin();gIter!=graphs.end();++gIter){
        isVisited[gIter->first] = false;
        mapPrev[gIter->first] = nullptr;
    }
    queue<T> mapQue; // 存储邻接表的节点元素 遵循一个原则，用到你才去声明
    mapQue.push(s);
    isVisited[s] = true;// 首先确定一个元素
    while(mapQue.size()!=0){
        T &w = mapQue.front();
        mapQue.pop(); // pop要说明一下，这是返回void，也就是说不能返回任何值，用的时候要注意一下
        // 由于需要遍历这个节点，所以需要进行iterator声明
        typename std::multiset<T,greater<T> >::iterator msIter;
        for(msIter = graphs[w].begin();msIter!=graphs[w].end();++msIter){
            T q = *msIter;
            if(!isVisited[q]){
                mapPrev[q] = &w; // 这里指向的反向的节点，而且每次都只是只存一个遍历的节点
                    if(q==t){
                        print(mapPrev,s,t);
                        return;
                    }
                mapQue.push(q);
                isVisited[q] = true;
            }
        }
    }
}
template<typename T>
void graphStorage<T>::print(map<T,T*>& mapPrev,T& s,T& t){
    if(mapPrev[t]!=nullptr&&s!=t){
        print(mapPrev,s,*(mapPrev[t]));
    }
    cout << t << endl;
}

template<typename T>
void graphStorage<T>::dfs(T &s,T &t){
    // 其实就是走过的就不走了，没走过的继续走
    if(found == true) return;
    found = false;
    // 也要一个visited
    map<T,bool> isVisited;
    map<T,T*> mapPrev;
    typename std::map<T,multiset<T,greater<T> > >::iterator gIter;
    for(gIter = graphs.begin();gIter!=graphs.end();++gIter){
        isVisited[gIter->first] = false;
        mapPrev[gIter->first] = nullptr;
    }
    recurDfs(s,t,mapPrev,isVisited);
    print(mapPrev,s,t);
}

template<typename T>
void graphStorage<T>::recurDfs(T &s,T &t,map<T,T*>& mapPrev,map<T,bool>& isVisited){
    if(found == true) return;
    isVisited[s] = true; // 没找到就将visited访问给补上
    if(s==t){
        found = true;
        return;
    }
    typename std::multiset<T,greater<T> >::iterator msIter;
    for(msIter = graphs[s].begin();msIter!=graphs[s].end();++msIter){ // 是递归，所以map的值依循传进来的s
        if(found == true) return;
        T q = *msIter;
        if(!isVisited[q]){ // 未访问到就去访问 访问过就不访问，没访问过就继续访问
            mapPrev[q] = &s;
            recurDfs(q,t,mapPrev,isVisited); // 主要是找没找到没找到继续找，找到就不找了
        }
    }
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