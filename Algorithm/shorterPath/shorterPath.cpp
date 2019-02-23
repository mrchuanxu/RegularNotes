/***
 * 构建有权有向图
 * ***/

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <set>
// 会选择multiset做持续堆化 如果相同的路径就会只保留一个就好
using namespace std;

struct  Edge
{
    char s;
    char t;
    int w;
    Edge(char &ss,char &tt,int &ww):s(ss),t(tt),w(ww){}
};

struct Vertex{
    char id;
    int dist;
};

class GraphWeight{
    map<char,vector<shared_ptr<Edge> > > mapEdage;
    // 构建有权有向图
    public:
        void addEdage(char s,char t,int w){
            mapEdage[s].push_back(shared_ptr<Edge>(new Edge(s,t,w)));
            // 构建边表
        }
        // 其实Dijkstra是一个贪心策略，哪个路长度小，就往哪边走
        void dijkstra(char&,char&);
        // 搞一个可调用对象
        // bool compareVertex(const Vertex&,const Vertex&);
};

bool compareVertex(const Vertex* a,const Vertex* b){
    return a->dist<b->dist;
}// 可调用对象作为判断实例

bool (*fn_compVex)(const Vertex*,const Vertex*) = compareVertex;
void GraphWeight::dijkstra(char& s,char& t){
    map<char,char> mpredecessor; // 用于还原最短路径，不断更新
    map<char,shared_ptr<Vertex> > mapVextes;
    multiset<shared_ptr<Vertex>,bool(*)(const Vertex*,const Vertex*)> prioque(fn_compVex);
    // 获取最小的路径长度 小顶堆
    map<char,bool> is_queue; // 判断是否进入了队列
    mapVextes[s]->dist = 0;
    prioque.insert(mapVextes[s]);
    // FIXME:
}

