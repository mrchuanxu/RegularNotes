/***
 * 函数指针解决一般性判断问题
 * 将数组的奇数放在偶数前面
 * 通过指针解决
 * ***/
#include <iostream>
using namespace std;

void RecoderOldEven(int *arr,unsigned int len,bool (*func)(int)){
    if(len == 0||arr==nullptr)
        return;
    int *pbegin = arr;
    int *pEnd = arr+len-1;

    while(pbegin<pEnd){
        // 前面判断奇数
        while(pbegin<pEnd&&!func(*pbegin))
           pbegin++;
        // 判断偶数
        while(pbegin<pEnd&&func(*pEnd))
           pEnd--;
        if(pbegin<pEnd){
            swap(*pbegin,*pEnd);
        }
    }
}
bool old_even(int n){
     return n&0x1==0;
}
/***
 * 这里主要体现的思想是 函数指针，获得一般性的判断请求
 * 一般用函数指针会使得扩展性良好
 * 大框架不变
 * 只需要改变其中的判断即可
 * 比较灵活，方便！***/

struct TriNode{
    TriNode* pre;
    TriNode* next;
    int val;
};

int main(){
    int arr[] = {1,2,3,4,5,65,6,7,8};
    RecoderOldEven(arr,10,old_even);
    // TriNode arr[10]; 
    // int *arrp[10];
    // TriNode *arrp;
    // arrp->val = 50;
//     int vnum = 42;
//     arrp[1] = &vnum;
//   //  arr[3]->val = vnum;
//     arr[0].val = 33;
//     if(arr[6].pre==NULL){
//         cout << "true" << endl;
//     }
//     cout << arr[0].val <<endl;
    return 0;
}