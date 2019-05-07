#include <vector>
#include <iostream>
using namespace std;
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 其实就是构建一颗二叉搜索树
        // 二分查找 构建
        if(nums.size()==0) return nullptr;
        TreeNode *p = makeSortArraytoBst(nums,0,nums.size()-1);
        return p;
    }
    
    TreeNode* makeSortArraytoBst(vector<int>& nums,int start,int end){
        if(start>end) return nullptr;
        int middle = (start+end)>>1;
        TreeNode *p = new TreeNode(nums[middle]);
        p->left = makeSortArraytoBst(nums,start,middle-1);
        p->right = makeSortArraytoBst(nums,middle+1,end);
        return p;
    }
};