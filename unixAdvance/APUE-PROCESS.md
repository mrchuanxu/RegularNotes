## 进程环境
### main函数
当内核执行C程序时(使用一个exec函数)，在调用main前先调用一个 **特殊的启动例程**。可执行程序文件将此启动例程指定为程序的起始地址--这是由链接编辑器设置的，而 **链接编辑器则由C编译器调用**。启动例程从内核取得命令行参数和环境变量值，然后为按上述方式调用main函数做好安排。<br>
### 进程终止
5种正常终止(termination)。
1. 从main返回 return 0; 只有在main中才能结束进程
2. 调用exit exit(0)专门用来结束进程的 程序任何地方都可以使用，并且退出进程，较于return不行，return是只退出当前函数。
3. 调用_exit或_Exit _exit(0)
4. 最后一个线程从启动例程返回
5. 从最后一个线程调用pthread_exit<br>
3种异常终止
1. 调用abort 出现了不可预知的错误，为了避免异常影响范围扩大，调用abort自杀。实际上越是通过信号完成的
2. 接到一个信号 信号有很多种，有些默认动作是被忽略的，有些默认动作则是杀死进程
3. 最后一个线程对取消请求做出响应<br>
进程是线程的容器，最后一个线程的结束会kill掉一个进程。<br>
#### atexit
```c
#include <stdlib.h>

int atexit(void (*func)(void));// 成功，返回0，出错，返回非0
```
atexit的参数是一个函数地址，当调用此函数时，无需向它传递任何参数，也不期望他会返回一个值。exit调用这些函数的顺序与他们登记时候顺序相反。(栈)<br>
![c程序是如何启动和终止](./img/process_exit.png)<br>
内核使程序执行的唯一方法是调用一个exec函数。进程自愿终止的唯一方法是显式或隐式地(通过调用exit)调用_exit或_Exit。进程也可非自愿地由一个信号使其终止。<br>
```c
    if(atexit(my_exit2)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    return 0;
```
**钩子函数:**注册的钩子函数形式必须是这样：void (*function)(void)，因为它不会接收任何参数，也没有任何机会返回什么值，所以是一个无参数无返回值的函数。
```c
    puts("Begin!");
    if(atexit(my_exit2)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    if(atexit(my_exit1)!=0)
        err_sys("can't re");
    puts("End!");
```
为什么 "End!" 先输出了，而 "f3" 后输出了呢？因为使用 atexit(3) 函数注册钩子函数的时候并不会调用钩子函数，仅仅是注册而已，只有在程序正常结束的时候钩子函数才会被调用。<br>
还记得我们上面提到的什么情况是正常结束吧？**注意是只有正常结束才会调用钩子哟，异常结束是不会调用钩子函数的。**<br>
可以解决很多问题！！！<br>
### 环境表
每个程序都会收到一张环境表。与参数表一样，环境表也是一个字符指针数组。其中每个指针包含一个以null结束的C字符串的地址。<br>
```c
extern char **environ;
```
environ为环境指针，指针数组为环境表，其中各指针指向的字符串为环境字符串。
![env环境表](./img/env.png)<br>
访问环境变量可以说你用getenv和putenv函数。<br>
