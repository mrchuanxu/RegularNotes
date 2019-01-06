#include <vector>
#include <iostream>

using namespace std;


/***
 * 数据流中的中位数
 * 其实就是最大堆存储左边的数据
 * 最小堆存储右边的数字
 * 保证最小堆的数字大于最大堆的数字
 * 所以就会有不断滴取出最小堆的堆顶元素
 * 然后把堆顶元素放到最大堆
 * 最大堆再排序
 * 
 * 保证两边平均存放数据
 * 
 * ***/
template<typename T> class DynamicArray{
    vector<int> min;
    vector<int> max;
    public:
        void Insert(T num){
            if(((min.size()+max.size())&1)==0){
                if(max.size()>0&&num<max[0]){
                    max.push_back(num);
                    push_heap(max.begin(),max.end(),less<T>());

                    num = max[0];
                    pop_heap(max.begin(),max.end(),less<T>());
                    max.pop_back();
                }
                min.push_back(num);
                push_heap(min.begin(),min.end(),greater<T>());
            }
            // ...
        }
};