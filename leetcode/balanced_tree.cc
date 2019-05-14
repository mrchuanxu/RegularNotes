/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(root==nullptr) return true;
        int idep;
        int *depth = &idep;
        return isBalanced(root,depth);
    }    
    
    bool isBalanced(TreeNode* root,int* depth){
        if(root==nullptr){
            *depth = 0; // 记录当前深度
            return true;
        }
        int nleft,nright,gap;
        if(isBalanced(root->left,&nleft)&&isBalanced(root->right,&nright)){// 后序遍历判断左右子树
            gap = nleft-nright;
            if(gap<=1&&gap>=-1){// 判断是否超过1
                *depth = (nleft>nright)?nleft+1:nright+1;// 获取当前最大的深度
                return true;
            }
        }
        return false;
    }

};