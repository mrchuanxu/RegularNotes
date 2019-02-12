#include <iostream>
using namespace std;

// weight 表示物品重量，n表示物品个数，w表示背包可承载的重量
int knapsack(int weight[],int n,int w){
    bool states[n][w+1];
    states[0][0] = true; // 第一行的数据要特殊处理
    states[0][weight[0]] = true;
    for(int i = 1;i<n;++i){ // 动态规划状态转移
        for(int j = 0;j<=w;++j){ // 不把第i个物品放入背包
            if(states[i-1][j] == true) states[i][j] = states[i-1][j];
        }
        for(int j = 0;j<=w - weight[i];++j){ // 把第i个物品放入背包
            if(states[i-1][j] == true) states[i][j+weight[i]] = true;
        }
    }
    for(int i = w;i>=0;--i){ // 输出结果 求的是背包能放的最大重量
        if(states[n-1][i] == true) return i;
    }
    return 0;
}

// 申请一维空间来获取背包最大的重量
int kanpsack2(int weight[],int n,int w){
    bool states[w+1];
    states[0] = true;
    states[weight[0]] = true;
    for(int i = 1;i<n;++i){
        for(int j = w-weight[i];j>=0;--j){
            if(states[j] == true) states[j+weight[i]] = true;
        }
    }
    for(int i = w;i>=0;--i){
        if(states[i] == true) return i;
    }
    return 0;
}

// 总价值量最大
int kanpsack3(int weight[],int value[],int n,int w){
    int states[n][w+1];
    for(int i = 0;i < n; ++i) //初始化states
    {
        for(int j = 0; j< w+1;++j){
            states[i][j] = -1;
        }
    }
    states[0][0] = 0;
    states[0][weight[0]] = value[0];
    for(int i = 1;i<n;++i){
        for(int j = 0;j<=w;++j){
            if(states[i-1][j] >= 0) states[i][j] = states[i-1][j];
        }
        for(int j = 0;j<=w-weight[i];++j){
            if(states[i-1][j]>=0){
                int v = states[i-1][j]+value[i];
                if(v>states[i][j+weight[i]]){ // 价值只要比之前的大就换
                    states[i][j+weight[i]] = v;
                }
            }
        }
    }
    int maxvalue = -1;
    for(int j = 0;j<=w;++j){
        // 从最后找最大值
        if(states[n-1][j] > maxvalue) maxvalue = states[n-1][j];
    }
    return maxvalue;
}
int main(){
    int weight[] = {2,2,4,6,3};
    int i = knapsack(weight,5,100);
    cout << i << endl;
    return 0;
}