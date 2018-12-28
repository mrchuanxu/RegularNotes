#include <iostream>
using namespace std;
/***
 * 二叉树
 * 链式存储与数组存储方式
 * 其中完全二叉树的存储 用数组存储方式存储会最节省空间
 * 完全二叉树的存储在数组中是以 2i左子树 2i+1右子树的方式
 * ***/

/***
 * 先来最简单的
 * 数组存储方式存储完全二叉树
 * 下标位置界定 2i与2i+1
 * ***/
// 给我一组数
struct BinaryTreeNode{
    int val;
    BinaryTreeNode *pLeft;
    BinaryTreeNode *pRight;
};

// 构建一棵二叉树 前序遍历构建 static保证len唯一
BinaryTreeNode* buildTree(int *arr,int len){
    static int Len = len;// 这里是正确的！ 这里如果通过压栈，就存在不唯一的情况，不停滴遍历新的len
    BinaryTreeNode *p;
    if(arr[Len]==0)
        p = nullptr;
    else{
        p = new BinaryTreeNode();
        p->val = arr[Len];
        p->pLeft = buildTree(arr,--Len);
        p->pRight = buildTree(arr,--Len); 
    }
    return p;
}

void preOrder(BinaryTreeNode *p){
    if(p==nullptr)
        return;
    cout << p->val << endl;
    preOrder(p->pLeft);
    preOrder(p->pRight);
}
void InOrder(BinaryTreeNode *p){
    if(p==nullptr)
        return;
    InOrder(p->pLeft);
    cout << p->val << endl;
    InOrder(p->pRight);
}
int main(){
    int arr[13]{0,0,0,14,16,0,0,11,0,0,9,10,13}; // 这里要有一个思想，就是，遍历的时候，出现二叉树没有左右结点，都要写为0 也就是置🈳️
    BinaryTreeNode *p = buildTree(arr,12);
    preOrder(p);
    InOrder(p);
    // cout << arr[6] <<endl;
    return 0;
}