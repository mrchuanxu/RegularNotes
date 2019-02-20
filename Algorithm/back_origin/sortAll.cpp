/***
 * 全排列
 * 全排列abcdefg
 * ***/

#include <iostream>
#include <vector>
using namespace std;

void Permutation(vector<int>& vec,int start){
    // 判断递归终止条件，判断到vec最后的长度
    if(start == vec.size()){
        for(auto iter:vec){
            cout << iter;
        }
        cout << endl;
       // return;
    }else{
        for(int i = start;i<vec.size();++i){
            swap(vec[start],vec[i]);// 用第一个跟后面的持续交换
            Permutation(vec,start+1);
            swap(vec[start],vec[i]); // 重新将最后一个交换到前面，作起始点
        }
    }
}

int main(){
    vector<int> vec{1,2,3,4};
    Permutation(vec,0);
    for(auto iter:vec){
        iter = 0;
    }
    cout << vec[0] << endl;
    int result = 1;
    result^=1;
    cout << result << endl;
    return 0;
}