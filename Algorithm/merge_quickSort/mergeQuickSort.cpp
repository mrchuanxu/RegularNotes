/***
 * 1. 归并排序 递归合并 分而治之 时间 O(nlogn) 空间 O(n) O
 * 2. 快速排序 O
 * 3. 快速排序寻找第k大元素 O
 * 4. 递归最大的特点就是不要绕进去，有递推公式就行了！O
 * ***/
#include <vector>
#include <iostream>
using namespace std;

template <class T> class MergeQuickSort{
    public:
        explicit MergeQuickSort(){}
        void merge_sort(T *arr,int start,int end);
        void en_merge(T *arr,int mid,int left,int right);
        void quick_sort(T *arr,int start,int end);
        int partition(T *arr,int start,int end);
        void k_biggerelement(T *arr,int k,int start,int end);
        int partitionk_element(T *arr,int start,int end);
    private:
        MergeQuickSort(const MergeQuickSort&);
        MergeQuickSort& operator=(const MergeQuickSort&);
};
// 归并排序
template <class T> void MergeQuickSort<T>::en_merge(T *arr,int mid,int left,int right){
     int lbegin = left;
     int rbegin = mid+1;
     vector<T> vtmp; // 最后会销毁
     cout <<"vtmp size:" << vtmp.size() << endl;
     while(lbegin <= mid && rbegin <= right){ // 这里的判定条件需要判定两个方向，一个是左边的尾部，一个是右边的尾部
         if(arr[lbegin] < arr[rbegin]){
             vtmp.push_back(arr[lbegin++]);
         }else{
             vtmp.push_back(arr[rbegin++]);
         }
     }
     // 这样会快一点
     while(lbegin <= mid){
         vtmp.push_back(arr[lbegin++]);
     }
     while(rbegin <= right){
         vtmp.push_back(arr[rbegin++]);
     }
    // 这样会有几个赋值操作，所以不推荐 但是可行
    // int istart = lbegin;
    // int iend = mid;
    // if(rbegin<=right){
    //     istart = rbegin;
    //     iend = right;
    // }
    // while(istart<=iend){
    //     vtmp.push_back(arr[istart++]);
    // }
     cout << "vtmp size after:" << vtmp.size() << endl;
     for(int i = 0; i < vtmp.size();i++){
        arr[left+i] = vtmp[i];
        // cout << vtmp[i] << endl;
     }
}

template <class T> void MergeQuickSort<T>::merge_sort(T *arr,int start,int end){
     if(start >= end)
         return;
     int middle = (start+end)/2;
     merge_sort(arr,start,middle); // 只需要将问题解成子问题 分
     merge_sort(arr,middle+1,end);
     en_merge(arr,middle,start,end); // 治之
}

// 快速排序
template <class T> void MergeQuickSort<T>::quick_sort(T *arr,int start,int end){
    if(start>=end)
        return;
    int middle_p = partition(arr,start,end); // 先治后分
    quick_sort(arr,start,middle_p-1);
    quick_sort(arr,middle_p+1,end);
}
// 这是快排的重点 分区
template <class T> int MergeQuickSort<T>::partition(T *arr,int start,int end){
    // 分区点
    T pivot = arr[end];
    // 分区点可以尝试三点取中法。开一个函数取也是可以的，这里先在这里尝试
    // int middle = (start+end)/2;
    // middle end start 取中间的值
    // 比较取中 
    // 后面通过不同的取值，作为更换
    int i = start;
    for(int j = start; j < end; j++){
        if(arr[j] > pivot){ // 分区的思想，可一在这里体现，其实就是改一下顺序 < 倒序 > 就能求出第k大元素。 
        swap(arr[i],arr[j]); // 先治后分！符合原地排序
        ++i;
        }
    }
    swap(arr[i],arr[end]);
    return i;
}
// 查找第k大元素
template <class T> void MergeQuickSort<T>::k_biggerelement(T *arr,int k,int start,int end){
    if(start>=end)
        return;
    int p = partition(arr,start,end);
    if(p+1 == k){
        cout << arr[p] << endl;
        return;
    }
    else if(k>p+1)
        k_biggerelement(arr,k,p+1,end);
    else if(k<p+1)
        k_biggerelement(arr,k,start,p-1);
}

int main(){
    int arr[8] = {11,8,3,9,7,1,2,5};
    MergeQuickSort<int> mergeQuickSort;
    mergeQuickSort.merge_sort(arr,0,7);
    for(int i = 0; i<8;i++){
        cout << arr[i] << endl;
    }

    int arrquick[9] = {12,3,4,5,7,3,6,8,0};
    mergeQuickSort.quick_sort(arrquick,0,8);
    for(int i = 0; i<9;i++){
        cout << arrquick[i] << endl;
    }
    int a = 'a'-'a';
    int b = 'b'-'a';
    cout << b << endl;
    //mergeQuickSort.k_biggerelement(arrquick,4,0,8);
    return 0;
}