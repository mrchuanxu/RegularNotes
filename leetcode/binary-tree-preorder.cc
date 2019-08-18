
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        // 模仿入栈即可
        vector<int> vec_res;
        if(root == nullptr) return vec_res;
        stack<TreeNode*> sta_node;
        sta_node.push(root);
        while(sta_node.size()!=0){
            // 前序遍历，先出栈，然后再入栈左
            vec_res.push_back(sta_node.top()->val);
            TreeNode *tmp = sta_node.top();
            sta_node.pop();
            if(tmp->right) sta_node.push(tmp->right);
            if(tmp->left){
                sta_node.push(tmp->left);
            }
        }
        return vec_res;
    }
};