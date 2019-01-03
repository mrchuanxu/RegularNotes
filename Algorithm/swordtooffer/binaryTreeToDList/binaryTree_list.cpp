#include <iostream>

using namespace std;

struct BinaryNode{
    int val;
    BinaryNode *p_Left;
    BinaryNode *p_Right;
};
// pLastNodelist 指向双向链表的尾节点
void ConvertNode(BinaryNode *pNode,BinaryNode **pLastNodelist){
    if(pNode==nullptr)
        return;
    BinaryNode *pCurrent = pNode; // 不能新建节点
    if(pNode->p_Left!=nullptr){
        ConvertNode(pNode->p_Left,pLastNodelist); // pLastNodelist只是为了存储前一个节点的
    }
    pCurrent->p_Left = *pLastNodelist; // 一直递归到叶子节点 然后将左节点指向前一个节点
    if(*pLastNodelist!=nullptr){
        (*pLastNodelist)->p_Right = pCurrent; // 将右节点继续指向后面的节点
    }
    *pLastNodelist = pCurrent; // 完成前面的操作，移位后一个节点

    if(pCurrent->p_Right!=nullptr){
        ConvertNode(pCurrent->p_Right,pLastNodelist); // 右边也是一样的操作
    }
}

BinaryNode* converResult(BinaryNode *pRoot){
    if(pRoot==nullptr)
        return nullptr;
    BinaryNode *pLastNodelist = nullptr;
    ConvertNode(pRoot,&pLastNodelist);
    BinaryNode *pHead = pLastNodelist;
    while(pHead!=nullptr&&pHead->p_Left!=nullptr){
        pHead = pHead->p_Left; // 回到头部
    }
    return pHead;
}