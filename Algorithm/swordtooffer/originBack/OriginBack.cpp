#include <iostream>
#include <string>

using namespace std;
/***
 * 回溯法 
 * 设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径
 * 路径只可上下左右，没有回头路
 * 例如 bcfe
 * a  /b/  t  g
 * c  /f/ /c/ s
 * j   d  /e/ h
 * ***/
// 一个函数

//解决子问题先
bool hasPath(const char *martix, int row, int rows, int col, int cols, int &ptrlength, char *str, bool *visited)
{
    if (str[ptrlength] == '\0')
        return true;
    bool haspath = false;
    if (str[ptrlength] == martix[row * cols + col] && row < rows && col < cols && row > 0 && col > 0 && !visited[row * cols + col])
    {
        ++ptrlength;
        visited[row * cols + col] = true;
        haspath = hasPath(martix, row + 1, rows, col, cols, ptrlength, str, visited) || hasPath(martix, row - 1, rows, col, cols, ptrlength, str, visited) || hasPath(martix, row, rows, col + 1, cols, ptrlength, str, visited) || hasPath(martix, row, rows, col - 1, cols, ptrlength, str, visited);
        if (!haspath)
        {
            --ptrlength;
            visited[row * rows + col] = false;
        }
    }
    return haspath;
}

bool hasStr(char *martix, int rows, int cols, char *str)
{
    if (str == NULL || martix == NULL)
        return false;
    bool *visited = new bool[rows * cols];
    memset(visited, 0, rows * cols);
    int ptrlength = 0;
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (hasPath(martix, row, rows, col, cols, ptrlength, str, visited))
            {
                return true;
            }
        }
    }
    delete[] visited;
    return false;
}
/***
 * 回溯法
 * 解决机器人运动问题
 * ***/
int getDigNum(int num){
    int sum = 0;
    while(num>0){
    sum += num%10;
    num /= 10;
    }
    return sum;
}

bool check(int k,int row, int rows,int col,int cols,bool *visited){
    if(row>0&&col>0&&col<cols&&row<rows&&!visited[row*cols+col]&&(getDigNum(row)+getDigNum(col)) == k) {
        return true;
    }else{
        return false;
    }
}

// 解决子问题
int movingCountCore(int k,int row, int rows,int col,int cols,bool *visited){
    int count = 0;
    if(check(k,rows,row,cols,col,visited)){
        count = 1+movingCountCore(k,row+1,rows,col,cols,visited)+movingCountCore(k,row-1,rows,col,cols,visited)||movingCountCore(k,row,rows,col+1,cols,visited)||movingCountCore(k,row,rows,col-1,cols,visited);
    }
    return count;
}

int movingCountRoboot(int *martix,int rows,int cols,int k){
      if(k<0&&martix==NULL)
          return 0;
      bool *visited = new bool[rows*cols];
      memset(visited,0,rows*cols);
      int sum =  movingCountCore(k,0,rows,0,cols,visited);
      delete [] visited;
      return sum;
}
