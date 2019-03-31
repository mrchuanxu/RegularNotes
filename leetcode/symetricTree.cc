
#include <iostream>
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isSymetric(root,root);
    }
    
    bool isSymetric(TreeNode* sroot,TreeNode* proot){
        if(sroot==nullptr&&proot==nullptr) return true;
        if(sroot == nullptr||proot==nullptr) return false;
        
        if(sroot->val!=proot->val) return false;
        
        return isSymetric(sroot->left,proot->right)&&isSymetric(sroot->right,proot->left);
    }
};