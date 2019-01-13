
#include <iostream>
#include<vector>
using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size()==0||vin.size()==0) return nullptr;
        bool existNum = false;
       // 获取与前序遍历的节点相同的长度，放到左子树
        int iLen;
        for(iLen = 0;iLen<vin.size();++iLen){
            if(vin[iLen]==pre[0]){
                existNum = true;
                break;
            }
        }
        if(!existNum&&vin.size()!=pre.size()) return nullptr;// 不存在这棵树
        auto preIter = ++pre.begin();
        auto vinIter = vin.begin();
        TreeNode* root = new TreeNode(pre[0]);
        // root->val = pre[0];
        cout << root->val << endl;
        vector<int> lpre;
        vector<int> lvin;
        --iLen;
        for(;iLen>0;--iLen){
            lpre.push_back(*preIter);
            lvin.push_back(*vinIter);
            ++preIter;
            ++vinIter;
        }
        root->left = reConstructBinaryTree(lpre,lvin); // 递归左子树
        vector<int> rpre;
        vector<int> rvin;
        ++vinIter;
        for(;vinIter!=vin.end();++vinIter){
            rvin.push_back(*vinIter);
            rpre.push_back(*preIter);
            ++preIter;
        }
        root->right = reConstructBinaryTree(rpre,rvin); // 递归右子树
        return root;
    }
};

int main(){
    vector<int> pre{1,2,4,7,3,5,6,8};
    vector<int> vin{4,7,2,1,5,3,8,6};
    Solution so;
    TreeNode *root;
    root = so.reConstructBinaryTree(pre,vin);
    return 0;
}