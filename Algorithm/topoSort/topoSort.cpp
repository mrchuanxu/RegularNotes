/***
 * Topological Sorting
 * 拓扑排序: 如何确定代码源文件的编译依赖关系
 * 一个完整的项目往往会包含很多代码源文件
 * 编译器在编译整个项目的时候，需要按照依赖关系，依次编译每个源文件
 * 如A->B A依赖B，就先编译B，再编译A
 * Makefile需要了解一下
 * 
 * 编译器又该如何通过源文件两两之间的局部依赖关系，确定一个全局的编译顺序呢？
 * 
 * 局部依赖关系->全局依赖关系
 * 
 * 解决图的拓扑排序算法
 * 
 * 算法是构建在数据结构之上
 * 
 * 如何将这个问题构建成一个具体的数据结构呢？
 * 
 * 可以将源文件与源文件之间的依赖关系，抽象成一个有向图(有向无环图)
 * 每个源文件对应图中的一个顶点，源文件之间的依赖关系就是顶点之间的边
 * 
 * 关于拓扑排序，介绍一下图的遍历DFS与BFS 以及 贪心Kahn
 * 
 * kahn贪心策略: 
 * 1.找入度为0，表示没有任何顶点必须先于这个顶点执行，那么这个顶点就可以执行了
 * 2. 从图中找一个入度为0饿的顶点，输出到拓扑排序的结果序列中
 * 3. 把这个顶点删除
 * 4. 循环执行上述过程，直到所有顶点输出
 * 5. 最后输出的序列，就是满足局部依赖关系的拓扑排序
 * ***/

// 实现一个图的结构
#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class Topological{
    int v; // 顶点个数
    map<char,vector<char> > adjmap;
    public:
        Topological(int &vertex):v(vertex){}
        void addEdge(char s,char t){
            adjmap[s].push_back(t); // 只顾着往后插
        }
        void topoSortByKahn();
        void topoSortByDfs();
};

void Topological::topoSortByKahn(){
    // 统计入度的数
    map<char,int> mapInDegree;
    for(auto iter:adjmap){// 遍历map
        for(auto lstIter:adjmap[iter.first]){
            mapInDegree[lstIter]++; // 每个字符都统计
        }
    }
    queue<char> qInDegree;
    for(auto iter_indegre:mapInDegree){
        if(iter_indegre.second == 0) qInDegree.push(iter_indegre.first);
    }
    while(!qInDegree.empty()){ // 开始删除入度为0的顶点
        char res_vex = qInDegree.front();
        qInDegree.pop();
        cout << "->"<< res_vex<<endl;
        for(auto iter:adjmap[res_vex]){
            mapInDegree[iter]--; // 入度减1
            if(mapInDegree[iter]==0) qInDegree.push(iter);
        }
    }
}
/***
 * 若最后输出的顶点个数少于图中顶点个数
 * 可以用于检测环的存在
 * 存在环，就是找不到入度为0的顶点
 * ***/

/***
 * DFS算法
 * 1. 通过邻接表构造逆邻接表
 * 2. 递归处理每个顶点 对于顶点vertex来说，先输出可达的顶点，然后把它依赖的所有的顶点输出了，再输出自己
 * O(V+W)
 * 所以这就是为什么要构造逆邻接表
 * 随后操作的都是逆邻接表
 * 
 * 如果反过来实现？a->b a先于b执行，改成b->a 依赖关系b依赖a，那么
 * kahn算法就要修改，可以构造逆邻接表，然后操作逆邻接表
 * DFS可以直接使用邻接表
 * BFS广度优先可以么？
 * 可以的，图的遍历，但是需要改造一下
 * 找到优先执行的节点
 * ***/

