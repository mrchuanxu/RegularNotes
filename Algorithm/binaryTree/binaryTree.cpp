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
    BinaryTreeNode *p;
    if(arr[len]==0||len<0) // FIXME:
        p = nullptr;
    else{
        p = new BinaryTreeNode();
        p->val = arr[len];
        p->pLeft = buildTree(arr,--len);
        p->pRight = buildTree(arr,--len); 
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
    int arr[9]{0,14,16,0,11,0,9,10,13};
    BinaryTreeNode *p = buildTree(arr,8);
    preOrder(p);
    // InOrder(p);
    // cout << arr[6] <<endl;
    return 0;
}