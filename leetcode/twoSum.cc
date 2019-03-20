
#include <map>
#include <vector>
using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // vector<int> vec_res;
        // if(nums.size()<=1) return vec_res;
        // // 这是最普通的做法 但是是最省空间的做法 但是最慢
        // for(int i = 0;i<nums.size();i++){
        //     for(int j =i+1;j<nums.size();j++){
        //         if(nums[i]+nums[j] == target){
        //             vec_res.push_back(i);
        //             vec_res.push_back(j);
        //             return vec_res;
        //         }
        //     }
        // }
        // return vec_res;
        // 
        // 这是我一开始的做法，但是我只是没想好怎么处理，如果需要匹配坐标，我觉得只需要坐标就可以了
        map<int,int> map_res;
        // 判断异常处理
        vector<int> vec_res;
        if(nums.size()<=1) return vec_res;
        map<int,int>::iterator map_res_iter;// 这里我省略多次迭代器的运算
        for(int i = 0;i<nums.size();i++){
            int chknum = target-nums[i]; 
            if((map_res_iter = map_res.find(chknum))!=map_res.end()){ 
                // 这里看起来可读性较差，但是还是可读的，易懂的
                // 判断map_res是否存在该key
                int map_res_num = map_res_iter->second;
                vec_res.push_back(map_res_num);
                vec_res.push_back(i);
                return vec_res;
            }
            map_res[nums[i]] = i;
        }
        return vec_res;
    }
};