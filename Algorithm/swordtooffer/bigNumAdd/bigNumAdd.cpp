/***
 * 打印从1到最大的n位数
 * 考虑n的最大数问题
 * 用字符串模拟加法 考虑进位 声明一个进位的计数值
 * 打印去除0
 * ***/


#include <iostream>

using namespace std;

// 判断加法 改变的是数字，所以传入该指针
bool addBigNumInStr(char *number){
    // 进位
    int overTake = 0;
    // 超出了范围
    bool isOverFlow = false;
    int nLen = strlen(number);
    for(int i = nLen - 1;i>=0;i--){
        int nSum = number[i]-'0'+overTake; // 解决进位
        if(i == nLen-1)   // 不断循环，不断重新加上去 O(n*n)
            nSum++;
        if(nSum>=10){
            if(i==0)
                isOverFlow = true;
            else{
                nSum-=10;
                overTake = 1;
                number[i] = '0'+nSum;
            }
        }else{
            number[i] = '0'+nSum;
            break;
        }
    }
    return isOverFlow;
}

void printNumber(char *number){
    int nLen = strlen(number);
    int i = 0;
    while(number[i]=='0'){
        i++;
    }
    for(;i<nLen;i++){
        cout << number[i];
    }
    cout << endl;
}

void fromOneToN(int n){
    // 考虑边界问题
    if(n<=0){
        return;
    }
    char *number = new char[n+1];
    memset(number,'0',n);
    number[n] = '\0';
    while(!addBigNumInStr(number)){
        printNumber(number);
    }
    delete [] number;
    number = NULL;
}

int main(){
    fromOneToN(0);
    return 0;
}