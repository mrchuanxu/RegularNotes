
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
    vector<int> inorderTraversal(TreeNode* root) {
        // 同样仿栈 哇，停了两三天，就开始想不清楚了哈哈哈，再想想
        vector<int> vec_res;
        if(root == nullptr) return vec_res;
        // 先要有栈 不可以修改root
        // 往左遍历，然后入栈
        stack<TreeNode*> sta_res;
        TreeNode* tmp = root;
        while(tmp!=nullptr || sta_res.size()!=0){
            while(tmp!=nullptr){
                sta_res.push(tmp);
                tmp = tmp->left;
            } // 先遍历左边 遍历完左边再看右边
            tmp = sta_res.top();
            sta_res.pop();
            vec_res.push_back(tmp->val);
            tmp = tmp->right;
        }
        return vec_res;
    }
};