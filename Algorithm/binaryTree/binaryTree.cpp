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

BinaryTreeNode* lookValue(BinaryTreeNode *p,int value){
    if(p == nullptr){
        return nullptr;
    }
    while(p!=nullptr){
        if(p->val>value){
            p = p->pLeft;
        }else if(p->val<value){
            p = p->pRight;
        }else{
            return p;
        }
    }
    return nullptr;
}

BinaryTreeNode* insertValue(BinaryTreeNode *p,int value){
    BinaryTreeNode *np = new BinaryTreeNode();
    np->val = value;
    if(p==nullptr)
        p = np;
    while(p!=nullptr){
        if(p->val>value){
            if(p->pLeft==nullptr){
                p->pLeft = np;
                return np;
            }
            p = p->pLeft;
        }else{
            if(p->pRight==nullptr){
                p->pRight = np;
                return np;
            }
             p = p->pRight;
        }
    }
    return nullptr; // 满了
}

BinaryTreeNode* lookFatherValue(BinaryTreeNode *p,int value){
    if(p == nullptr)
        return nullptr;
    BinaryTreeNode *fp;
    while(p!=nullptr){
        if(p->val>value){
            fp = p;
            p = p->pLeft;
        }else if(p->val<value){
            fp = p;
            p = p->pRight;
        }else if(p->val == value){
            p = fp;
            return p;
        }
    }
    return nullptr;
}

bool deleteValue(BinaryTreeNode *p,int value){
    auto dp = lookValue(p,value);
    auto fp = lookFatherValue(p,value);
    if(dp == nullptr)
        return false;
    if(dp->pLeft==nullptr&&dp->pRight==nullptr){
        if(fp->pLeft->val == value){ // 判断在父节点的左边还是右边
                fp->pLeft = nullptr;
                delete dp;
                return true;
            }else{ // 判断在父节点左边还是右边
                fp->pRight = nullptr;
                delete dp;
                return true;
        }
    }else if(dp->pRight!=nullptr&&dp->pLeft==nullptr){
        if(fp->pLeft->val == dp->val){
            fp->pLeft = dp->pRight;
        }else{
            fp->pRight = dp->pRight;
        }
        delete dp;
        return true;
    }else if(dp->pLeft!=nullptr&&dp->pRight==nullptr){
        if(fp->pLeft->val == dp->val){
            fp->pLeft = dp->pLeft;
        }else{
            fp->pRight = dp->pLeft;
        }
        delete dp;
        return true;
    }else if(dp->pLeft!=nullptr&&dp->pRight!=nullptr){
            if(fp == nullptr){ // 根节点
                auto tmp = dp;
                dp = dp->pRight;
                while(dp->pLeft!=nullptr){
                    dp = dp->pLeft;
                }
                dp->pLeft = tmp->pLeft;
                delete tmp; // 删除根节点
                return true;
            }
            auto tlp = dp->pLeft;
            auto delp = dp;
            dp = dp->pRight;
            if(dp->pLeft==nullptr){ // 考虑左值
                if(fp->pLeft->val == value){ // 判断在父节点的左边还是右边
                    dp->pLeft = tlp;
                    fp->pLeft = dp;
                    delete delp;
                    return true;
                }else{ // 判断在父节点左边还是右边
                    dp->pLeft = tlp;
                    fp->pRight = dp;
                    delete delp;
                    return true;
                }
            }else{
                while(dp->pLeft->pLeft!=nullptr){ // 遍历都左节点的最后 获得父节点
                    dp = dp->pLeft;
                }
                delp->val = dp->pLeft->val; // 替换值就好
                if(dp->pRight!=nullptr){ // 考虑右节点
                    dp->pLeft = dp->pLeft->pRight;
                }
                delete dp->pLeft;
                return true;
            }
    }
    return false;
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
    //preOrder(p);
    //InOrder(p);
    BinaryTreeNode *vp = lookFatherValue(p,10);
    cout << vp->val << endl;
    //InOrder(p);
    if(deleteValue(p,13)){
        InOrder(p);
    }
    // cout << arr[6] <<endl;
    return 0;
}