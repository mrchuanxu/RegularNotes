## 进程与线程的应用
上一篇文章主要讲了进程、线程以及协程是什么，这一篇文章我们讲讲进程、线程以及协程的调度方式和通信方式，解决线程死锁的问题(cpp 应用)，多线程安全问题等。要知道这些问题，首先我们先要看到实例，如何创建线程，进程以及如何结束呢？
#### 创建进程
Unix，最近在看unix环境高级编程，fork()是系统调用父进程创建(新)子进程的一个函数，伴随着exec函数，exec会将接下来的代码放入新的存储空间，跑接下来的程序。<br>
看看代码实现
```c
#include "../include/apue.h"
/***
 * 创建子进程date，参数是+%s
 * 相当于在shell中执行date+%s命令
 * 执行date命令
 * ***/
int main(){
    pid_t pid;

    puts("Begin!");

    fflush(NULL);

    pid = fork();

    if(pid<0){
        err_sys("fork error");
        exit(1);
    }
    if(pid == 0){
        execl("/bin/sh","sh","-c","date +%s",NULL);
        err_sys("execl()");
        exit(1);
    }
    wait(NULL);
    puts("END");
    exit(0);
}
```
这个创建了一个system命令。那么fork之后是执行那个程序呢？这个就是看操作系统的调度算法了。<br>
### 阻塞与唤醒
对于一个进程，不依赖于CPU调度，
### 线程与进程通信
### 调度方式
### 死锁
### 线程安全