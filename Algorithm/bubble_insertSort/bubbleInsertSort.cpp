#include <iostream>

using namespace std;
/***
 * 1 冒泡排序 O
 * 2 插入排序 O
 * 原地排序，稳定性 O(1)空间复杂度 O
 * 交换和移动成就冒泡，选择，插入排序 O
 * 考虑时间，一般采用插入排序 O
 * 有序度和逆序度 判定交换次数 O
 * ***/
template <typename T> class bubbleInsertSort{
    public:
        bubbleInsertSort(T *array):arr(array){
        }
        T *arr;
        void bubbleSort();
        void insertSort();
        void selectSort();
        int arr_size;
    private:
        bubbleInsertSort(const bubbleInsertSort&);
        bubbleInsertSort& operator=(const bubbleInsertSort&);
};

template <typename T> void bubbleInsertSort<T>::bubbleSort(){
    if(arr_size <= 1){
          return;
    }
    for(int i = 0; i < arr_size; i++){
        bool flag = false;
        for(int j = 0; j < arr_size-i-1;++j){
            if(arr[j] > arr[j+1]){
                // int tmp = arr[j]; // origin arr arr[j]
                // arr[j] = arr[j+1]; // arr[j] = arr[j+1]
                // arr[j+1] = tmp; // arr[j+1]
                swap(arr[j],arr[j+1]);
                flag = true;
            }
            //++arr;
        }
        if(!flag)
            break;
    }
}
// 插入排序
template <class T> void bubbleInsertSort<T>::insertSort(){
    if(arr_size<=1){
        return;
    }
    for(int i = 1; i <arr_size;i++){
        T value = arr[i];
        int j = i-1;
        for(;j>=0;--j){
            if(arr[j] > value){
                arr[j+1] = arr[j]; // 腾出一个空间
            }else{
                break;
            }
        }
        arr[j+1] = value;
    }
}

// 选择排序
template <class T> void bubbleInsertSort<T>::selectSort(){
    if(arr_size <=1) return;
    for(int i = 0;i<arr_size;i++){
        int j = i+1;
        for(;j<arr_size;j++){// 找到最小的元素
            if(arr[i]>arr[j]) {
               swap(arr[i],arr[j]);
            }
        }
    }
}

int main(){
    int *arr = new int[10]{2,3,4,7,6,4,2,3,3,4};
    bubbleInsertSort<int> bSort(arr);
    bSort.arr_size = 10;
    // bSort.bubbleSort();
    //bSort.insertSort();
    bSort.selectSort();
    int i = 0;
    while(i<10){
        cout << arr[i] << endl;
        i++;
    }
    delete [] arr;
    return 0;
}

