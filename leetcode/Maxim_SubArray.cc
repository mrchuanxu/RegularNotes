#include <vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 比较sum
        if(nums.size() ==0)return 0;
        int greatSum = 0;
        int nGreatSum = 0x80000000;// 将其设置成足够小，是min_value
        
        for(int i = 0;i<nums.size();i++){
            if(greatSum<=0) greatSum = nums[i];
            else greatSum+=nums[i];
            if(greatSum>nGreatSum) nGreatSum = greatSum;
        }
        return nGreatSum;
    }
};