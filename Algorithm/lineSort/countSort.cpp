
#include <iostream>
#include <string>
using namespace std;

class CountSort{
    public:
        CountSort(){}
        int *array;
        void countingSort(int *arr,int n);
    private:
        CountSort(const CountSort&);
        CountSort& operator=(const CountSort&);
};

void CountSort::countingSort(int *arr,int n){
    if(n <= 1)
        return;
    int max_val = arr[0];

    // 首先寻找最大值
    for(int i = 0; i < n;i++){
        if(max_val<arr[i]){
            max_val = arr[i];
        }
    }
    
    int *carr = new int[max_val+1];
     // 将值计数
    for(int i = 0;i<n;i++){
        carr[arr[i]]++;
    }

    // 将计数值累加
    for(int i = 1; i<=max_val;i++){
        carr[i] = carr[i]+carr[i-1];
    }

    // 接下来进行排序
    int *rarr = new int[n];
    for(int i = n-1;i>=0;--i){
        rarr[carr[arr[i]]-1] = arr[i];
        carr[arr[i]]--;
    }

    for(int i = 0;i<n;++i){
        arr[i] = rarr[i];
    }
    delete [] rarr;
    delete [] carr;
}

int main(){
    int arr[9] = {2,4,3,1,5,5,6,7,3};
    CountSort countSort;
    countSort.countingSort(arr,9);
    for(int i = 0;i<9;++i){
        cout << arr[i] << endl;
    }
    return 0;
}
