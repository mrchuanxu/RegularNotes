#include <iostream>
#include <cmath>
using namespace std;

/***
 * 给出一个树结构
 * 判断B是不是A的子结构
 * 判断两个二叉树
 * 用的是递归***/
struct BinaryTreeNode{
        double m_dbValue; // 这里是个坑 判断的时候只能用 fabs(num1-num2)<0.0000001
        BinaryTreeNode* m_pLeft;
        BinaryTreeNode* m_pRight;
};

/***
 * 判断两个数是否相同***/
bool equal(double num1,double num2){
        if(abs(num1-num2)<0.0000001)
           return true;
        else 
           return false;
}
/***
 * 首先解决子问题
 * 子问题是
 * 一颗子树的A树的根节点是否是和一棵B树的根节点相同***/

bool binaryRoot(BinaryTreeNode *p_LRoot,BinaryTreeNode *p_RRoot){
        // 边界问题 两个树是不是空了，就是叶子节点为空就爆出不是
        if(p_LRoot == nullptr)
            return false;
        if(p_RRoot == nullptr)
            return false;
        
}
