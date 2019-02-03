/***
 * 分而治之
 * 分治是一种算法思想，一般来说，分治适合递归来实现
 * 分治，将原问题划分成n个规模较小，并且结构与原问题相似的子问题，递归地解决这些子问题
 * 而后，合并其结果，就得到原问题的解
 * 
 * 递归实现三个操作
 * 分解：将原问题分解成一系列的子问题
 * 解决：递归地求解各个子问题，若子问题足够小，则直接求解
 * 合并：将子问题的结果合并成原问题
 * 
 * 分治条件
 * 原问题与分解成的子问题具有相同的模式
 * 原问题分成的小问题可以独立求解，子问题之间没有相关性(区分动态规划)
 * 具有分界终止条件，即问题足够小，可以直接求解
 * 可以将子问题合并成原问题，而这个合并操作的复杂度较低
 * 
 * 尝试求解一组数据的逆序度的对数或有序度的对数
 * 归并可以求解
 * 归并非常符合分而治之的思想
 * 先分后治，而求逆序度，
 * 
 * 这里先介绍分治算法的几个思想的实现一个是归并排序，一个是快速排序，一个是求有序度的实现
 * 
 * ***/

/***
 * 归并排序
 * 归并排序的思想比较简单
 * 先分后治，重点在于治
 * 
 * 而后我们要使用归并排序求逆序度
 * 统计，只要start之后的数字比middle之后的大，那么就可以统计为一个逆序对个数
 * ***/

#include <vector>
#include <iostream>

using namespace std;
template <typename T>
class Sort{
    public:
        Sort() = default;
        // merge
        void merge_sort(vector<T> &vec,int start,int end);
        void merge(vector<T> &vec,int start,int middle,int end);
        // quick
        void partition(vector<T> &vec,int start,int end);
        void quick_sort(vector<T> &vec,int start,int end);
    private:
        int nums; // 记录逆序度个数
};
template <typename T>
void Sort<T>::merge_sort(vector<T> &vec,int start,int end){
    // 终止条件
    if(start>=end) return;
    int middle = (start+end)/2;
    merge_sort(vec,start,middle);
    merge_sort(vec,middle+1,end);
    // 治
    merge(vec,start,middle,end);
    // cout << nums << endl;
}

template <typename T>
void Sort<T>::merge(vector<T> &vec,int start,int middle,int end){
    // 治比较重要
    // 先设i,j,k
    int  lbegin = start;
    int rbegin = middle+1;
    // 申请存储空间
    vector<T> tmpvec;
    while(lbegin<=middle&&rbegin<=end){
        if(vec[lbegin]<=vec[rbegin]){
            tmpvec.push_back(vec[lbegin++]);
        }else{
            // 统计start到middle之间，比lbegin大的数
            nums += (middle-lbegin + 1);
            tmpvec.push_back(vec[rbegin++]);
        }
    }
    // 如果没有遍历完，要么是i没遍历完，要么是j
    while(lbegin<=middle){
        tmpvec.push_back(vec[lbegin++]);
    }
    while(rbegin<=end){
        tmpvec.push_back(vec[rbegin++]);
    }
    for(int count = 0;count<tmpvec.size();count++){
        vec[start+count] = tmpvec[count]; // 巧妙的将数据归并在一起
    }
}

int main(){
    Sort<int> merge_s;
    vector<int> vec{8,11,3,9,7,1,2,5};
    merge_s.merge_sort(vec,0,7);
    for(auto iter:vec){
        cout << iter << endl;
    }
    return 0;
}