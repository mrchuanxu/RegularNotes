/***
 * 0-1背包问题
 * 要么装，要么不装
 * 
 * 假设背包重量为100 物品个数为10，物品的重量存储在数组a中
 * 
 * 所以限制条件就是物品不能超过10，重量不能超过100
 * 
 * 然后我们求个价值 cv
 * 重量即价值量
 * 装了的重量为cw***/

#include <iostream>
using namespace std;

static int maxWeight = 0;
static int maxValue = 0;
// 画个递归树🌲 加个备忘录📕
static bool mew[10][101]; // 备忘录记录已经计算过的值
void storage_pack(int i,int cw,int items[],int cv){
    if(cw == 100||i==10){
        // if(cw>maxWeight) maxWeight = cw;
        if(cv>maxValue) maxValue = cv; 
        return;
    }
    if(mew[i][cw]) return; // 记录已经计算过的值
    mew[i][cw] = true;
    // 对于一个i物件，只有放还是不放到背包里
    storage_pack(i+1,cw,items,cv);
    if(cw+items[i]<=100){
        storage_pack(i+1,cw+items[i],items,cv+items[i]); // 物品的重量小，所以还是可以放的
    }
}

int main(){
    int items[] = {1,2,3,2,3,7,9,8,5,8,2,10,3,4};
    storage_pack(0,0,items,0);
    cout << maxWeight << endl;
    return 0;
}