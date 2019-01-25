## 进程控制
上一篇文章，我讲述了整个进程的环境，包括环境变量，工作路径，申请空间，进程跑的退出函数，跳转函数以及ulimit限制用户。这次，我们围绕fork,exec,wait这三个函数进行讨论，unix系统是如何管理进程的。<br>
一般查看进程，unix用的是ps命令。而ps命令又有很多参数，主要还是查看man手册，终端💻输入man ps就可以查看详细的命令参数。
* ps -axf 主要查看当前系统进程中的PID以及执行终端的tty和状态信息，更重要是，它能显示出进程的父子关系
* ps -axj 主要用于查看当前系统中进程的PPID、PID、PGID、SID、TTY等信息
* ps -axm 显示进程的详细信息，PID列下面的减号(-)是显示这个进程中的线程
* ps ax -L以Linux的形式显示当前系统中的进程列表
PID是系统中进程的唯一标志，在系统中使用pid_t的类型表示，它是一个非负整型。<br>
#### 1号init进程
所有进程的祖先进程(但不一定是父进程)，内核启动后会启动init进程，然后内核就会像一个库一样守在后台等待出现异常情况的时候再出来处理一下，其他的事情都由init进程创建子进程来完成。(嗯，😄很像一个长者，只有有问题才出来说一下，没问题就守在后台，闭关修炼，像马爸爸一样)<br>
Unix系统使用延迟复用的算法，使得赋予新建进程的ID不同于最近终止进程所使用的ID，说白了，就是不断地往后申请新ID，到了最后再回来往前申请，一个循环队列咯。<br>
#### getpid、getppid、getuid、geteuid、getgid、getegid
```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void); // 获取当前进程ID
pid_t getppid(void); // 调用进程的父进程ID
uid_t getuid(void); // 调用进程的实际用户ID
uid_t geteuid(void); // 调用进程的有效用户ID
gid_t getgid(void); // 调用进程的实际组ID
git_t getegid(void); // 调用进程的有效组ID
```
### fork,you are neo!
```c
fork - create a child process
#include <unistd.h>
pid_t fork(void);
```
fork函数的作用，就是创建子进程。返回两个ID，子进程里返回0，父进程返回新建子进程ID。<br>
调用fork，创建子进程的时候，刚开始父子进程是一摸一样的，就连代码执行到的位置都是一毛一样的，这就是将父进程的资源，以及执行的位置都赋值一遍给了子进程。<br>
子进程要想获得父进程的PID就需要调用getppid函数，getpp。<br>
一般来说，调用fork后会执行if(依赖fork的返回值)分支语句，用来区分下面的代码，哪些代码由父进程执行，哪些代码由子进程执行。<br>
![fork_cow](./img/fork.png)<br>
vfork实现父子进程共享一块数据空间，解决，创建子进程的时候不必担心赋值数据耗费的资源较高的问题。可是，这个函数已经过时了，没人用了，聪明是很聪明，但是对不起，系统不需要<br>
fork技术的改良，写时拷贝技术。
#### 写时拷贝技术(Copy_On_Write COW)
fork函数刚刚创建子进程的时候，父子进程的数据 **指向同一块物理内存！** 指向同一块物理内存！指向同一块物理内存！重要的事情说三遍！但是，内核将这些内核的访问变为 **只读的**了，当父子进程中的任何一个想要修改数据的时候，内核就会为修改区域的那块内存制作一个副本，并将自己的 **虚拟地址映射到物理地址的指向** 修改为副本的地址，从此父子进程自己完自己的，谁也不影响谁，效率就提高了。新分配的副本大小通常是虚拟存储系统中的一页。<br>
当然，COW技术中所谓的副本，是在物理地址中制作的，并非我们在程序中拿到的那个指针所指向的地址，我们的指针所指向的地址其实是虚拟地址，所以这些动作对于用户态的程序员是透明的，不需要我们自己进行管理，内核会自动为我们打点好一切。<br>
看个🌰吧
```c
#include "../include/apue.h"
/***
 * 子进程对变量所做的改变并不影响父进程中该变量
 * 0 调度进程 交换进程 新进程创建ID不可能是0 所以可以返回 0
 * 1 init进程
 * 2 页守护进程
 * pid_t fork(void); // fork新进程 子进程返回 0，父进程返回子进程🆔
 * 子进程是父进程的副本，子进程获得父进程数据空间、堆和栈的副本。子进程所拥有的副本！父进程和子进程并不共享这些存储空间部分。
 * 父进程和子进程共享正文段
 * fork后跟着exec
 * ***/
int globvar = 6;
char buf[] = "a write to stdout;\n"; // buf改变变量
int subProcess(int a){
    a+=a;
    return a;
}
int main(void){
    int var;
    pid_t pid; // 进程pid

    var = 88;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1) // 输出
        err_sys("write error!");
    printf("before fork\n"); // before fork
    //printf("pid=%ld,glob=%d,vr=%d\n",(long)geteuid(),globvar,var); 
    pid = fork(); // fork之后，将会有两个进程在跑，一个是父进程在跑，一个是子进程在跑 fork之后就是两个程序在跑了！
    if(pid<0) // 0 调度进程 交换进程
        err_sys("fork error");
    else if(pid==0){
        printf("i am subProcess and i will add globvar 1\n");
        //printf("pid=%ld,glob=%d,vr=%d\n",(long)getppid(),globvar,var);
        printf("a=%d\n",subProcess(10));
        globvar++;
        var++;
    }else{
        sleep(2);
        //printf("a=%d\n",subProcess(420)); // 可以等待其他请求
        //printf("i am Process and i sleep\n");
    }
    int i = printf("pid=%ld,glob=%d,vr=%d\n",(long)getpid(),globvar,var); 
    printf("i=%d\n",i);
    //printf("pid=%ld,glob=%d,vr=%d\n",(long)getppid(),globvar,var); 
    exit(0);
}
```
上面这个🌰就说明了，其实，父子进程修改变量，子进程修改变量其实不修改父进程的变量，没有关系的。而且，父子进程，谁先运行不确定的，是由进程调度器决定的。<br>
但是vfork会保证子进程先执行。进程调度器不是一个工具，是在内核中的一块代码。<br>
也可以输出到文件<br>
`a.out>result.txt`,但是cat result.txt的时候就会出现
```
a write to stdout;
before fork
i am subProcess and i will add globvar 1
a=20
pid=1452,glob=7,vr=89
i=22
before fork
pid=1451,glob=6,vr=88
i=22
```
输出了两次beforefork，OMG，其实这是因为行缓冲变成了全缓冲导致的。标准输出是行缓冲，而系统默认的是全缓冲模式。所以当我们将它输出到控制台的时候可以的到预期的结果的，但是一旦重定向到文件的时候就由行缓冲变成全缓冲模式，而子进程产生的时候是会复制父进程的缓冲区的数据的，所以子进程刷新缓冲区的时候子进程也会将从父进程缓冲区中复制到的内容刷新出来。因此， **在使用 fork(2) 产生子进程之前一定要使用 fflush(NULL) 刷新所有缓冲区！**<br>
[全缓冲与行缓冲的定义](https://github.com/Vitomy/RegularNotes/blob/master/unixAdvance/APUE-STDIO.md#%E5%85%A8%E7%BC%93%E5%86%B2)<br>
那如果我fflush了呢？会怎么样<br>
```
a write to stdout;
before fork
before fork
i am subProcess and i will add globvar 1
a=20
pid=1521,glob=7,vr=89
i=22
pid=1520,glob=6,vr=88
i=22
```
同理，将会即时冲到缓冲区，然后输出，这时候，这时候就不会影响到子进程的输出了。<br>
咦❓这是一个特别有意思的问题，为什么，程序运行时，子程序输出的结果是在当前的shell而不是新打开一个shell呢？<br>
因为复制父进程的所有东西嘛。其实包括了文件描述符，就像执行了dup函数一样，父子进程每个相同的打开文件描述符共享一个文件表项。既然是复制了父进程的文件描述符，若父进程在创建子进程之前关闭了三个标准的文件描述符，那么子进程也就没有这三个文件描述符可以使用了，也就不会输出到shell了。<br>
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
    pid_t pid;
    int i = 0;
    for(i = 0;i<10;i++){
        fflush(NULL);
        pid = fork();
        if(pid<0){
            perror("fork() error");
            exit(1);
        }else if(0==pid){
            printf("pid = %d\n",getpid());
            exit(0);
        }
    }
    sleep(100);
    return 0;
}
```
这里的子进程先结束，变成了僵尸进程，要等父进程“收尸”。白头人送黑头人。而父进程正在睡觉😪<br>
如果父进程先死了，子进程成为孤儿进程就会找马爸爸做爸爸，也就是1号的init进程，当这些子进程运行结束时，就会变成僵尸进程，然后1👌init进程就会及时收尸☠️<br>
##### 其实🧟‍♀️僵尸进程不会占用大量的资源
他们在内核中仅仅保留一个结构体，也就是自身的状态信息，其他的资源都会释放。但是会占用一个重要的系统资源就是PID，因为系统中的PID的数量是有限的，所以需要及时收尸☠️<br>
### wait 阻塞等待子进程资源的释放，相当于收尸☠️
