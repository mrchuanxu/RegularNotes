#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // 遇到相同的就删掉
        // 进行数据搬移操作
        if(nums.size()<=1) return nums.size();
        // 快慢指针
        int i=0,j=1;
        while(i<nums.size()&&j<nums.size()){
            if(nums[i]==nums[j]){
                int count = i;
                while(j<nums.size()){ // 进行数据搬移
                    swap(nums[count++],nums[j++]);
                }
                nums.pop_back();
            }else{
                i++;
            }
             j=i+1;
        }
        return nums.size();
    }
};