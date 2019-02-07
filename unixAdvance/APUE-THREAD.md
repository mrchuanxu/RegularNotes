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




