/***
 * 动态规划
 * 经典：剪绳子问题
 * 剪出最大的乘积
 * ***/

#include <iostream>
#include <cmath>
using namespace std;

int maxProductAfterCutting(int len){
    if(len < 2)
        return 0;
    if(len == 2)
        return 1;
    if(len == 3)
        return 2;

    // 需要一个一维存储最大值
    int *products = new int[len+1];
    // 需要一个max作为临时比较值
    int max = 0;
    products[0] = 0;
    products[1] = 1;
    products[2] = 2;
    products[3] = 3;
    for(int i = 4;i<=len;++i){
        max = 0;
        for(int j = 1;j<=i/2;++j){
            int product = products[j]*products[i-j];
            if(max<product){
                max = product;
            }
            products[i] = max; // 将最优解放入products中。
        }
    }
    max = products[len];
    delete [] products;
    return max;
}

/***
 * 贪心算法
 * 每次都只剪3，然后算3的乘积
 * 若剩余最后一段，就剪2
 * 剩余剪2
 * ***/

int greedy_cutting_three(int len){
    if(len<2)
        return 0;
    if(len == 2)
        return 1;
    if(len == 3)
        return 2;
    // 贪心， 分三，每次都获取最优解
    int timesOf_three = len/3;
    if(len - timesOf_three*3 == 1){
        timesOf_three-=1;
    }
    int timesOf_two = (len-timesOf_three*3)/2;
    return pow(3,timesOf_three)*pow(2,timesOf_two);
}

// 位运算

int countOneInBinary(int num){
    int count = 0;
    while(num){
        ++count;
        num = (num-1)&num;
    }
    return count;
}
// 计算m改变多少二进制位才能得到n
int countChangeBit(int m,int n){
    int res = m^n;
    int count = 0;
    while(res){
      ++count;
      res = (res-1)&res;
    }
    return count;
}
int main(){
    cout << countChangeBit(10,13) << endl;
    return 0;
}