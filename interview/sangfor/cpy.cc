/**
 * 记一次深信服面试
 * 这次面试其实很考基础
 * 多线程
 * 死锁
 * cpy函数实现
 * 消费者生产者
 * ***/


#include <iostream>
using namespace std;
char *strcoy(char *dest,const char* src){
    assert(dest!=NULL&&src!=NULL);
    char *ret = dest;
    while((*dest++=*src++)!='\0'); // 遇到‘\0’就结束，其实还是蛮简单的一个指针操作 太紧张了！
    return ret;
}

// 要是发生了内存重叠，怎么办？
// 什么是内存重叠？内存重叠就会崩溃
// 尝试修改
void* my_memcoy(void *dest,const void *src,unsigned int count);
char *my_strcoy(char *dest,const char* src){
    assert(dest!=NULL&&src!=NULL);
    char *ret = dest;
    my_memcoy(dest,src,strlen(src)+1);
    return ret;
}
// 尝试内存重叠修改
void* my_memcoy(void *dest,const void *src,unsigned int count){
    assert(dest!=NULL&&src!=NULL);
    void *ret = dest;
    // 正常 内存从低地址开始复制
    if(dest<=src||(char*)dest>=((char*)src+count)){
        while(count--){
            *(char*)dest = *(char*)src;
            dest = (char*)dest+1;
            src = (char*)src+1;
        }
    }else{ // 内存重叠 从高地址开始复制
        dest = (char*)dest+count-1;
        src = (char*)src+count-1;
        while(count--){
            *(char*)dest = *(char*)src;
            dest = (char*)dest-1;
            src = (char*)src-1;
        }
    }
    return ret;

}
class Animal{
    public:
    Animal(){
        cout << "I am Animal" << endl;
    }
    virtual void run();
    virtual void call();
    virtual void action();
    virtual ~Animal(){
        cout << "delete Animal" << endl;
    }
};


class Dog:public Animal{
    public:
    Dog(){
        cout << "I am Dog"<<endl;
    }
    virtual void action();
    virtual void call();
    virtual void run();
    virtual ~Dog(){
        cout << "Delete Dog" << endl;
    }
};

void Animal::action(){
    cout  << "hi Animal" << endl;
}

void Animal::run(){
    cout << "one step" << endl;
}

void Animal::call(){
    cout << "moximoxi" << endl;
}

void Dog::action(){
    cout << "hi Dog"<<endl;
}
void Dog::call(){
    cout << "hi Dog call"<<endl;
}
void Dog::run(){
    cout << "Dog run" << endl;
}
int main(){
    // char src[10] = "hello";
    // char *dest = (char*)malloc(10);
    // dest = my_strcoy(src+1,src);
    // printf("%s\n",src);
    Animal *dog = new Animal();
    dog->action();
    delete dog;

    return 0;
}

