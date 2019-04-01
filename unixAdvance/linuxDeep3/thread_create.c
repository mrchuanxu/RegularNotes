/**
 * 不动笔墨不读书系列
 * 继续理解线程实现，达成高效率和低复杂度
 * 
 * 线程的内存布局
 * 一个进程可以包含多个线程
 * 多个线程可以并发执行，从而提高系统的整体吞吐量，提供更好的用户体验
 * 一个进程中的多个线程共享大多数的进程数据，
 * 包括代码段、初始化数据、为初始化数据段、堆内存段以及动态链接内存段等
 * 实际上，线程栈的位置遵循共享库加载、映射共享内存和线程创建的排列顺序，有时可能会有所变化
 * 
 * 每个线程的代码均放置在ELF文件的.texg段中，会在进程启动时加载到可执行内存段内
 * 当进程在运行中动态创建线程时，每个线程特有的数据只是自己的栈，其他数据与所在进程的其他线程共享
 * 
 * 所有线程共享一块堆空间
 * 
 * 线程的实现方案
 * 
 * 线程实现模型
 * 多对一模型
 * 一对一模型
 * 多对多模型
 * 目前主流的线程实现方案是NPTL 一对一模型 
 * 
 * 修改与优化
 * 改进了线程组的实现
 * 引入Futex，将其作为一种通用的同步机制
 * 重写了内核调度程序，以实现有效的调度，支持更多的线程
 * 扩展了系统调用clone()
 * 
 * 内核中的用户线程和进程
 * 进程和线程的区别仅仅是一些属性(如虚拟内存，打开的文件，信号处理函数，进程ID等)的共享程度不同
 * clone是创建线程的底层系统调用，同时也为进程创建提供底层支持
 * ***/
#include <pthread/pthread.h>
#include <mutex>

int clone(int (*func)(void *), void * child_stack, int flags, void * func_args, ...);
/**
 * 其中，参数flags可以指定进程复制时与父进程共享的资源。
 * CLONE_VM | CLONE_FILES | CLONE_FS | CLONE_SIGHAND | CLONE_THREAD | CLONE_SETTLS | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM
 * 可以选择共享资源
 * 
 * 新建的实体与父进程共享同一份虚拟内存页、同一个打开的文件描述符表、文件系统信息、信号处理函数表等，且新创建的实体会被放在创建者的线程组内(CLONE THREAS)
 * 
 * 
 * 线程同步
 * 多线程，数据共享非常方便
 * 在线程读-处理-更新操作，保证其他线程不会中途闯入与其交叉执行
 * 
 * 互斥锁的使用
 * 最常用的线程同步技术是互斥锁，Linux线程库中的相关函数
 * int pthread_mutex_lock(pthread_mutex_t *mutex);
 * int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * 
 * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 * int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
 * 
 * 多个线程在临界区上的执行是串行的
 * 
 * 互斥锁的保护范围和使用顺序
 * 
 * ***/
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict abs_timeout);

/**
 * 保护锁
 * Futex方案，在该实现中，只有发生了锁的争用才需要陷入到内核空间中处理，否则所有的操作都可以在用户空间快速完成
 * 
 * 线程的链接和分离
 * 监听
 * pthread_join(pthread_t thread,void **retval);
 * 任何线程都可以监听一个指定的线程退出
 * 线程链接函数只能链接一个指定的ID的线程，而不能像进程一样监听任意线程的退出
 * 线程创建之后，可以分离函数设置其不需要等待被链接，线程结束后自动被清理
 * pthread_detach(pthread_t thread);
 * 
 * 线程的取消
 * 
 * 运行中的线程可以被其他线程主动取消
 * int pthread_cancel(pthread_t thread);
 * 
 * 对退出线程状态和类型的掌控，可以进一步控制它们响应取消请求的处理过程
 * int pthread_setcancelstate(int state, int *oldstate);
 * int pthread_setcanceltype(int type, int *oldtype);
 * 
 * 线程特有的数据
 * 全局变量静态变量和局部变量
 * 某个线程内的全局和静态变量。线程特有的数据就是某些线程内函数特有的=共享变量，
 * 
 * int pthread_key_create(pthread_key_t* key,void(*destructor)(void*));
 * 在线程中只执行一次，可以放在pthread_once()函数中执行。destructor是一个析构函数，用来创建标识某个线程本地存储的key
 * 析构函数用来释放各自内存空间
 * 
 * 设置并获取key
 * 
 * int pthread_setspecific(pthread_key_t key, const void *value);
 * void * pthread_getspecific(pthread_key_t key);
 * 
 * 
 * ***/
