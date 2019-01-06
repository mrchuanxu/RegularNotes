/***
 * 最小的k个数
 * 刚拿到这个题目的时候就会先把这个数组排序
 * 但是，会有更快的算法
 * 就是用大顶堆和小顶堆的思想
 * 在红黑树内取这几个数字
 * 
 * 可修改数字
 * 同样可以用第k个数的排序
 * 快排的partition
 * 大于k就在k的左边
 * 小于下标k就在k的右边递归
 * 当然不一定是有序
 * 但是肯定是最小值
 * 
 * 用到红黑树会比较好使用
 * 其中multiset就是用红黑树存储的
 * 
 * 
 * 寻找最大的k个数可以用最小堆实现
 * 寻找最小k个元素可用最大堆来实现
 * 
 * ***/

#include <set>
#include <iostream>
#include <vector>

using namespace std;
typedef multiset<int,greater<int> > setInt;
typedef multiset<int,greater<int> >::iterator setIterator;
void getLeastNumbers(const vector<int>& data,setInt& intSet,int k){
    intSet.clear();
    if(k<1||data.size()<k)
        return;
    vector<int>::const_iterator iter = data.begin();
    for(;iter!=data.end();++iter){
        if(intSet.size()<k){ // 在堆中建立k个元素的堆
            intSet.insert(*iter);
        }else{
            setIterator siter = intSet.begin(); // 与最大堆的堆顶元素做比较
            if(*iter < *siter){ // 小于堆顶元素就插入，然后堆化
                intSet.erase(*siter);
                intSet.insert(*iter);
            }
        }
    }
    for(auto siter = intSet.begin();siter!=intSet.end();++siter){
        cout << *siter << endl;
    }
}

int main(){
    vector<int> ivec{1,2,4,5,6,7,8,9,5,4,3,2,4,5,6,7,8};
    setInt intSet;
    getLeastNumbers(ivec,intSet,7);
    return 0;
}