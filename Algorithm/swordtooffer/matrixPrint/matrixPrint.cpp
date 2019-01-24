#include <iostream>
#include <vector>
/***
 * 重要是要判断终止条件，这些条件判断打印的循环执行
 * 对比了自己写的方法和offer上的方法，虽然思路大概都是差不多的，凡事offer确实分开了两种方式来做
 * 这个程序的细粒度是有的，可是我只是顺着思路一直走，没有考虑把它拿出来，在循环里继续跑。
 * 其实遇到这些大问题，应该写成小问题来改
 * 一步一步走，这样以后改的时候也方便，所以推荐offer的解法。
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
// 来及牛客的解体
vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> pMResult;
        if(matrix.size() == 0) return pMResult;
        int startCol = 0;
        int startLine = 0;
        int endCol = matrix[0].size()-1;
        int endLine = matrix.size()-1;
        int sumSize = (endCol+1)*(endLine+1);
        while(pMResult.size()<sumSize){
            // 👉
            int i,j,leftCount,upCount;
            for(i = startCol;i<=endCol;++i){
                pMResult.push_back(matrix[startLine][i]);
                if(pMResult.size()==sumSize) return pMResult;
            }
            // 👇
            for(j= startLine+1;j<=endLine;++j){
                pMResult.push_back(matrix[j][endCol]);
                if(pMResult.size()==sumSize) return pMResult;
            }
            --j;
            --i;
            // 👈
            for(leftCount = i-1;leftCount>=startCol;--leftCount){
                pMResult.push_back(matrix[j][leftCount]);
                if(pMResult.size()==sumSize) return pMResult;
            }
            ++leftCount;
            // 👆
            for(upCount = j-1;upCount>startLine;--upCount){
                pMResult.push_back(matrix[upCount][leftCount]);
                if(pMResult.size()==sumSize) return pMResult;
            }
            ++startCol;
            ++startLine;
            --endLine;
            --endCol;
        }
        return pMResult;
        }