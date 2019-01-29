#include <iostream>

/***
 * 模式串匹配
 * 通过好前缀和坏字符
 * 最长可匹配后缀子串
 * 最长可匹配前缀子串
 * 
 * ***/
int* getNexts(char b[],int m);
// a，b分别是主串和模式串；n，m分别是主串和模式串的长度
int kmp(char a[],int n,char b[],int m){
    int* next = getNexts(b,m);
    int j = 0;
    for(int i = 0;i<n;++i){
        while(j>0&&a[i]!=b[j]){ // 寻找坏字符
            j = next[j-1]+1;
        }
        if(a[i] == b[j]){
            ++j;
        }
        if(j == m){ // 找到匹配的模式串
            return i-m+1;
        }
    }
    return -1;
}

// 失效函数 next数组
int* getNexts(char b[],int m){
    int *next = new int[m];
    next[0] = -1;
    int k = -1;
    for(int i = 1;i<m;++i){
        while(k!=-1&&b[k+1]!=b[i]){
            k = next[k];
        }
        if(b[k+1] == b[i]){
            ++k;
        }
        next[i] = k;
    }
    return next;
}