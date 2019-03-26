class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0||(x!=0)&&x%10==0) return false;
        // 因为负数，不需要回文判断就知道false
        // 尝试将x求余放入链表，利用快慢指针
        // 最高位等于个位，那么我直接将x求余得到的个位持续相加
        int ret = 0;
        while(x>ret){
            ret = ret*10+x%10;
            x/=10;
        }
        // 减少一半数字的判断
        return (x==ret)||(x==ret/10);
        // 最后的判断
    }
};