class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // 容器vector的使用 插入排序，将有序区作为nums target为插入对象
        // 其实就是插入排序的改版
        // 重点考虑异常
        if(nums.size() == 0) return 0;
        nums.push_back(target);
        int j = nums.size()-2;
        for(;j>=0;j--){
            if(nums[j]>=target){
                nums[j+1] = nums[j];
            }else{
                break;
            }
        }
        return j+1;
    }
};