#include <iostream>
using namespace std;

class Solution {
public:
    int reverse(int x) {
       int ret = 0;
       while(x!=0){
           int pop = x%10;
           x/=10;
           // 我真的不知道可以这么分析，余数与整数的分析
           if((ret>INT_MAX/10)||(ret==INT_MAX/10&&pop>7)) return 0;
           if((ret<INT_MIN/10)||(ret==INT_MIN/10&&pop<-8)) return 0;
           ret = ret*10+pop;
       }
        return ret;
    }
};