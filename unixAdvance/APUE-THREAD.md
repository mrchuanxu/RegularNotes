## 线程(终于到了线程)
本章节主要讲述线程的创建、取消、终止、同步等。后面的操作系统会主要讲线程死锁，调度等关系<br>
实际项目中多线程会用得比较多，因为多线程是 **先有标准后有实现的**，所以不会像多进程那样在不同的平台上有许多不同的情况<br>
#### pthread_t 线程就是一个正在运行的函数
C语言线程有很多标准，POSIX就是其中的一种，POSIX是一套标准，而不是一种实现。<br>
正因为POSIX是一套标准而不是实现，所以POSIX只是规定了 **pthread_t作为线程标识符**，并没有规定它必须是由什么类型组成的。所以在有的平台上他可能是int，有些平台他可能是struct(例如linux)，还有些平台可能是union，所以不要直接操作这个类型，而是要 **使用POSIX规定的各种线程函数来操作它。**<br>
###### 标准的风格
标准制定出来的很多东西都是一种风格，它为你提供一个数据类型，但是不会让你直接对这个类型进行操作，要通过它定义的一系列函数来实现对这个类型的操作，这样就在各个平台上实现统一的接口了，所以这样做才能让标准制定出来的东西具有比较好的可移植性。**玩游戏🎮就要遵循游戏规则，大家都一个标准才有玩的意思**<br>
##### ps ax -l 查看线程的情况 方便调试程序
```c
$ ps ax -L
PID   LWP TTY      STAT   TIME COMMAND
877   877 ?      Ss     0:06 dbus-daemon --system --fork
```
LWP是在linux可以查看得到的线程标识。在mac就不能用这个命令查看了。<br>
PID是进程号，而LWP是线程ID。PID相同，LWP不同，代表PID有不同的几个线程。<br>
线程ID只有在他所属的进程才有意义。<br>
### pthread_equal 比较线程标识符是否相同 pthread_self获取当前线程ID
```c
pthread_equal - compare thread IDs

#include <pthread.h>

int pthread_equal(pthread_t t1, pthread_t t2);

Compile and link with -pthread.

pthread_self - obtain ID of the calling thread

#include <pthread.h>

pthread_t pthread_self(void); // 获取当前线程ID

Compile and link with -pthread.
```
这两个函数一起使用的🌰，主线程可能把工作任务放在一个队列中，用线程ID来控制每个工作线程处理哪些作业。主线程把新的作业放到一个工作队列中，由3个工作线程组成的线程池从队列中移出作业。主线程不允许每个线程任意处理从队列顶端取出的作业，而是由主线程控制作业的分配，主线程会在每个待处理作业的结构中放置处理该作业的线程ID，每个工作线程只能移出标有自己线程ID的作业。<br>
![工作队列实例](./img/workqueue.png "工作队列实例")<br>
### pthread_create 线程的创建
```c
pthread_create - create a new thread

#include <pthread.h>

int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void*(*start_routine)(void*),void *arg);
Compile and link with -pthread
```
* thread: 由函数回填的线程标识符，它来唯一的标识产生的新线程，后面我们只要需要操作新线程就需要用到它
* attr: 线程属性，所有的属性都是使用NULL，也就是使用默认属性
* start_routine: 线程的执行函数；参数是void*，返回值是void*。座椅可以使用任何类型
* arg: 传递给start_routine的void*参数<br>
返回，成功返回0，失败返回errno。为什么会返回errno？因为一些平台error是全局变量，如果大家都使用同一个全局变量，那么多线程下就会出现竞争的可能，所以POSIX的线程函数一般在失败的时候都是直接返回errno的，这样就避免了某些平台errno的缺陷。<br>
**新线程和当前线程是两个兄弟线程，平等的，没有父子关系**<br>
新线程被创建后，两个线程的执行顺序是不确定的，由调度器决定。如果你希望哪个线程一定先执行，那么就在其他线程中使用类似sleep的函数，让它们等等。<br>
### pthread_exit 退出当前线程
```c
pthread_exit - terminate calling thread

#include <pthread.h>

void pthread_exit(void *retval);

Compile and link with -pthread.
```
在线程执行函数中调用，作用是退出当前线程，并将返回值通过retval参数返回给调用pthread_join函数(为线程收尸的函数)的地方，如果不需要返回值可以传入NULL<br>
看一个上面函数一起使用的🌰，其实好像并没有体现多线程的使用，而只是体现一个函数的调用<br>
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static void *func(void *p){
    puts("Thread is working.");
    sleep(10);
    pthread_exit(NULL); // 返回
}

int main(){
    pthread_t tid;
    int err;
    puts("Begin!");

    err =  pthread_create(&tid,NULL,func,NULL);
    // 失败就设置errno
    err =  pthread_create(&tid,NULL,func,NULL);
    if(err){
        fprintf(stderr,"pthread create():%s\n",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL); // 最后要为线程收尸
    puts("End!");
    exit(0);
}
```
那么我们再来看一个🌰，这个🌰比较清晰的表现了主线程和新线程。
```c
#include <pthread.h>
#include <string.h>
#include "../include/apue.h"


pthread_t ntid;

void printids(const char *s){
    pid_t pid;
    pthread_t tid;

    pid = getpid(); // 获得当前进程id
    tid = pthread_self();
    printf("%s pid %lu tid %lu(0x%lx)\n",s,(unsigned long)pid,
    (unsigned long)tid,(unsigned long)tid);
}

void* thr_fn(void *arg){
    printids("new thread:"); // 这里打印新线程
    return((void *)0);
}

int main(void){
    int err;
    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(err!=0)
        err_exit(err,"can't create thread");
    printids("main thread:");// 这里打印主线程
    sleep(1); // 不知道哪个先调用，就让主线程先睡觉
    exit(0);
}
```
新线程通过调用pthread_self函数获取自己的线程ID的，而不是从共享内存中读出的，或者从线程的启动例程以参数的形式接收到的。<br>
```c
main thread: pid 1328 tid 4474140096(0x10aadf5c0)
new thread: pid 1328 tid 123145419599872(0x700006fdb000)
```
返回的是16进制，像是一个地址，像是使用指向线程的数据结构的指针作为它的线程ID。<br>
### 线程终止pthread_exit pthread_join(线程之间谁都可以为别人收尸)
如果进程中的任意线程调用了exit、_Exit或者_exit，那么整个进程就睡终止。如果默认动作是终止进程，那么发送到线程的信号就会终止整个进程<br>
单个线程可以通过三种方式退出，因此可以在不终止整个进程的情况下，停止它的控制流
* 线程可以简单地从启动例程中返回，返回值是线程的退出码
* 线程可以被同一进程中的其他线程取消
* 线程可以屌用pthread_exit
```c
#include <pthread.h>
void pthread_exit(void *rval_ptr);
// rval_ptr参数是一个无类型指针，与传给启动例程的单个参数类似。进程中的其他线程也可以通过屌用pthread_join函数访问这个指针
int pthread_join(pthread_t thread,void **rval_ptr);
// 自动把线程置于分离状态，如果已分离，调用就会失败，返回EINVAL
```
调用线程将一直阻塞，直到指定的线程调用pthread_exit、从启动例程中返回或者被取消。如果线程简单地从它的启动例程返回，rval_ptr就包含返回码。如果线程被取消，由rval_ptr指定的内存单元就设置为PTHREAD_CANCELED。<br>
如果不感兴趣返回值，就设置为NULL。**pthread_join等待指定线程终止，但并不获取线程的终止状态**<br>
```c
#include "../include/apue.h"
#include <pthread.h>

void* thr_fn1(void *arg){
    printf("thread 1 returning\n");
    return ((void*)1);
}

void* thr_fn2(void *arg){
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

int main(void){
    int err;
    pthread_t tid1,tid2; // 创建两个线程
    void *tret;

    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 1");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 2");
    err = pthread_join(tid1,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 1");
    printf("thread 1 exit code %ld\n",(long)tret);
    // 线程结束返回码
    err = pthread_join(tid2,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 2");
    printf("thread 2 exit code %ld\n",(long)tret);
    exit(0);
}
```
获取线程终止返回码。无类型单数，可以传递包含复杂信息的结构的地址。这个复杂的信息结构所使用的内存在调用者完成调用后必须保持有效的。<br>
### pthread_cancel 取消同一个进程中的其他线程的线程
为什么要取消线程？当一个线程没有必要继续执行下去，又没法收尸，所以就需要先取消这个线程，然后再为它收尸。<br>
```c
pthread_cancel - send a cancellation request to a thread

#include <pthread.h>

int pthread_cancel(pthread_t thread);
Compile and link with -pthread
```
例如要用多线程遍历一棵很大的二叉树查找一个数据，其中某一个线程找到了要查找的数据，那么其他线程就没必要继续了，可以取消它们了。<br>
**⚠️pthread_cancel并不等待线程终止，它仅仅提出请求**，而线程收到这个请求也不会立即终止，而是要执行到 **取消点**才被取消。<br>
### 线程清理处理程序 pthread_cleanup_push and pthread_cleanup_pop
```c
pthread_cleanup_push,pthread_cleanup_pop - push and pop thread cancellation clean-up handlers

#include <pthread.h>

void pthread_cleanup_push(void (*routine)(void *),void *arg);
// routine是钩子函数 arg传递给钩子函数的参数
void pthread_cleanup_pop(int execute);
// execute 0不调用该钩子函数，1调用钩子函数
Compile and link with -pthread
```
就像在进程级别使用atexit函数挂钩子函数一样，线程可能也需要在结束时执行一些清理工作，这时候就需要派生线程处理程序上场了。钩子函数的调用顺序也是逆序的，也就是执行顺序与注册顺序相反。(类似入栈)<br>
⚠️这两个是带参的宏而不是函数，所以必须成对使用，而且必须先使用pthread_cleanup_push再使用pop。<br>
使用的🌰
```c
#include "../include/apue.h"
#include <pthread.h>

void cleanup(void *arg){
    printf("clean up:%s\n",(char *)arg);
}

void* thr_fn1(void *arg){
    printf("thread 1 returning\n");
    pthread_cleanup_push(cleanup,"thread 1 first handler");
    pthread_cleanup_push(cleanup,"thread 1 second handler");
    printf("thread 1 push complete");
    if(arg)
        return((void*)1);
    pthread_cleanup_pop(1);// 成对出现
    pthread_cleanup_pop(1);
    return ((void*)1);
}

void* thr_fn2(void *arg){
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup,"thread 2 first handler");
    pthread_cleanup_push(cleanup,"thread 2 second handler")
    printf("thread 2 push complete\n");
    if(arg)
        pthread_exit((void *)2);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void *)2);
}

int main(void){
    int err;
    pthread_t tid1,tid2; // 创建两个线程
    void *tret;

    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 1");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err!=0)
        err_exit(err,"can't create thread 2");
    err = pthread_join(tid1,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 1");
    printf("thread 1 exit code %ld\n",(long)tret);
    // 线程结束返回码
    err = pthread_join(tid2,&tret);
    if(err != 0)
        err_exit(err,"can't join with thread 2");
    printf("thread 2 exit code %ld\n",(long)tret);
    exit(0);
}
```
线程在退出时调用该退出函数。<br>

### pthread_detach分离线程，被分离的线程是不能被收尸的
```c
pthread_detach - detach a thread

#include <pthread.h>

int pthread_detach(pthread_t thread);

Compile and link with -pthread.
```

### 互斥量(pthread_mutex_t) 解决竞争
多线程就是为了充分利用硬件资源，使程序可以并发的运行，但是只要是并发就会遇到竞争问题。互斥量就是为了解决竞争的多种手段之一。<br>
💭考虑一个问题，如何让20个线程同时从一个文件中读取数字。累加1，然后再写入回去，并保证程序运行后，文件中的数值比运行程序之前大20.<br>
```c
#include "../include/apue.h"
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#define BUFSIZE 32

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 互斥量

static void *fun(void *p){
    int fd = -1;
    long long n = 0;
    char buf[BUFSIZE] = "";
    fd = open(p,O_RDWR|O_CREAT,0664);
    pthread_mutex_lock(&mutex); // 锁住互斥量
    printf("only one thread work!\n");
    read(fd,buf,BUFSIZE); // 读取
    lseek(fd,0,SEEK_SET); // 设置偏移量
    n = atoll(buf);
    snprintf(buf,BUFSIZE,"%lld\n",++n);// ➕1操作
    write(fd,buf,strlen(buf));

    close(fd);

    pthread_mutex_unlock(&mutex); // 解锁🔓资源
    pthread_exit(NULL); // 线程读完退出
}

int main(int argc,char **argv){
    int err;
    pthread_t tids[20];
    int i = 0;
    if(argc < 2){
        fprintf(stderr,"Usage %s<filename>\n",argv[0]);
        return -1;
    }
    for(i = 0;i<20;i++){
        err = pthread_create(&tids[i],NULL,fun,argv[1]);
        printf("pthread %d\n",i);
        if(err)
            err_exit(err,"create() error");
    }
    for(i = 0;i<20;i++){
        pthread_join(tids[i],NULL);
    }

    pthread_mutex_destroy(&mutex); //毁掉互斥量
    return 0;
}
```
运行结果，每次线程的执行顺序是不固定的，但是线程是必须执行的，除非调用的函数自动退出。每次读取临界区，也就是发生竞争的区域，每次读取都会将资源锁住，而锁住了，后面的线程也就等待前面的资源释放了再继续运行。只有等待前面的线程结束了，后面的线程才可以继续解锁资源继续执行。<br>
##### pthread_mutex_init初始化互斥量 phtread_mutex_t
初始化后必然要销毁，pthread_mutex_destory，否则会导致内存泄漏。<br>
#### 锁🔒mutex
```c
pthread_mutex_lock, pthread_mutex_trylock, pthread_mutex_unlock -  lock and unlock a mutex

#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mutex);
// 阻塞加锁，抢不到锁就等，死等，直到别人通过unlock再抢
int pthread_mutex_trylock(pthread_mutex_t *mutex);
// 尝试加锁，无论能否抢到锁都返回
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
**临界区是每个线程都要单独执行的，所以临界区的代码执行时间越短越好**<br>
📝 4个线程疯狂打印abcd持续五秒钟，但是要按照顺序打印，不能是乱序。<br>
```c
#include "../include/apue.h"
#include <pthread.h>
#include <string.h>

#define THRNUM 4
static pthread_mutex_t mut[THRNUM]; // 定义四个互斥量

static int next(int a){
    if(a+1 == THRNUM) // 0，1，2，3
        return 0;
    return a+1;
}

static void *thr_func(void *p){
    int n = (int)p;
    int ch = n+'a';
    while(1){
        pthread_mutex_lock(mut+n);// 锁住自己的互斥量
        write(1,&ch,1);
        pthread_mutex_unlock(mut+next(n));// 🔓解锁下一线程对应的互斥量
    }
    pthread_exit(NULL);
}

int main(){
    int i,err;
    pthread_t tid[THRNUM];
    for(i = 0;i<THRNUM;i++){
        pthread_mutex_init(mut+i,NULL);
        pthread_mutex_lock(mut+i);
        err = pthread_create(tid+i,NULL,thr_func,(void*)i);
        if(err){
            fprintf(stderr,"pthread_create():%s\n",strerror(err));
            exit(1);
        }
    }
    pthread_mutex_unlock(mut+1); // 解锁其中一个
    alarm(5);
    for(i = 0;i<THRNUM;i++){
        pthread_join(tid[i],NULL);
    }

    exit(0);
}
```
每个线程都在等待互斥量解锁，一旦解锁就执行，每个线程负责打印一个字母，每个字母都在ch的基础上➕1。<br>
**互斥量限制一段代码能否执行，而不是一个变量或一个资源。**<br>
### 条件变量 pthread_cond_t
令牌桶，通用多线程并发版令牌桶