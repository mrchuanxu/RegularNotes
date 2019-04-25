/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[][]}
 */
var levelOrder = function(root) {
    // 这个用队列实现
    if(root==null) return [];
    var res = [];
    var que_pre = [];
    var que_nxt = [];
    que_pre.push(root);
    var res_tmp = [];
    var isNxt = 1;
    while(que_pre.length||que_nxt.length){
        if(isNxt){
            var tmpNode = que_pre.shift();
            if(tmpNode.left!=null) que_nxt.push(tmpNode.left);
            if(tmpNode.right!=null)que_nxt.push(tmpNode.right);
            res_tmp.push(tmpNode.val);
            if(que_pre.length==0){
                isNxt = 0;
                res.push(res_tmp);
                res_tmp = [];
            }
        }else{
             var tmpNode = que_nxt.shift();
            if(tmpNode.left!=null) que_pre.push(tmpNode.left);
            if(tmpNode.right!=null)que_pre.push(tmpNode.right);
            res_tmp.push(tmpNode.val);
            if(que_nxt.length==0){
                isNxt = 1;
                res.push(res_tmp);
                res_tmp = [];
            }
        }
    } 
    return res;
};