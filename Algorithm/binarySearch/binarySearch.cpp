#include <iostream>
#include <cmath>
using namespace std;
/***
 * 二分查找，快速查找，O(logn)的查找速度
 * 可以解决寻找旋转数组的最小数字的问题，数组需要是递增排序的数组的一个旋转，但是需要判断10111
 * 旋转 中值寻找 (low+high)>>1
 * 二分查找 中值 low+((high-low)>>1)
 * 求一个数的平方根 精确到第六位
 * ***/

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
// 二分 不断拆分 原理 middle 这是一个很好的想法，sqrt没想到是这样实现的 middle的左右赋值，大了就右边，小了就左边
double squrt(double num){
    if(num < 0 )
        return 0;
    double middle,pre;
    double r = num;
    double l = 0.0;
    middle = l+(r-l)/2;
    do{
        if(middle*middle>num)
            r = middle;
        else
            l = middle;
        pre = middle;
        middle = l+(r-l)/2;
    }while(abs(middle-pre)>0.000001);
    return middle;
}

//  在排序从小到大的元素的重复的数组中查找第一个元素等于给定值的位置
int firstEle(int *arr,int val,int len){
    if(len <= 1)
        return -1;
    int low = 0;
    int high = len - 1;
    while(low<=high){
        int middle = low + ((high-low)>>1);
        if(arr[middle]>val){
            high = middle - 1;
        }else if(arr[middle]<val){
            low = middle + 1;
        }else{
            if(middle == 0 || arr[middle - 1] == val) return middle; //重点
            else
                high = middle - 1;
        }
    }
    return -1;
}

// 在排序从小到大的元素的重复的数组中查找最后一个元素等于给定值的位置
int lastEle(int *arr,int val,int len){
    if(len<=1)
        return -1;
    int low = 0;
    int high = len - 1;
    while(low<=high){
        int middle = low+((high-low)>>1);
        if(arr[middle]>val){
            high = middle - 1;
        }else if(arr[middle]<val){
            low = middle + 1;
        }else{
            if(middle == len-1 || arr[middle+1] != val) return middle; // 重点
            else
                low = middle+1;
        }
    }
    return -1;
}

// 在排序从小到大的元素的重复的数组中查找第一个大于等于元素等于给定值的位置
int exactEle(int *arr,int val ,int len){
    if(len<=1)
        return -1;
    int low = 0;
    int high = len-1;
    while(low <= high){
        int middle = low+((high-low)>>1);
        if(arr[middle]>=val){
            if(middle == 0||arr[middle-1]<val) return middle; // 重点
            else 
                high = middle - 1;
        }else{
            low = middle+1;
        }
    }
    return -1;
}

// 在排序从小到大的元素的重复的数组中查找最后一个小于等于元素等于给定值的位置
int exactlastEle(int *arr,int val ,int len){
    if(len<=1)
        return -1;
    int low = 0;
    int high = len-1;
    while(low <= high){
        int middle = low+((high-low)>>1);
        if(arr[middle]<=val){
            if(middle == len-1||arr[middle+1]>val) return middle; //   重点
            else 
                low = middle + 1;
        }else{
            high = middle-1;
        }
    }
    return -1;
}

//  在循环数组中查找值等于给定值的位置
int cir_exacEle(int *arr,int val,int len){
    if(len <= 1)
        return -1;
    // 查找循环的变值，数组从小到大排序，将数组突然变为大到小的位置寻找出来
    int chagNum = 0;
    for(;chagNum < len;++chagNum){
        if(arr[chagNum]>arr[chagNum+1])
            break;
    }
    if(arr[chagNum] == val)
        return chagNum;
    else if(val<arr[chagNum]&&val>arr[0]){
        int low = 0;
        int high = chagNum-1;
        while(low<=high){
            int middle = low+((high-low)>>1);
            if(arr[middle]>val){
                high = middle - 1;
            }else if(arr[middle]<val){
                low = middle + 1;
            }else{
                return middle;
            }
        }
    }else{
        int low = chagNum+1;
        int high = len - 1;
        while(low<=high){
            int middle = low+((high-low)>>1);
            if(arr[middle]>val){
                high = middle - 1;
            }else if(arr[middle]<val){
                low = middle + 1;
            }else{
                return middle;
            }
        }
    }
    return -1;
}

// 第二种方法查找循环数组的值等于给定值 ==========================>_<!!!
int sec_cir_ExactEle(int *arr,int val,int len){
    if(len<=1)
        return -1;
    int low = 0;
    int high = len-1;
    while(low<=high){
        int middle = low+((high-low)>>1);
        if(arr[middle]>arr[low]){
            int low_fst = low;
            int high_fst = middle-1;
            while(low_fst<=high_fst){
                int middle_fst = low_fst+((high_fst-low_fst)>>1);
                if(arr[middle_fst]>val){
                    high_fst = middle_fst - 1;
                }else if(arr[middle_fst]<val){
                    low_fst = middle_fst + 1;
                }else{
                    return middle_fst;
                }
            }
            low = middle + 1;
        }else if(arr[middle]<arr[low]){
            int low_sec = middle+1;
            int high_sec = high;
            while(low_sec<=high_sec){
                int middle_sec = low_sec+((high_sec-low_sec)>>1);
                    if(arr[middle_sec]>val){
                        high_sec = middle_sec - 1;
                    }else if(arr[middle_sec]<val){
                        low_sec = middle_sec + 1;
                    }else{
                        return middle_sec;
                }
            }
            high = middle - 1;
        }
    }
    return -1;
}
int main(){
    int *arr =new int[10]{4,5,6,7,8,9,1,2,3,4};
    cout << sec_cir_ExactEle(arr,9,10) << endl;
    return 0;
}