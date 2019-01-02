#include <iostream>
#include <vector>

using namespace std;

struct BinaryTreeNode{
    int m_value;
    BinaryTreeNode* p_Left;
    BinaryTreeNode* p_Right;
};
/***
 * 主要在判断序列的各个方面
 * 判断是否到底前序遍历的尽头
 * 就是只有左子树没有右子树
 * 或者只有右子树没有左子树
 * 
 * 考虑中序遍历的输入是否可以一直有效
 * ***/
BinaryTreeNode* ConstructCore(int *preOrderStart,int *preOrderEnd,int *inOrderStart,int *inOrderEnd){
    BinaryTreeNode *root = new BinaryTreeNode();
    int rootValue = preOrderStart[0];
    root->m_value = rootValue;
    root->p_Left=root->p_Right=nullptr;
    if(preOrderStart==preOrderEnd){
        if(inOrderStart==inOrderEnd && *preOrderStart==*inOrderStart)
            return root;
        else{
            throw runtime_error("Invaild input");
        }
    }
    int *rootInorder = inOrderStart;
    while(rootInorder<=inOrderEnd && *rootInorder!=rootValue){ // 找到左子树之前的节点 在中序遍历查找
        ++rootInorder;
    }

    if(rootInorder==inOrderEnd&&*rootInorder!=rootValue) // 判断遍历不到任何字符，到底最后，查不出中序遍历的根
        throw runtime_error("Invaild input");
    
    int leftLen = rootInorder-inOrderStart;
    int *leftPreEnd = preOrderStart+leftLen;
    if(leftLen>0){
        // 构建左子树
        root->p_Left = ConstructCore(preOrderStart+1,leftPreEnd,inOrderStart,rootInorder-1);// 注意边界条件！！！
    }
    if(leftLen<preOrderEnd-preOrderStart){ // 判断是否应该构建右子树
       // 构建右子树
       root->p_Right = ConstructCore(leftPreEnd+1,preOrderEnd,rootInorder+1,inOrderEnd);
    }
    return root;
};


BinaryTreeNode* Construct(int *preOrder,int *inOrder,int len){
    if(preOrder==nullptr||inOrder==nullptr||len<=0)
        return nullptr;
    return ConstructCore(preOrder,preOrder+len-1,inOrder,inOrder+len-1);
}
/***
 * 二叉树找路径的问题
 * 找某一路径的和等于指定的值即可
 * 主要是分析思路
 * 依照前序遍历
 * 每次将遍历的值存入vector容器中，仿照栈的压入和弹出
 * ***/
void FindPath(BinaryTreeNode *pRoot,int currentSum,int expectedSum,vector<int> &path){
    // 首先 取节点的值
    path.push_back(pRoot->m_value);
    currentSum+=pRoot->m_value;
    bool isLef = pRoot->p_Left==nullptr&&pRoot->p_Right==nullptr;     // 是否为叶子节点
    if(currentSum == expectedSum && isLef){// 是叶子节点，总的值也是你
        for(auto iter = path.begin();iter!=path.end();++iter){
            cout << *iter << endl;
        }
    }
    if(pRoot->p_Left!=nullptr){
        FindPath(pRoot->p_Left,currentSum,expectedSum,path);
    }
    if(pRoot->p_Right!=nullptr){
        FindPath(pRoot->p_Right,currentSum,expectedSum,path);
    }
    // 去到叶子节点就开始往回走
    path.pop_back();
}

void BinaPath(BinaryTreeNode *pRoot,int expectedNum){
    if(pRoot==nullptr)
        return;
    vector<int> path;
    FindPath(pRoot,0,expectedNum,path);
}

int main(){
    int prearr[] = {1,2,4,7,3,5,6,8};
    int inarr[] = {4,7,2,1,5,3,8,6};
    BinaryTreeNode *root = new BinaryTreeNode();
    root = Construct(prearr,inarr,8);
    BinaPath(root,14);
    return 0;
}