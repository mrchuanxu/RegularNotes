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
        void bubbleSort();
        void insertSort();
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
            if(*(arr+j*sizeof(T)) > *(arr+(j+1)*sizeof(T))){
                T tmp = *(arr+j*sizeof(T));
                *(arr+j*sizeof(T)) = *(arr+(j+1)*sizeof(T));
                *(arr+(j+1)*sizeof(T)) = tmp;
                flag = true;
            }
        }
        if(!flag)
            break;     
    }
}
int main(){
    int arr[10] = {2,3,4,7,6,4,2,3,3,4};
    bubbleInsertSort<int> bSort(arr);
    bSort.arr_size = 10;
    bSort.bubbleSort();
    int i = 0;
    while(i<10){
        cout << arr[i] << endl;
    }
    return 0;
}

