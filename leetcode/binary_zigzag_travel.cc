
#include <vector>
#include <iostream>
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
    vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
        vector<vector<int> > vec_res;
        if(root == nullptr) return vec_res;
        
        stack<TreeNode*> sta_res[2];
        sta_res[0].push(root);
        bool isNxt = true;
        vector<int> res_tmp;
        while(sta_res[0].size()||sta_res[1].size()){
            if(isNxt){
                TreeNode* tmpNodePre = sta_res[0].top();
                if(tmpNodePre->left) sta_res[1].push(tmpNodePre->left);
                if(tmpNodePre->right) sta_res[1].push(tmpNodePre->right);
                res_tmp.push_back(tmpNodePre->val);
                sta_res[0].pop();
                if(sta_res[0].size()==0){
                    isNxt = false;
                    vec_res.push_back(res_tmp);
                    res_tmp.clear();
                }
            }else{
                TreeNode* tmpNodeNxt = sta_res[1].top();
                if(tmpNodeNxt->right) sta_res[0].push(tmpNodeNxt->right);
                if(tmpNodeNxt->left)sta_res[0].push(tmpNodeNxt->left);
                res_tmp.push_back(tmpNodeNxt->val);
                sta_res[1].pop();
                if(sta_res[1].size()==0){
                    isNxt = true;
                    vec_res.push_back(res_tmp);
                    res_tmp.clear();
                }
            }
        }
        return vec_res;
    }
};