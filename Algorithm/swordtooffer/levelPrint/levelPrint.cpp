#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/***
 * 层序遍历二叉树
 * 放入queue
 * 逐个打印出来
 * 放的是节点
 * 要对节点进行判断
 * 
 * ***/
template<typename T>
struct BinaryNode{
    T val;
    BinaryNode *pLeft;
    BinaryNode *pRight;
};

/***
 * 前序遍历构造一棵树
 * 8,6,5,0,0,7,0,0,10,9,0,0,11,0,0
 * ***/
BinaryNode<int>* PreOrderBuild(int *arr,int len){
    BinaryNode<int>* np;
    static int Len = len;
    if(arr[Len] == 0){
        np = nullptr;
    }else{
        np = new BinaryNode<int>();
        np->val = arr[Len];
        np->pLeft = PreOrderBuild(arr,--Len);
        np->pRight = PreOrderBuild(arr,--Len);
    }
    return np;
}
/**
 * 按左右打印
 * ***/
void levalPrint(BinaryNode<int> *p){
   // 来一个队列
   if(p==nullptr)
       return;
   queue<BinaryNode<int>*> qNode;
   qNode.push(p);
   while(qNode.size()){
       BinaryNode<int>* qn = qNode.front();
       qNode.pop();
       cout << qn->val<<',';
       if(qn->pLeft!=nullptr){
           qNode.push(qn->pLeft);
       }
       if(qn->pRight!=nullptr){
           qNode.push(qn->pRight);
       }
   }
   cout << endl;
}
/***
 * 8
 * 6,10
 * 5,7,9,11
 * 按层序遍历打印
 * ***/
void levelPrintByLine(BinaryNode<int> *p){
    if(p==nullptr)
        return;
    queue<BinaryNode<int>*> qNode;
    qNode.push(p);
    int levelNodes = 0;
    int toBePrint = 1;
    while(qNode.size()){
        BinaryNode<int> *qn = qNode.front();
        qNode.pop();
        cout << qn->val<<',';
        if(qn->pLeft!=nullptr){
            qNode.push(qn->pLeft);
            ++levelNodes;
        }
        if(qn->pRight!=nullptr){
            qNode.push(qn->pRight);
            ++levelNodes;
        }
        --toBePrint;
        if(toBePrint==0){
            toBePrint = levelNodes;
            levelNodes=0;
            cout << endl;
        }
    }
}

void preOrder(BinaryNode<int> *p){
    if(p==nullptr)
        return;
    cout << p->val << endl;
    preOrder(p->pLeft);
    preOrder(p->pRight);

}

/***
 * 按之字型打印
 * 也就是两个栈
 * 分别打印
 * 打印完又插入
 * ***/
void zPrint(BinaryNode<int> *p){
    if(p==nullptr)
        return;
    stack<BinaryNode<int>*> stNode[2];
    int current = 0;
    int next = 1;
    stNode[current].push(p);
    while(!stNode[0].empty()||!stNode[1].empty()){
        BinaryNode<int> *nst = stNode[current].top();
        stNode[current].pop();
        cout << nst->val << ',';
        if(current==0){
            if(nst->pLeft!=nullptr){
                stNode[next].push(nst->pLeft);
            } 
            if(nst->pRight!=nullptr){
                stNode[next].push(nst->pRight);
            }
        }else{
            if(nst->pRight!=nullptr){
                stNode[next].push(nst->pRight);
            }
            if(nst->pLeft!=nullptr){
                stNode[next].push(nst->pLeft);
            } 
        }
        if(stNode[current].empty()){
            current = 1-current;
            next = 1-next;
            cout << endl;
        }
    }
}

int main(){
    int arr[]={0,0,11,0,0,9,10,0,0,7,0,0,5,6,8};
    BinaryNode<int> *p = new BinaryNode<int>();
    p = PreOrderBuild(arr,14);
    preOrder(p);
    levalPrint(p);
    levelPrintByLine(p);
    zPrint(p);
    return 0;
}