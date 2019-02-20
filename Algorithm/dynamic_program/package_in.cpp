#include <iostream>
#include <vector>

using namespace std;

/***
 * 背包问题
 * 将一个问题分为多个阶段
 * 然后前一个状态决定后面的状态
 * 要么装
 * 要么不装
 * 
 * 第一个问题求最大的重量
 * 
 * 第二个问题，求最大的价值量
 * ***/
// w是最大重量，items是物品重量
void package_in(int w,int items[],int itemlen){
    bool states[itemlen-1][w+1];
    states[0][0] = true; // 初始化第一个变量，选择不装，重量还是0
    states[0][items[0]] = true; // 初始化第一行
    // 然后开始遍历每一个物体
    for(int i = 1;i<itemlen;i++){
        // 不装物体
        for(int j = 0;j<=w;j++){
            if(states[i-1][j])states[i][j] = true; 
        }
        // 装物体
        for(int j = 0;j<=w-items[i];j++){
            // 向着重量出发
            if(states[i-1][j])states[i][j+items[i]] = true;
        }
    }
    for(int i=w;i>=0;--i){
        if(states[itemlen-1][i]) cout << i << endl;
    }
}

// 假设变为全装，然后每次都计算重量
void package_in_one(int w,int items[],int itemlen){
    bool states[w+1];
    // states[0] = true; // 初始化第一个变量，选择不装，重量还是0
    states[items[0]] = true; // 初始化第一行
    // 然后开始遍历每一个物体
    for(int i = 1;i<itemlen;i++){
        // 装物体
        for(int j = w-items[i];j>=0;--j){ // 从后面开始算起
            // 向着重量出发 主要是量化每个物品 根本就不需要考虑前面的值
            if(states[j])states[j+items[i]] = true;
        }
    }
    for(int i=w;i>=0;--i){
        if(states[i]) cout << i << endl;
    }
}

int package_in_value(int w,int items[],int itemsvalue[],int itemlen){
    int states[itemlen-1][w+1];
    //  初始化变量
    for(int i = 0;i<itemlen;++i){
        for(int j = 0;j<w+1;++j){
            states[i][j] = -1;
        }
    }
    states[0][0] = 0;
    states[0][items[0]] = itemsvalue[0]; // 初始化
    // 然后开始遍历每一个物体
    for(int i = 1;i<itemlen;i++){
        // 不装物体
        for(int j = 0;j<=w;j++){
            if(states[i-1][j]>0)states[i][j] = states[i-1][j]; 
        }
        // 装物体
        for(int j = 0;j<=w-items[i];j++){
            // 向着重量出发
            if(states[i-1][j]>=0){
                int value = states[i-1][j]+itemsvalue[i];
                if(value > states[i][j+items[i]]) states[i][j+items[i]] = value;
            }
        }
    }
    int maxValue = -1;
    for(int i=0;i<=w;++i){ // 寻找最大值
        if(states[itemlen-1][i]>maxValue) maxValue = states[itemlen-1][i];
    }
    return maxValue;
}

