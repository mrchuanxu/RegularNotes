## 信号量、条件变量、互斥量、读写锁🔒
对于进程和线程或者协程有了了解之后，我们知道，由于抢占式调度方式，进程和线程的执行顺序是不可预知的，那么如何使得两个进程按照我们想要的顺序执行，从而得出正确的结果呢？今天我们就来聊聊并探讨一下<br>
我们直到两个进程之间要相互通信并顺序执行就需要一些帮助，在什么情况呢？例如 **两个或多个进程读写某些共享数据，最后结果依赖于进程的精确时序(竞争条件)。**<br>
**把对共享内存进行访问的程序片段称作临界区。** 如果能使两个进程 **不可能同时处于临界区内** ，就能够 **避免竞争**。<br>
先看一个经典问题❓ <br>
**生产者-消费者问题:** 有一个缓冲区，
* 一个（或多个——进程在生产某种产品，它生产的东西会放入缓冲区内；
* 一个(或多个)进程在消费产品，它会从缓冲区内取走产品。
* 当缓冲区满的时候，生产者应当暂时停止生产；
* 当缓冲区为空时，消费者应当暂时听追消费。<br>
显而易见，这个问题用简单的哦判断缓冲区是否为0或N是无法解决的。如果在消费者判断缓冲区为0时，恰好遇到了进程切换，生产者进程开始运行，此时应当唤醒消费者，然而这个信号丢失了，因为切换到消费者才进行了睡眠。这时，生产者会不断地运行，直到缓冲区满，两个进程全部睡眠，造成了死锁
```c
#define N 10000

int count = 0;
void producer(void){
    int item;
    while(TRUE){
        item = produce_item();
        if(count == N) sleep(); // 缓冲区满，生产者进程睡眠
        insert_item(item);
        count = count+1;
        if(count == 1) wakeup(consumer); 
        // 设想条件成立就切换进程，再次切回时，唤醒消费者进程，然后此时消费者进程没有睡眠，信号丢失
    }
}

void consumer(void){
    int item;
    while(TRUE){// 睡眠前期遇到了进程切换
        if(count == 0) sleep(); // 第一次count = 1，消费者进程不会睡眠；第二次确实睡眠了
        item = remove_item();
        count = count - 1;
        if(count == N-1) wakeup(producer);
        cousume_item(item);
    }
}
```
那怎么解决这个问题呢？怎么按照顺序执行呢？乍一看其实也没什么，觉得是按顺序执行就好，但，理想很丰满，现实很骨感。<br>
### 信号量 用来计数的整数和一个队列
信号量是一种数据结构，可以理解为一个用来计数的整数和一个队列。整数用来记录唤醒的次数，而队列被用来记录因为该信号量而阻塞的进程。<br>
信号量只支持两种操作:  **P/V操作**<br>
* P操作: 可以理解为测试并减一。P(signal)，如果signal大于0，那么把它减一，进程继续执行；如果signal为0，那么执行P操作的进程将会被阻塞，从而变为阻塞态，添加到因为signal信号而阻塞的进程队列中。<br>
* V操作: 可以理解为+1并唤醒。V(signal)后，如果signal本来就大于0，那么执行+1；如果有进程在该信号量上被阻塞，那么从队列中根据某种策略选择一个进程唤醒。如果多个进程在该信号量上阻塞，那么V操作后，signal仍然可能为负数。<br>
**P/V均是原子操作，一个整体执行而不会被打断**<br>
有了信号量，再来看一下生产者-消费者问题
```c
#define N 1000

typedef int semaphore;
semaphore mutex = 1; // 控制对临界区的访问 共享内存访问部分
semaphore empty = N; // 表示空槽的数量
semaphore full = 0; // 表示填满槽的数量
int count = 0;

void producer(void){
    int item;
    while(TRUE){
        item = produce_item();
        down(&empty); // 信号量empty表示未用数量
        down(&mutex); // 要改变共享区(缓冲区) 加锁
        insert_item(item);
        up(&mutex); // 解锁 wakeup
        up(&full);
    }
}

void consumer(void)
{
    int item;
    while(TRUE)
    {
        down(&full); // 信号量full 表示已用 wait操作
        down(&mutex); // 加锁
        item=remove_item();
        up(&mutex); // wakeup操作 释放锁
        up(&empty);// 再置为N wakeup操作
        consume_item(item);
    }
}
```
empty大于0，生产者继续生产，full等于0，消费者持续等待⌛️。最后生产者解锁，更改full，消费者判断full>0，开始wakeup运行程序。这样就将切换进程不再影响顺序执行。<br>
OK，生产者消费者的问题我们解决了，这里我们彻底来看一下在linux下的信号量的操作。<br>
#### Linux中信号量的使用 sys/sem.h
linux提供了一组信号量API，声明在头文件sys/sem.h中<br>
* semget函数，新建信号量
```c
int semget(key_t key,int num_sems,int sem_flags);
// key 信号量键值，可以理解为信号量的唯一性标记
// sem_flags 两个值 IPC_CREATE和IPC_EXCEL
// IPC_CREATE 表示若信号量已存在，返回该信号量标识符
// IPC_EXECL 表示若信号量已存在，返回错误
// 返回相应的信号量标识符，失败返回-1
```
* semop 修改信号量的值
```c
int semop(int sem_id,struct sembuf *sem_opa,size_t num_sem_ops);
// sem_id信号量标识符 通常是semget返回的值
```
sem_opa是一个结构体
```c
struct sembuf{
    short sem_num; 
    // 除非使用一组信号量，都则它为0，一组信号就会依次排序0，1，2...
    short sem_op; 
    // (信号资源)信号量在一次操作中需要改变的数据，通常是两个数，一个是-1，即P操作，一个是+1，V操作
    short sem_flg; 
    // 通常为SEM_UNDO，使操作系统跟踪信号 并在进程没有释放该信号量而终止时，操作系统释放信号量(调用semop前的值) 还有一种使SEM_NOWAIT 信号不能满足时，semop就会阻塞，并立即返回，同时设置错误信息
    // 采用SEM_UNDO，避免在异常情况下结束时，未将锁定资源解锁，造成该资源永远锁定
}
```
所以释放原来的信号量很重要。<br>
* semctl，用于信号量的初始化和删除
```c
int semctl(int sem_id,int sem_num,int command,[union semun sem_union]);
// command有两个值，SETVAL，IPC_RMID表示初始化和删除(remove)信号量
```
sem_union使可选参数
```c
union semun{
    int val; // 传给信号量的初始值
    struct semid_ds *buf;
    unsigned short *arry;
}
```
#### Linux信号量的使用示例
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int sem_id;

int set_semvalue(){
    union semun sem_union;
    sem_union.val = 1; // 初始化信号量为1
    if(semctl(sem_id,0,SETVAL,sem_union)==-1) return 0;
    return sem_union.val; // 返回信号量的值
}

// P操作
int semaphore_p(){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_b,1)==-1){ // 修改信号量的值
        fprintf(stderr,"semaphore_p failed\n");
        return 0;
    }
    return 1;
}

// V 操作
int semaphore_v(){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if(semop(sem_id,&sem_b,1)==-1){ // 修改信号量的值
        fprintf(stderr,"semaphore_v failed\n");
        return 0;
    }
    return 1;
}
// delete 信号量
void del_semvalue(){
    union semun sem_union;
    if(semctl(sem_id,0,IPC_RMID,sem_union) == -1)
        fprintf(stderr,"Failed to delete smaphore\n");
}

int main(int argc,char **argv){
    char message = 'x';
    // 创建信号量
    sem_id = semget((key_t)4566,1,0666|IPC_CREAT);
    if(argc>1){
        // 初始化信号量
        if(!set_semvalue()){
            fprintf(stderr,"init failed\n");
            exit(EXIT_FAILURE);
        }
        // 参数第一个字符赋给message
        message = argv[1][0];
    }
    int i = 0;
    for(i = 0;i<5;i++){
        // 等待信号量
        if(!semaphore_p()){
            exit(EXIT_FAILURE);
        }
        printf("%c",message);
        fflush(stdout);
        sleep(1);
        // 发送信号量
        if(!semaphore_v()){
            exit(EXIT_FAILURE);
        }
        sleep(1);
        printf("\n%d-finished\n",getpid());
        if(argc>1){
            // 退出前删除信号量
            del_semvalue();
        }
        exit(EXIT_SUCCESS);
    }
}
```
这个只是使用示例，若要完成具体功能就需要使用不同的编写方式。<br>
那么使用的mutex又是什么骚操作呢？
### 互斥锁(mutex)🔒
互斥量其实可以理解为一个简化的信号量，只有两种状态: 0和1.互斥锁是用来解决 **进程(线程)互斥**问题的。所谓进程互斥，就是两个进程实际上是一种互斥的关系， **两者不能同时访问共享资源。**<br>
互斥量和信号量原理比较类似，一旦一个线程获得了锁，那么其他线程就无法访问共享资源，从而被阻塞，直到该线程交还出了锁的所有权，另外一个线程才能获得锁🔒。<br>
### 条件变量 用于线程和管程中的进程互斥 常与互斥量一起使用
条件变量是另一种同步机制，可用于线程和管程中的进程互斥。通常与互斥量一起使用。<br>
条件变量允许线程由于一些暂时没有达到的条件而阻塞。通常，等待另一个线程完成该线程所需要的条件。条件达到时，另外一个线程发送一个信号，唤醒该线程。<br>
* pthread_cond_wait 等待
* pthread_cond_signal 条件达到发送信号<br>
条件变量与互斥量一起使用，一般情况: 一个线程锁住一个互斥量，然后当它不能获得它期待的结果时，等待一个条件变量；最后另外一个线程向它发送信号，使得它可以继续执行。<br>
⚠️，pthread_cond_wait会暂时解开持有的互斥锁。<br>
再来看一下linux下的条件变量
#### Linux下的条件变量 怎么判断是否达到了条件？
```c
#include <pthread.h>

int pthread_cond_init(pthread_cond_t *cond,pthread_condattr_t *cond_attr);//  初始化pthread_cond_t是条件，在使用之前必须要进行初始化 成功返回0，失败返回错误编号 attr为NULL时，会创建一个默认属性的条件变量
int pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);
// 成功返回0，失败返回错误编号
int pthread_cond_timewait(pthread_cond_t *cond,pthread_mutex *mutex,const timespec *abstime);
// 成功返回0，失败返回错误编号
int pthread_cond_destroy(pthread_cond_t *cond);  
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);  //解除所有线程的阻塞
```
上来就这几个函数，先来解释一遍这些函数怎么用吧。<br>
初始化pthread_cond_t有两种方式，
* 静态: pthread_cond_init可以用PTHREAD_COND_INITALIZER
```c
pthread_cond_t qready = PTHREAD_COND_INITALIZER;
```
* 动态: pthread_cond_init函数，是释放动态条件变量的内存空间之前，要用pthread_cond_destory对其进行清理(怎么清理?)<br>
#### 等待条件，阻塞等待`pthread_cond_wait`和超时等待`pthread_cond_timewait`
等待条件函数等待条件变为真，传递给pthread_cond_wait的互斥量 **对条件进行保护**，调用者把锁住的互斥量传递给函数，函数把调用线程放到等待条件的线程列表上，然后对互斥量解锁，这两个操作时原子操作。所以在还没返回之前，互斥量是已经解锁的，但是返回后，互斥量就再次被锁住，这时候，等待的线程就可以继续执行。<br>
#### 通知条件 通知变化
```c
int pthread_cond_signal(pthread_cond_t *cond);
// 成功返回0，失败返回错误编号
int pthread_cond_broadcast(pthread_cond_t *cond);  
// 解除所有线程的阻塞 成功返回0，失败返回错误编号
```
这两个函数用于通知线程条件已经满足，向线程或条件发送信号。⚠️，一定要在改变条件状态以后再给线程发送信号<br>
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t condc,condp; // 条件变量
pthread_mutex_t the_mutex; // 互斥锁

unsigned int buffer = 0;
const int MAX = 100;

void *producer(void *ptr){ // 生产者
    for(int i = 1;i < MAX;i++){
        pthread_mutex_lock(&the_mutex); // 锁住资源
        while(buffer != 0) pthread_cond_wait(&condp,&the_mutex); // 对互斥量解锁
        sleep(1);
        buffer = i;
        printf("producer pthread produce one production %d.\n",i);
        // 唤醒两个消费者线程
        pthread_cond_broadcast(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0); // 退出线程
}

void *consumer1(void *ptr){
    for(int i = 1;i<MAX;i++){
        pthread_mutex_lock(&the_mutex); //  共用一个锁，锁住同一个资源
        while(buffer == 0) pthread_cond_wait(&condc,&the_mutex); // 这是上面传下来的条件变量
        printf("consumer1 pthread consume one production %d\n",buffer);
        buffer = 0;
        pthread_cond_signal(&condp); // 通知线程 条件已经满足
        pthread_mutex_unlock(&the_mutex); // 解锁资源
    }
    pthread_exit(0);
}

void *consumer2(void *ptr){
    for(int i = 1;i<MAX;i++){
        pthread_mutex_lock(&the_mutex); //  共用一个锁，锁住同一个资源
        while(buffer == 0) pthread_cond_wait(&condc,&the_mutex); // 这是上面传下来的条件变量
        printf("consumer2 pthread consume one production %d\n",buffer);
        buffer = 0;
        pthread_cond_signal(&condp); // 通知线程 条件已经满足
        pthread_mutex_unlock(&the_mutex); // 解锁资源
    }
    pthread_exit(0);
}

int main(void){
    pthread_t pro,con1,con2;
    pthread_mutex_init(&the_mutex,0); // 初始化锁，0
    pthread_cond_init(&condc,0);
    pthread_cond_init(&condp,0); // 这时候就需要讲讲线程的创建了
    pthread_create(&con1,0,consumer1,0);
    pthread_create(&pro,0,producer,0);
    pthread_create(&con2,0,consumer2,0);
    pthread_join(pro, 0);
    pthread_join(con1, 0);
    pthread_join(con2, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
    return 0;
}
```
这部分要在创建线程的部分继续拿来做🌰。<br>
条件变量暂时先讲到这里
### 读写锁 读者-写者问题
读写锁🔒和互斥量类似，不过读写锁🔒允许更高的 **并行性**。互斥量要么锁住状态要么时不加锁状态，而且一次只有一个线程可以对其加锁。<br>
* 只要有一个读者在读，后来的读者可以进入共享区直接读
* 只要有一个读者在读，写者就必须阻塞，直到最后一个读者离开
* 不考虑抢占式，写者在写时，即使有读者到达，也会就绪等待<br>
```c
typedef int semaphore;
semaphore mutex = 1; // 互斥锁，控制对rc的访问
semaphore db = 1; // 控制对数据库的访问
int rc = 0; // 当前读者的数量

void reader(void){
    while(TRUE){
        down(&mutex); // 加锁
        rc += 1;
        if(rc == 1) down(&db); // 第一个读者 加锁
        up(&mutex); // 解锁 允许多个读者读数据库
        read_data_base();
        down(&mutex); // 加锁 保护读者计数器 
        rc = rc-1; // 读者在减少
        if(rc == 0) up(&db); // 最后一个读者离开，解锁数据库资源
        up(&mutex); // 解锁 读者资源
        use_data_read();
    }
}

void writer(void){
    while(TRUE){
        think_up_data();
        down(&db); // 获取数据库访问的锁
        write_data_base();
        up(&db); // 写完解锁🔓
    }
}
```
三种状态：
1. 读模式下的加锁状态 试图以读模式对它进行加锁的线程都可以得到访问权，若有线程要写，那么就要阻塞等待直到线程释放最后一个读🔒。
2. 写模式下加锁状态 被解锁之前，所有对这个锁加锁🔒的线程都会被阻塞
3. 不加锁状态
一次只有一个线程可以占有写模式的读写锁，但是多个线程可以同时占有读模式的读写锁🔒。<br>
当读写锁🔒处于读模式锁住状态时，如果另外线程试图以写模式加锁，读写锁🔒通常水阻塞随后的读模式锁，也就是队列的思想。<br>
**读写锁🔒非常适合于对数据结构读的次数远大于写的情况**。当在读写锁在写模式下，所保护的数据结构可以被安全地修改，因为当前只有一个线程可以在写模式下拥有这个锁。读，也可以被锁保护，多个读模式锁线程可以读取<br>
**读写锁🔒也叫共享-独占锁🔒**。读模式共享，写模式独占<br>
### 总结
* 互斥锁只用于同一个线程中，用来给一个需要对临界区进行读写的操作加锁🔒
* 信号量和互斥量不同的地方在于，信号量一般用于多进程或线程中，分别实行P/V操作
* 条件变量一般和互斥锁同时使用，或者用在管程中
* 互斥锁，条件变量都只用于同一个进程的各线程间，而信号量(有名信号量)可用于不同进程间的同步。当信号量用于进程间同步时，要求信号量建立在共享内存区
* 互斥锁是为上锁而优化的；条件变量是为等待而优化的；信号量既可用于上锁也可用于等待，因此会有更多的开销和更高的复杂性。<br>