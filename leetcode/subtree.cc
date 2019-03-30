#include <iostream>

struct TreeNode {
      int val;
      TreeNode *left;
    TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        bool result = false;
        if(s!=nullptr&&t!=nullptr){
            if(s->val==t->val) result = HasSubTree(s,t);
            if(!result) result = isSubtree(s->left,t);
            if(!result) result = isSubtree(s->right,t);
        }
        return result;
    }
    // 递归最好做
    // 先判断左右子树
    bool HasSubTree(TreeNode* s, TreeNode* t){
        if(t ==  nullptr && s == nullptr) return true;
        if(s == nullptr || t == nullptr) return false;
        
        if(s->val != t->val) return false;
        // 左右都要相等
        return HasSubTree(s->left,t->left)&&HasSubTree(s->right,t->right);
    }
};