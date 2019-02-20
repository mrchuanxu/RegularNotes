/***
 * 今天最后一个问题
 * 硬币找零问题
 * 几种不同的币种
 * v1,v2,...,vn
 * 要支付w元
 * 求最少需要多少个硬币
 * 
 * vector<int> coin{1,3,5}
 * 支付9元
 * 最少需要3个硬币
 * 
 * f[1] = 1;
 * f[2] = 2;
 * f[3] = 1;
 * f[4] = 2;
 * f[5] = 1;
 * 通过这几个求值，最简单
 * 
 * 最少
 * 所以方程是
 * f(n) = 1+min{f(n-1),f(n-3),f(n-5)}
 * ***/
#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

// 取出最小值
int funMins(int m,int n,int k){
    int result = min(m,n);
    return min(k,result);
}

int funCoins(int n){
    int res_coins[n+1]; // 存储状态
    res_coins[0] = 0;
    res_coins[1] = 1;
    res_coins[2] = 2;
    res_coins[3] = 1;
    res_coins[4] = 2;
    res_coins[5] = 1;

    for(int m = 6;m<n+1;++m){
        res_coins[m] = 1+funMins(res_coins[m-1],res_coins[m-3],res_coins[m-5]); // 每块硬币已知
    }
    return res_coins[n];
}

// 以上就是1，3，5动态规划的问题，始终都记住要记录状态，那么请问，如果币种不一样呢？
// 不同币种就是funCoins(n) = 1+funMins({funCoins(n-v1),funCoins(n-v2),funCoins(n-v3)...});
// 其实可以用形参列表递归找出最小的值
// 剩下的就是状态转移方程 始终记录 对币种进行记录 coins[0] = 0; 
// 对于不是币种的，可以尝试在前面来入手

// int coinsMin(initializer_list<int> &il){ // 列表中找出最小的值
//     int result = *(il.begin());
//     for(auto coin:il){
//         result = min(coin,result);
//     }
//     return result;
// }
// int funCoins2(vector<int>& coinsKind,int w){
//     int len = coinsKind.size();
//     int res_coins[len+w];
//     for(auto coinKind:coinsKind){
//         res_coins[coinKind] = 1; // 初始化币种
//     }
    
//     for(int m=0;m<w+1;++m){
        
//     }

// }
int main(){
    int res = funCoins(1);
    cout << res << endl;
    return 0;
}

