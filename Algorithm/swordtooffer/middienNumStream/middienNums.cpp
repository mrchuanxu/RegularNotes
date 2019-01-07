#include <vector>
#include <iostream>
#include <exception>

using namespace std;


/***
 * 数据流中的中位数
 * 其实就是最大堆存储左边的数据
 * 最小堆存储右边的数字
 * 保证最小堆的数字都大于最大堆的数字
 * 所以就会有不断滴取出最小堆的堆顶元素
 * 然后把堆顶元素放到最大堆
 * 最大堆再排序
 * 
 * 保证两边平均存放数据
 * 
 * ***/
template<typename T>
class MiddienNums{
    // 大顶堆和小顶堆
    vector<T> mins;
    vector<T> maxs;
    public:
        void insertNum(const T& num){
            if((mins.size()+maxs.size())&1==0){ // 如果是偶数 插入小顶堆
                // 要保证平均分配 保证每次都会比较一次 新数据先插入顶堆
                if(maxs.size()>0&&num<mins[0]){ // 如果这个值比最小堆堆顶元素要小，就插入到大顶堆，并且把大顶堆最大的元素堆顶元素取出来放到小顶堆中
                    maxs.push_back(num);
                    num = maxs[0]; // 取出大顶堆最大元素
                    push_heap(maxs.begin(),maxs.end(),less<T>());
                    pop_heap(maxs.begin(),maxs.end(),less<T>()); // 将元素最大值放到堆尾
                    maxs.pop_back(); // 将尾元素弹出 删掉
                }
                mins.push_back(num);
                push_heap(mins.begin(),mins.end(),greater<T>()); //  建立小顶堆
            }else{
                // 如果是奇数 插入大顶堆
                if((mins.size()>0&&mins[0]<num)){ // 如果这个值比最小堆堆顶元素大，那么就取出小顶堆的元素，插入到大顶堆
                    mins.push_back(num);
                    num = mins[0];
                    push_heap(mins.begin(),mins.end(),greater<T>());
                    pop_heap(mins.begin(),mins.end(),greater<T>());
                    mins.pop_back();
                }
                maxs.push_back(num);
                push_heap(maxs.begin(),maxs.end(),less<T>());
            }
        }

        T& getMiddle(vector<T> &mins,vector<T> &maxs){
            size_t sumsize = mins.size()+maxs.size();
            if(sumsize == 0)
                throw runtime_error("No numbers at all");
            T middle;
            if(sumsize&1==0){
                middle = (mins[0]+maxs[0])/2;
            }else{
                middle = mins[0]; // 因为先存的小根堆，所以奇数的中位数就在这最顶
            }
            return middle;
        }
};


int main(){
    return 0;
}