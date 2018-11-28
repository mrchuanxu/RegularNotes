#include <iostream>
#include <string>

using namespace std;
/***
 * 1 队列，满足动态扩容 O
 * 2 满足数据搬移 O
 * 3 实现出栈，入栈操作 O
 * 4 循环队列实现 ？
 * ***/
template <typename T> class queueUse{
    public:
        queueUse(T *arr,int len):array(arr),length(len),head(arr){}
        T *head;
        T *tail;
        T *array;
        void enqueue(const T& element);
        void dequeue();
        int length;
        int count = 0;
    private:
        queueUse& operator=(const queueUse&);
        queueUse(const queueUse&);
};


template<typename T> void queueUse<T>::enqueue(const T& element){
    if(count < length){
        tail = array++; // 指针往后指 
        *tail = element; // 取得地址，将值存入
        ++count; // 计算长度空间
    }else{
        cout << "queue is full please wait!" << endl;
    }
}

template<typename T> void queueUse<T>::dequeue(){
    if(head == tail){
       cout << "no element" << endl;
       return;
    }
    auto ret = *head;
    *head = NULL;
    ++head;
    --count;
    cout << ret << endl;
}

int main(){
    char qctr[10];
    queueUse<char> quctr(qctr,10);
    string str = "i love";
    for(int i = 0; i<str.size();i++){
        quctr.enqueue(str[i]);
    }
    for(int i = str.size();i >=0; i--){
        quctr.dequeue();
    }
    return 0;
}
