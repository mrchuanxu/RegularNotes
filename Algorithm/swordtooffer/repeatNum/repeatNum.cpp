#include <iostream>
#include <vector>

using namespace std;
/***
 * 找出数组中重复的数字
 * 两种方式
 * 1. 修改数组 通过下标对比 O(n)时间复杂度
 * 2. 不修改数组,二分查找,不断切割,到最后一个数出现的次数查找为止.
 * ***/


// int DupArray::dupNum(){
//     int arrlen = sizeof(arr)/sizeof(*arr);
//     for(int i = 0;i<arrlen;i++){
//         while(*(arr+i) != i){
//             int tmp = *(arr+(*(arr+i)));
//             int *tmparr = arr+(*(arr+i));
//             tmparr = arr+i;
//             *(arr+i) = tmp;
//             if(*(arr+i) == *tmparr){
//                 return *(arr+i);
//             }
//         }
//     }
// }

int main(){
    int dupArr[7] = {0,1,2,3,4,5,5};
    int dupNum;
    for(int i = 0;i<sizeof(dupArr)/sizeof(*dupArr);i++){
        while(dupArr[i] != i){
           int tmp = dupArr[dupArr[i]];
           dupArr[dupArr[i]] = dupArr[i];
           dupArr[i] = tmp;
           if(dupArr[i] == dupArr[dupArr[i]]){
               dupNum = dupArr[i];
               break;
           }
        }
    }
    cout << dupNum << endl;
    return 0;
}
