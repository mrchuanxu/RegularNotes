/***
 * 数组中出现次数超过一半的数字
 * 数组中有一数字出现次数超过数组的长度的一半
 * 请找出这个数字
 * {1,2,2,2,2,2,2,2,2,3,5,4,2}
 * 输出2
 * 其实首先会想到先排序
 * 然后找出中位数
 * 但是这种可以用快排的思想去做
 * 先排一次，找到是不是中位数，如果是，就确定是这个数，否则，比中位数大就在左边找，比中位数小就继续在右边找
 * 如果恰好是中间
 * 就输出这个中间值
 * 但是是O(logn) 总的时间O(n)
 * 判断的时候要判断这个数组是不是有效输入
 * 
 * 前面的查找只是找出是否有这个中位数
 * 后面还要判断这个数字是否真的超过了一半
 * 不然就没有这个数字
 * ***/

/***
 * 数组的找法
 * 这种比较简单
 * 保存一个数字
 * 有，times++
 * 下一个不是 times--
 * times是0
 * 就继续将times=1
 * 然后继续保存下一个数字
 * ***/

// 检查这个数组是不是存在
#include <iostream>
using namespace std;

// 全局变量判断输入是否有效
bool checkArrVaild(int *number,int len){
    if(number== nullptr||len<=0)
        return false;
    return true;
}

bool checkArrNumHalf(int *number,int len,int num){
    int times = 0;
    for(int i = 0;i<len;i++){
        if(number[i]==num)
            times++;
    }
    if(times*2<=len){
        return false;
    }
    return true;
}
// 这种不用修改数组，比较简单易懂
int numberHalfLen(int *number,int len){
    if(!checkArrVaild(number,len))
        return 0;
    int times = 1;
    int result = number[0]; // 先保存一个元素
    // 然后开始遍历这个times
    for(int i = 1;i<len;i++){
        if(times == 0){
            result = number[i];
            times = 1; // 最后的result肯定是那个让times最后设为1的数字
        }
        if(number[i]==result)
            times++;
        else
            times--;
    }
    if(checkArrNumHalf(number,len,result))
        return result;
    return 0;    
}

int main(){
    int number[] = {1,2,3,4,5,4,4,3,3,3,3,3,3,3,3,4,5};
    int result = numberHalfLen(number,17);
    cout << result << endl;
    return 0;
}