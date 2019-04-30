class Solution {
public:
    int mySqrt(int x) {
        if(x == 0) return 0;
        double pre = 0,result = 1;
        while(result!=pre){
            pre = result;
            // 牛顿迭代法，求K斜率值公式，求得result值
            result = (result+x/result)/2;
        }
        return (int)result;
    }
};