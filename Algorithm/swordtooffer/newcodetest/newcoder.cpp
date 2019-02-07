
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
    int jumpRecur(int number,int m){
        if(number==1||m == 1) return 1;
        if(number <1|| m < 1) return 0;
        if(number < m) return jumpRecur(number,number);
        if(number == m) return jumpRecur(number,m-1)+1;
        return jumpRecur(number,m-1)+jumpRecur(number-m,m);
    }
};
    int  NumberOf1(int n) {
         int count = 0;
         while(n){
             n=n-1;
             if(n&1)
                 ++count;
         }
         return count;
     }


int main(){
    // vector<int> pre{1,2,4,7,3,5,6,8};
    // vector<int> vin{4,7,2,1,5,3,8,6};
    // Solution so;
    // TreeNode *root;
    // root = so.reConstructBinaryTree(pre,vin);
    // int sum = 0;
    // for(int i = 3;i>=1;--i){
    //     sum += so.jumpRecur(3,i);
    //     //cout << sum << endl;
    // }
    // cout << sum+1 << endl;
    // int i = 8&1;
    // cout << "f" << i << endl;
    // const char *str = "testssssssss";
    // cout << strlen(str)<<endl;
    // vector<int> vec{1,2,3};
    // vector<int> vec3{3,4,5};
    // vec = vec3;
    // for(auto iter:vec){
    //     cout << iter << endl;
    // }
    char s[]="\\123456\123456\t";
    printf("%d\n",strlen(s));
    return 0;
}