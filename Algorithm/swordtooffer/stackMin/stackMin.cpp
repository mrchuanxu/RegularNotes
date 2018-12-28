#include <iostream>

/***
 * 利用辅助栈解决
 * 一个数据栈
 * 一个辅助栈
 * 数据栈存储压入元素
 * 辅助栈存储最小元素，不停存储最元素，元素数目与之前的数目一样
 *  ***/
using namespace std;

template <typename T> class Stack{
    public:
        Stack(T *arr):array(arr){}
        void pop();
        void push();
        void min();
    private:
        T *array;
};