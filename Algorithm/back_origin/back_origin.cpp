/***
 * 深度优先
 * 回溯的思想，到了某个分岔路口，不符合期望值就往回走
 * 
 * 8皇后问题
 * 同样是回溯的思想
 * ***/

#include <iostream>
#include <vector>
using namespace std;

// 首先，声明一个row，用来存储皇后
int *row = new int[8]; // 未初始化

bool isOk(int row,int col); // 判断是否可以有
void printQueens(int *row);

void cal8Queens(int rows){ // 先放了一种
    if(rows == 8){
        printQueens(row);
        return;// 查到了最后，返回
    }
    for(int col = 0;col<8;col++){ // 这是回溯的重点
        if(isOk(rows,col)){
            row[rows] = col;
            cal8Queens(rows+1); // 考察下一行 每次都是新的放法
        }
    }// 打印了所有的可能性
    return;
}

bool isOk(int rows,int col){
    int leftup = col-1;
    int rightup = col+1;
    for(int i = rows-1;i>=0;i--){
        if(row[i] == col) return false; // 行与列
        if(leftup>=0){
            if(row[i] == leftup) return false;// 左对角线
        }
        if(rightup < 8){
            if(row[i] == rightup) return false; // 右对角线
        }
        --leftup;
        ++rightup;
    }
    // 检测完没问题，就返回这个行列可以
    return true;
}

void printQueens(int *row){
    // 直接打印就好了
    // 打印一个二维数组
    for(int rows= 0;rows<8;rows++){
        for(int cols = 0;cols<8;cols++){
            if(row[rows] == cols) cout << "Q";
            else cout << "*";
        }
        cout << endl;
    }
    cout << endl;
}

/***
 * 0-1背包问题
 * 搜索剪枝的技巧
 * 当发现物品的重量超过Wkg之后，就停止继续探测剩下的物品
 * cw表示当前已经装进去的物品的重量和；i表示考察到哪个物品了
 * w背包重量；items表示每个物品的重量；n表示物品个数
 * 假设背包可承受重量100，物品个数10，物品重量存储在数组a中，那可以这样调用函数
 * 
 * ***/

int maxW = 100;
int *result = new int[10];
void func(int i,int coutweight,int items[],int n,int w){
    if(coutweight == w||i==n){ // cw == w表示装满了；i==n 表示已经考察完所有物品
        if(coutweight > maxW) maxW = coutweight;
        return;
    }
    func(i+1,coutweight,items,n,w);// 不装 不装的条件是目前countweight已经等于w了
    if(coutweight + items[i]<=w){ // 没超过背包承受的重量，就装 条件是countweight还小
        result[i] = items[i];
        func(i+1,coutweight+items[i],items,n,w);
    }
}
/***
 * 全排列
 * 全排列数字
 * ***/
void Permutation(vector<int>& vec,int start){
    // 判断递归终止条件，判断到vec最后的长度
    if(start == vec.size()){
        for(auto iter:vec){
            cout << iter;
        }
        cout << endl;
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
    return 0;
}
int main(){
    int a[] = {1,2,3,2,1,2,3,4,3,2,1,3,4,2,1,2,3,4,5,3,1,8,9,7,10,22,33};
    func(0,0,a,10,50);
   // cal8Queens(0);
   for(int i = 0;i<10;i++){
       cout << result[i] << endl;
   }
    delete []row;
    delete []result;
    return 0;
}
