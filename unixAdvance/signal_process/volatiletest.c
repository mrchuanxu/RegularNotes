#include <stdio.h>

volatile int n = 1;
// 当要求使用volatile声明变量时，系统总是重新从它坐在的内存读取数据，即使它
// 前面的指令刚刚从该处读取过数据
// 

int main(){

    return 0;
}