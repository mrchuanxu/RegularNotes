#include <iostream>

/***
 * 重要是要判断终止条件，这些条件判断打印的循环执行
 * ***/
using namespace std;
void printMatrix(int **number,int columns,int rows,int start){
    // 第一步，从左到右
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;
    for(int i = start;i<endX;i++){
        cout << number[start][i] << endl;
    }
    // 第二步从上到下 这里的终止条件是start>endY
    if(start<endY){
        for(int j = start+1;j<endY;j++){
            cout << number[j][endX] << endl;
        }
    }
    // 第三步 从右到左
    if(start<endX&&start<endY){
        for(int rl = endX-1;rl>=start;--rl){
            cout << number[endY][rl] << endl;
        }
    }
    // 第四步 从下到上
    if(start<endX&&endY-start>1){
        for(int downUp = endY-1;downUp>=start;--downUp){
            cout << number[downUp][start] << endl;
        }
    }
}

void martixEnter(int **number,int columns,int rows){
    if(number ==nullptr||columns<=0||rows<=0)
        return;
    int start = 0;
    while(columns>start*2&&rows>start*2){
        printMatrix(number,columns,rows,start);
        ++start;
    }
}