
/***
 * 解决杨辉三角问题
 * 数字特征是
 * 5
 * 7,8
 * 2,3,4
 * 4,9,6,1
 * 2,7,9,4,5
 * 
 * nums[i][j]只能到达
 * nums[i+1][j]或nums[i+1][j+1]
 * 
 * 每次访问就将值加上
 * 要么访问nums[i+1][j]
 * 要么访问nums[i+1][j+1]
 * 最后的值一定是最小的
 * 
 * 终止条件是到达了最尾部
 * ***/


#include <iostream>
#include <vector>

using namespace std;

// 回溯暴力解决 都走一遍
static int minDist = 100; // 随便定义一个最大值
vector<vector<int> > nums_tri{{5},{7,8},{2,3,4},{4,1,6,1},{2,1,9,4,5}};

void triangle_shorter(int rows,int columns,int min_dist,vector<vector<int> >&nums){
    if(rows==nums.size()){
        if(min_dist<minDist) minDist = min_dist;
        return;
    }
    // 备忘录
    // if(minDistRecord[rows][columns]>0) return;
    // minDistRecord[rows][columns] = min_dist;
    if(rows<nums.size()){
        triangle_shorter(rows+1,columns,min_dist+nums[rows][columns],nums);
        triangle_shorter(rows+1,columns+1,min_dist+nums[rows][columns],nums);
    }
}
// 以上是暴力回溯的求解方法

// 动态规划
int dy_tripro(vector<vector<int> >& nums){
    int len = nums.size();
    int col = nums[len-1].size();
    int min_dist[len][col];
    // 将里面的值都设置为0
    for(int i = 0;i<len;i++){
        for(int j = 0;j<col;j++){
            min_dist[i][j] = 0;
        }
    }
    int sum = 0;
    for(int i = 0;i<len;++i){
        sum+=nums[i][0]; // 初始化第一列
        min_dist[i][0] = sum;
    }

    for(int i = 1;i<len;++i){
        for(int j = 1;j<nums[i].size();++j){
            if(min_dist[i-1][j]>0){
                // 递归公式，也是动态规划的重点
                min_dist[i][j] = nums[i][j]+min(min_dist[i-1][j],min_dist[i-1][j-1]);
            }else{
                // 三角有一部分是空的。所以直接加上左上角
                min_dist[i][j] = nums[i][j]+min_dist[i-1][j-1];
            }
        }
    }
    int result = min_dist[len-1][0];
    for(int i = 0;i<col;i++){
        if(min_dist[len-1][i]<result) result = min_dist[len-1][i];
    }
    return result;
}

int main(){
    triangle_shorter(0,0,0,nums_tri);
    cout << minDist << endl;
    int result = dy_tripro(nums_tri);
    cout << result << endl;
    return 0;
}