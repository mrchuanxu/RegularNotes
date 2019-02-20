#include <iostream>
#include <vector>

using namespace std;

static int vec_res[8]; // 下标代表行，值代表列

void printQueens(int vec[]){
    for(int i = 0;i<8;i++){
        for(int j = 0;j<8;j++){
            if(vec[i] == j) cout << "Q";
            else cout << "*";
        }
        cout << endl;
    }
    cout << endl;
}
// 8皇后问题，首先分解子问题，判断这个行这个列是否可以存储
bool isOk(int row,int column){
    // 判断左上角与右上角是否可以存储
    int leftup = column-1;
    int rightup = column+1;
    // 然后逐行网上判断
    for(int i = row-1;i>=0;--i){
        if(vec_res[i] == column) return false; // 存在了这个棋子♟
        if(leftup>=0){
            if(vec_res[i] == leftup) return false; // 左上角存在棋子♟
        }
        if(rightup<8){ // 8皇后，就判断8个列
            if(vec_res[i] == rightup) return false; // 右上角存在棋子♟
        }
        --leftup;
        ++rightup;
    }
    return true; // 都没有这个行或者这个列就判断是正确的，可以的
}

// 然后就要计算这个到底有多少种摆法
void calEightQueens(int row){
    // 首先，因为递归，所以找终止条件
    if(row == 8){ // 摆完了，就可以了
        printQueens(vec_res);
        return;
    }
    // 这里是回溯的重点
    for(int column = 0;column<8;++column){ // 遍历8个列
        if(isOk(row,column)){ // 判断这个行列能否放
            vec_res[row] = column; // 加入值
            calEightQueens(row+1); // 考察下一行
        } 
    }
}

int main(){
    calEightQueens(0);
    return 0;
}