
/***
 * 计数排序
 * 1. 寻找最大值k，分配k空间，记录各值出现次数
 * 2. 累加出现次数各值
 * 3. 申请适当空间，进行提取排序
 * 4. 赋值原来数组
 * 
 * 思考题
 * 排序 a A C c D d B f 1 E 3 5 字符串
 * ***/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CountSort{
    public:
        CountSort(){}
        int *array;
        void countingSort(int *arr,int n);
        void countString(string &str);
    private:
        CountSort(const CountSort&);
        CountSort& operator=(const CountSort&);
};

// class DerivedSort:public CountSort{
//     public:
//         DerivedSort() = default;
//     private:
//         int dernum;
// };

void CountSort::countString(string &str){
    //  处理数字，字母
    if(str.size() <=1)
        return;
   // 使用交换原则，交换得到字母的排序。 添加如数字 排序在中间
//    int strStart = 0;
//    int strEnd = str.size()-1;
//    while(strStart < strEnd){
//        if(str[strStart]>='A'&&str[strStart]<='Z'){
//            if(str[strEnd]>='a'&&str[strEnd]<='z'){
//                swap(str[strEnd],str[strStart]);
//                ++strStart;
//                --strEnd;
//            }else{
//                --strEnd;
//            }
//        }else{
//            ++strStart;
//        }
//    }
   // 计数排序
   int *count_ctr = new int[3]();
   for(int i = 0;i<str.size();++i){
    if(str[i]>='a'&&str[i]<='z'){
        ++count_ctr[0];
    }else if(str[i]>='0'&&str[i]<='9'){
        ++count_ctr[1];
    }else if(str[i]>='A'&&str[i]<='Z'){
        ++count_ctr[2];
    }
   }
   // 累加三个
   for(int i = 1;i<3;++i){
       count_ctr[i] = count_ctr[i]+count_ctr[i-1];
       cout<< i << ":" <<count_ctr[i] << endl;
   }
   // 申请空间进行插入
   char *rstr = new char[str.size()-1];
   for(int i = str.size()-1;i>0;--i){
       if(str[i]>='A'&&str[i]<='Z'){
           rstr[count_ctr[2]-1] = str[i];
           --count_ctr[2];
       }else if(str[i]>='a'&&str[i]<='z'){
           rstr[count_ctr[0]-1] = str[i];
           --count_ctr[0];
       }else if(str[i]>='0'&&str[i]<='9'){
            rstr[count_ctr[1]-1] = str[i];
           --count_ctr[1];
       }
   }
   // 置换到原str
   for(int i = 0;i<str.size();++i){
       str[i] = rstr[i];
   }
   delete [] rstr;
   delete [] count_ctr;
}
// 计数排序
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
    
    int *carr = new int[max_val+1]();
     // 将值计数
    for(int i = 0;i<n;i++){
        carr[arr[i]]++;
    }

    // 将计数值累加
    for(int i = 1; i<=max_val;i++){
        carr[i] = carr[i]+carr[i-1];
    }

    // 接下来进行排序
    int *rarr = new int[n]();
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
    int arr[9]{2,4,3,1,5,5,6,7,3};
    CountSort countSort;
    countSort.countingSort(arr,9);
    for(int i = 0;i<9;++i){  
        cout << arr[i] << endl;
    }
    string str("a1bcD4FYDe5RrH");
    countSort.countString(str);
    cout << str << endl;
    return 0;
}
