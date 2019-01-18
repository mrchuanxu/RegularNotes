#include <iostream>
#include <stack>
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
        if(p_RRoot == nullptr)
            return true;   // 这是一个比较重要的一点，即遍历到B树的最后一层，返回true，作为结束条件 而且一定要在第一条！！！先判断子结构嘛
        if(p_LRoot == nullptr)
            return false;
        if(!equal(p_LRoot->m_dbValue,p_RRoot->m_dbValue))
            return false;
        return binaryRoot(p_LRoot->m_pLeft,p_RRoot->m_pLeft)&&binaryRoot(p_LRoot->m_pRight,p_RRoot->m_pRight);
}

bool binarySubSame(BinaryTreeNode *p_LRoot,BinaryTreeNode *p_RRoot){
        if(p_LRoot == nullptr)
            return false;
        if(p_RRoot == nullptr)
            return false;
        bool result = false;
        if(equal(p_LRoot->m_dbValue,p_RRoot->m_dbValue))
            result = binaryRoot(p_LRoot,p_RRoot);
        if(!result)
            result = binarySubSame(p_LRoot->m_pLeft,p_RRoot);
        if(!result)
            result = binarySubSame(p_LRoot->m_pRight,p_RRoot);
        return result;
}

/***
 * 求二叉树的镜像
 * 其实就是交换非叶子节点的左右子节点
 * 遇到我就交换
 * ***/
void MirrorbinaryTree(BinaryTreeNode *btn){
    if(btn == nullptr)
        return;
    if(btn->m_pLeft == nullptr&&btn->m_pRight == nullptr)
        return;
    swap(btn->m_pLeft,btn->m_pRight);
    if(btn->m_pLeft)
        MirrorbinaryTree(btn->m_pLeft);
    if(btn->m_pRight)
        MirrorbinaryTree(btn->m_pRight);
}

/***
 * 用循环实现上述镜像
 * 要想明白二叉树的递归调用，首先得明白二叉树的存储方式和栈的处理
 * 所以需要学会构建树这个结构
 * 考虑清楚运行完一个pLeft就要压栈一个pRight然后再考虑到程序最后出栈操作
 * ***/
void MirrorTree(BinaryTreeNode *btn){
    if(btn == nullptr)
        return;
    // 用栈来解决
    stack<BinaryTreeNode* > stcNode;
    stcNode.push(btn);
    while(stcNode.size()>0){
        BinaryTreeNode *pbtn = stcNode.top();
        stcNode.pop();
        swap(pbtn->m_pLeft,pbtn->m_pRight);
        // 入栈操作
        if(pbtn->m_pLeft)
            stcNode.push(pbtn->m_pLeft);
        if(pbtn->m_pRight)
            stcNode.push(pbtn->m_pRight);
    }
}