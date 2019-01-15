/***
 * 图的遍历
 * 图的遍历需要设计一个存储结构
 * 这里设计的存储结构用的是平衡二叉树
 * 一种平衡的二叉树容器 multiset<>
 * 实现查询和插入的时间复杂度会是o(logn)
 * 采用的邻接表的方式
 * 
 * 紧接着采用的是广度优先搜索产生最短路径
 * 
 * 接下来是深度搜索优先
 * ***/

#include <map>
#include <set>
#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class GraphOperator
{
    // 存储图结构 根据值获取相应的链表
    map<T, multiset<T, greater<T> > > mGraph;
    // 这里使用vector<shared_ptr<Node>> edges //会解决释放内存资源的问题  
    void recurDfs(T &s,T &t,map<T,T*>&,map<T,bool>&);
    bool found = false;
  public: // 为外部提供接口
    GraphOperator()
    {
    }
    // 存储数据 采用无向图插入数据 两边都要插一遍
    void graphBuild(T &key, T &value)
    {
        mGraph[key].insert(value);
        mGraph[value].insert(key);
    }
    // 广度优先图的遍历 寻找s到t的最短路径
    void bfsGraph(T &s, T &t);
    void dfsGraph(T &s,T&t);
    void print(map<T,T*>& mprev,T &s,T &t);
};

template <typename T>
void GraphOperator<T>::bfsGraph(T &s, T &t)
{
    if (t == s)
        return;
    // 需要三个存储空间 一个是已访问visited 一个是队列 一个是存储最短路径的反向路径的元素数组
    map<T, bool> mapVisited;
    map<T, T*> mapPrev;
    typename std::map<T, multiset<T, greater<T> > >::iterator gIter;
    // 需要将mapPrev对应的值打上nullptr
    for (gIter = mGraph.begin(); gIter != mGraph.end(); ++gIter)
    {
        mapPrev[gIter->first] = nullptr;
        mapVisited[gIter->first] = false;
    }
    queue<T> qVelem;
    qVelem.push(s);
    mapVisited[s] = true;
    while (qVelem.size() != 0)
    {
        T &w = qVelem.front(); // 最外面的路径值
        qVelem.pop();
        // 现在需要遍历map[w]下的所有的后面的链表节点元素，然后放进prev和q
        typename std::multiset<T, greater<T> >::iterator msIter;
        for (msIter = mGraph[w].begin();msIter!=mGraph[w].end();++msIter)
        {
            // 然后判断这个msIter是否被访问过
            T q = *msIter;
            if(!mapVisited[q]){
                // 没有被访问
                mapPrev[q] = &w; // 放入mapPrev
                if(q == t){
                    print(mapPrev,s,t);
                    return;
                }
                mapVisited[q] = true;
                qVelem.push(q);
            }
        }
    }
}

template <typename T>
void GraphOperator<T>::print(map<T,T*> &mPrev,T &s,T &t){
    if(mPrev[t]!=nullptr&&s!=t){
        print(mPrev,s,*(mPrev[t]));
    }
    cout << t << endl;
}

template<typename T>
void GraphOperator<T>::dfsGraph(T &s,T &t){
    if(s==t)
        return;
    // 要有visited
    map<T,bool> mapVisited;
    // 要有存的mprev
    map<T,T*> mapPrev; // 指针是一个比较难受的做法，这里面的s要是在作用域失效，就会使得整个作用s都的地址都失效 只要赋值就可以解决
    // 给mapPrev添加nullptr
    typename std::map<T, multiset<T, greater<T> > >::iterator gIter;
    for(gIter=mGraph.begin();gIter!=mGraph.end();++gIter){
        mapVisited[gIter->first] = false;
        mapPrev[gIter->first] = nullptr;
        cout << gIter->first << endl;
    }
    // 其实就是压栈
    recurDfs(s,t,mapPrev,mapVisited); // 这里遇到一个递归，突然清空的问题 想想怎么处理这个清空的事情 FIXME:
    // typename map<T,T*>::iterator mpIter;
    // mpIter = mapPrev.begin();
    // while(mpIter!=mapPrev.end()){
    //     cout << *(mpIter->second) << endl;
    // }
    print(mapPrev,s,t);
}

template<typename T>
void GraphOperator<T>::recurDfs(T &s,T &t,map<T,T*>& mPrev,map<T,bool>& mVisited){
    if(found == true) return;
    mVisited[s] = true;
    if(s==t){
        found = true;
        return;
    }
    // 遍历这个s后面的节点
    typename std::multiset<T,greater<T> >::iterator msIter;
    for(msIter = mGraph[s].begin();msIter!=mGraph[s].end();++msIter){
        if(found == true) return;
        T q = *msIter;
        if(!mVisited[q]){
            mPrev[q] = &s; // 将遍历的节点放回mPrev
            // cout << "kkk:"<< q <<s << endl;
            recurDfs(q,t,mPrev,mVisited);
        }
    }
}

int main(){
    GraphOperator<char> gs;
    char arr[] = {'a','b','c','d','e','f','g','h','i','j'};
    gs.graphBuild(arr[0],arr[1]);
    gs.graphBuild(arr[0],arr[4]);
    gs.graphBuild(arr[1],arr[5]);
    gs.graphBuild(arr[1],arr[2]);
    gs.graphBuild(arr[2],arr[6]);
    gs.graphBuild(arr[2],arr[3]);
    gs.graphBuild(arr[3],arr[7]);
    gs.graphBuild(arr[6],arr[8]);
    gs.graphBuild(arr[7],arr[9]);
    //gs.bfsGraph(arr[0],arr[9]);
    gs.dfsGraph(arr[0],arr[9]);
    //map<int,multiset<int,greater<int> > > mgraphs = gs.getGraphs();
    // auto iternum = mgraphs[1].find(2);
    // cout << *iternum << endl;
    // for(auto iter = mgraphs[2].begin();iter!=mgraphs[2].end();++iter){
    //     cout << *iter << endl;
    // }
    return 0;
}