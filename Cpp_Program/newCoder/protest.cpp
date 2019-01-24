// #include <stdio.h>
// #pragma pack(2)
// struct A{
//   int a;
//   char b;
//   short c;
// };
// #pragma pack()
// #pragma pack(4)
// struct B{
//   char b;
//   int a;
//   short c;
// };

// #pragma pack()

// int main(){
//   float num = 1e+5;
//   printf("sizeof(A) = %d,size(B) = %d \n",sizeof(A),sizeof(B));
//   printf("%f",num);
// }

#include <iostream>
#include <vector>
using namespace std;

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
int main(){
  vector<vector<int> > matrix{{1}};
  vector<int> vec;
  vec = printMatrix(matrix);
  for(auto iter:vec){
      cout << iter << endl;
  }
  return 0;
}
        