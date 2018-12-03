#include <iostream>

using namespace std;
/***
 * 1 冒泡排序
 * 2 插入排序
 * 原地排序，稳定性 O(1)空间复杂度
 * 交换和移动成就冒泡，选择，插入排序
 * 考虑时间，一般采用插入排序
 * 有序度和逆序度 判定交换次数
 * ***/
template <typename T> class bubbleInsertSort{
    public:
        bubbleInsertSort(T *array):arr(array){

        }
        T *arr;
        void bubbleSort(T array[]);
        void insertSort(T array[]);
    private:
        bubbleInsertSort(const bubbleInsertSort&);
        bubbleInsertSort& operator=(const bubbleInsertSort&);
};

template <typename T> void bubbleInsertSort<T>::bubbleSort(T arr[]){
    if(sizeof(arr)/sizeof(arr[0])){

    }
}
int main(){
    int arr[10];
    cout << sizeof(arr)/sizeof(arr[0]) << endl;
    return 0;
}

