/**
 * 不动笔墨不读书系列
 * 线程同步，让复杂工作流协调有序
 * 
 * 1. 多线程，让CPU持续忙碌
 * 2. 尽量让所有的CPU都有大体相当的负载，平均工作量
 * 
 * CPU在等待IO操作的时候，会闲。
 * 当某些工作需要IO操作时。应该放在独立的线程完成。
 * 
 * 此外一个线程在同一时刻只能运行在一个CPU核心上
 * 把一个应用中多个相干性很少的处理任务分成多个不同的线程区执行
 * 提高CPU的利用效率
 * 服务于同一应用的多个线程，会有联系
 * 
 * 互斥锁，常用的线程同步技术
 * 信号量 条件变量 读写锁 自旋锁
 * 
 * 信号量也能用于线程间的同步
 * 信号量可以使执行者在某个需要的条件不满足时进入休眠，当其他的执行者更新了信号量，使需要的条件重新被满足时，就会把睡眠的执行者唤醒继续执行
 * 
 * 递减信号量的操作相当于接取任务
 * 如果接取成功，会使得信号量减1
 * 如果信号量为0，表示当前没有可接取的任务，这是任务领取者会被挂起，直到有其他执行者在该信号量上执行递加操作
 * 
 * 递加操作相当于发布新任务
 * 发布成功，会使信号量加1
 * 如果有挂起的执行者，会唤醒该执行者来接取这个任务
 * 如果当前信号量已经达到了指定的容量，表示任务队列已满，任务发布的执行者会被挂起，直到任务队列中有空位留出
 * 
 * 信号量常与互斥锁配合使用
 * 
 * 信号量优缺点，结合工作方式
 * 优点 避免一些无效的线程唤醒，总体上减轻整个系统的负担
 * 
 * 劣势 重量级，信号量是一种IPC资源，对信号量操作的如下接口都是系统调用都是系统调用
 * 
 * ***/
int semget(key_t key, int nsems, int semflg);      //创建一组以 key 为标识的信号量
int semctl(int semid, int semnum, int cmd, ...);   //在指定的信号量上执行控制操作
int semop(int semid, struct sembuf *sops, unsigned nsops); //在指定信号量上执行 PV 操作

/**
 * 信号量配合互斥锁的实现只适用于工作线程对每个任务的处理时间相对较长，而且任务产生的速率比较慢的情形
 * 否则会引入严重的竞争消耗，以及不可忽略的系统调用消耗
 * 乱
 * 
 * 条件变量引入
 * 每个线程有自己的任务队列
 * 任务分发线程会把任务直接分配到某个工作线程的任务队列
 * 启动更多工作线程
 * 
 * 一个任务量巨大，并且每个任务处理时间很短的系统都可以采用这样的工作模式
 * 
 * ***/
int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t * cond); // 唤醒至少一个
int pthread_cond_broadcast(pthread_cond_t *cond); // 唤醒所有

/**
 * wait 会阻塞一个线程，直到有另外的线程在同一个条件变量cond上用signal或broadcast发出通知时再继续执行
 * 
 * while(pthread_cond_wait(&cond, &mtx)); Process the task
 * 正确处理多余和虚假的唤醒动作
 * 
 * ***/

/**
 * 读写锁
 * 更新频率低，多个线程中读取使用的频率很高临界区较大，临界区保护需要读写锁
 * 读共享，写独占
 * 确保临界区读写模式满足
 * 
 * ***/
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, 
        const pthread_rwlockattr_t *restrict attr);         //初始化读写锁
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);       //销毁读写锁
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);        //加读锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);        //加写锁

/**
 * 自旋锁
 * 实时性要求高，需要自旋锁
 * 执行的临界区非常短，只是执行有限的几条指令，可以考虑自旋锁
 * 循环持续获取锁
 * 持续忙等
 * 只有非常快速地完成临界区才适合用自旋锁保护
 * 而且临界区内一定不能有对同一个临界区的递归调用，否则会发生死锁
 * 
 * ***/
int pthread_spin_init(pthread_spinlock_t *lock, int pshared);  //初始化自旋锁
int pthread_spin_destroy(pthread_spinlock_t *lock);            //销毁自旋锁
int pthread_spin_lock(pthread_spinlock_t *lock);               //锁定自旋锁
