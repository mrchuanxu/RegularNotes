#include <iostream>

using namespace std;

template <typename T> class BinarySearch{
    public:
        BinarySearch() = default;
        int binary_search(T *arr,T value,int len);
    private:
        BinarySearch(const BinarySearch&);
        BinarySearch& operator=(const BinarySearch&);
};

template <typename T> int BinarySearch<T>::binary_search(T *arr,T val,int len){
    if(len <= 1)
        return -1;
    int low = 0;
    int high = len-1;
    while(low<=high){
        int mid = low+((high-low)>>1);
        if(val > arr[mid]){
            low = mid+1;
        }else if(val < arr[mid]){
            high = mid-1;
        }else if(val == arr[mid]){
            return mid;
        }
    }
    return -1;
}