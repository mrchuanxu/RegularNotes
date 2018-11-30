#include <iostream>
#include <string>

using namespace std;
/***
 * 1 队列，满足动态扩容 O
 * 2 满足数据搬移 O
 * 3 实现出栈，入栈操作 O
 * 4 循环队列实现 0
 * ***/
template <typename T> class queueUse{
    public:
        queueUse(T *arr,int len):array(arr),length(len),head(arr),tail(arr){}
        T *head;
        T *tail;
        T *array;
        bool enqueue(const T& element);
        bool dequeue();
        bool cir_enqueue(const T& element);
        bool cir_dequeue();
        int length;
        int counthead = 0;
        int count = 0;
    private:
        queueUse& operator=(const queueUse&);
        queueUse(const queueUse&);
};
// 循环队列，其实只是处理入队和出队 队满，head和tail的指向问题的问题
template<typename T> bool queueUse<T>::cir_enqueue(const T& element){
    if(tail+sizeof(T) == head){ // 始终有一个空的tail指向
        cout << "queue is full" << endl;
        return false;
    }
    *tail = element;
    ++count;
    tail = array+((count)%length)*sizeof(T); // tail往后延伸，但是得求余获得位置，一般求余后得到的是一个循环
    return true;
}

template<typename T> bool queueUse<T>::cir_dequeue(){
    if(head == tail){
        cout << "queue is empty" << endl;
        return false;
    }
    cout << *head << endl;
    *head = NULL;
    ++counthead;
    ++head;
    if(counthead == length){ // 因为head一直都是按顺序指向下一个，所以一直都是结束后从0开始出队列
        head = array;
        counthead = 0;
    }
    return true;
}
// 普通队列
template<typename T> bool queueUse<T>::enqueue(const T& element){
    if(tail == (array+(length-1)*sizeof(T))){ // 队列被插到最后，重新搬移数据
        if(head == array){
            cout << "queue is full!" << endl;
            return false;
        }
        int lochead = length-count; // 完成数据搬移
        for(int i = lochead;i<length;++i){
            auto currarr = array+(i-lochead)*sizeof(T); // 数据搬移操作
            *currarr = *(array+i*sizeof(T));
        }
        tail = array+(count-1)*sizeof(T);
        head = array;
    }
    *tail = element;
    ++tail;
    ++count;
    return true;
}

template<typename T> bool queueUse<T>::dequeue(){
    if(head == tail){
        cout << *head << endl;
        head = array;
        tail = array;
        cout << "queue empty now!" << endl;
        return false;
    }
    auto ret = *head;
    *head = NULL;
    ++head;
    --count;
    cout << ret << endl;
    return true;
}

int main(){
    char qctr[10];
    queueUse<char> quctr(qctr,10);
    string str = "i love u";
    int i = 0;
    while(quctr.cir_enqueue(str[i])&&str[i]){
        ++i;
    }
    i=0;
    quctr.cir_dequeue();
    quctr.cir_dequeue();
    quctr.cir_dequeue();
    string str1 = "fuck you man";
    while(quctr.cir_enqueue(str1[i])&&str1[i]){
        ++i;
    }
    while(quctr.cir_dequeue());
    return 0;
}
