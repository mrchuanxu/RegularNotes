## 信号 初级异步
Linux环境的并发可以分为多进程+信号和多线程两种，信号属于初级异步，多线程属于强烈异步。<br>
信号与信号量不是一回事，信号量是指在同一个资源下，信号量通过P/V原子操作，使得线程之间能够按顺序执行，也就是同步，信号量是用计数的整数和一个队列来完成<br>
实际项目中，信号和多线程基本不会一块使用，要么使用多进程+信号，要么采用多线程的形式。<br>
**同步程序**的特点就是程序的执行流程、分支都是很明确，但是 **异步事件**就是事件到来的时间无法确定，到来之后的结果也是不确定的。比如俄罗斯方块游戏中，需要异步接收用户的方向控制输入。这就需要信号的支持。<br>
异步事件的获取方式通常有两种，一种是查询法，一种是通知法。<br>
异步事件到来的频率比较高的情况考虑用 **查询法**，因为撞到异步事件到来的概率比较高。<br>
异步事件到来的频率比较稀疏的情况考虑通知法，因为经济实惠。<br>
**所有的通知法都需要配合一个监听机制❕** 例如🎣钓鱼，放一个鱼竿就你就走了，就算🐟上钓你也不知道。<br>
#### 时间片调度
时间片调度就是通过中断打断程序的执行，把事件片耗尽的进程移动到队列中等待。所以任何进程在执行的过程中都是磕磕绊绊的不断被打断的，程序在任何地方都有可能被打断，唯独一条机器指令是无法被打断(原子操作)。<br>
### 信号概述
**信号不是中断**，中断只能由硬件产生， **信号是模拟硬件中断⏸️的原理**，在软件层面上进行的。<br>
`kill -l`，向其他进程查看或发送信号
```c
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL
 5) SIGTRAP      6) SIGABRT      7) SIGEMT       8) SIGFPE
 9) SIGKILL     10) SIGBUS      11) SIGSEGV     12) SIGSYS
13) SIGPIPE     14) SIGALRM     15) SIGTERM     16) SIGURG
17) SIGSTOP     18) SIGTSTP     19) SIGCONT     20) SIGCHLD
21) SIGTTIN     22) SIGTTOU     23) SIGIO       24) SIGXCPU
25) SIGXFSZ     26) SIGVTALRM   27) SIGPROF     28) SIGWINCH
29) SIGINFO     30) SIGUSR1     31) SIGUSR2
```
1-31标准信号，这里都是标准信号，其实下面讨论的内容没有特殊标记出来就是针对标准信号的。信号名都被定义为正整数常量<br>
信号有五种不同的默认行为:  **终止，终止+core，忽略，停止进程🤚，继续🏃。**<br>
core文件就是程序在崩溃时由操作系统为它生成的内存现场映像📷和调试信息，只要用来调试程序的，可以使用ulimit命令设置允许生成core文件的最大大小。<br>
* 终止🔚：使程序异常结束🔚。被信号杀死就是异常终止
* 终止+core：杀死进程，并为其产生一个core dump文件，可以使用这个core dump文件获得程序被🔪杀死的原因。
* 忽略：程序会忽略该信号，不作出任何响应。
* 停止🛑进程：将运行中的程序中断。被停止的进程就像被下了一个断点一样，停止运行并不会再被调度，直到收到继续运行的信号。当按下Ctrl+Z时就会将一个正在运行的前台进程停止，其实就是向这个进程发送了一个SIGTSTP信号(STOP🛑)。
* 继续🏃：使被停止的进程继续运行▶️。只有SIGCONT(continue)具有这个功能。
<br>
以下介绍几种常用的标准信号<br>

信号|默认动作|说明
|--|--|:--|
SIGABRT|终止+core|调用abort函数会向自己发送该信号使程序异常终止，通常在程序自杀或夭折时使用
SIGALRM|终止|调用alarm或setitimer定时器超时时⌚️向自身发送信号。setitimere设置which参数的值为ITMER_REAL时，超时后会发送此信号
SIGCHLD|忽略|当子进程状态改变系统会将该信号发送给其父进程。状态改变是🈯️由运行▶️状态改变为⏸️暂停状态、由暂停状态⏸️改变为运行▶️状态、由运行状态▶️改变为终止🛑状态等等
SIGHUP|终止|如果终端💻接口检测到链接断开则将此信号发送给该终端的控制进程，通常会话首进程就是该终端的控制进程
SIGINT|终止|当用户按下中断键➖(Ctrl+C)时，终端驱动程序产生此信号并发送给前台进程组中的每一个进程。
SIGPROF|终止|setitimer设置which参数的值为ITIMER_PROF时，超时后会发送此信号
SIGCONT|继续/忽略|接收信号的进程处于停止🤚信号则继续执行，否则忽略
SIGQUIT|终止+core|当用户在终端按下退出键➖`(Ctrl+\)`时，终端驱动程序产生此信号并发送给前台进程组中的所有进程，该信号与SIGINT的区别时，在终止进程的同时为它生成core dump文件
SIGTERM|终止|使用kill发送信号，若不置顶具体信号，则默认发送该信号
SIGUSR1|终止|用户自定义的信号。系统不赋予特殊意义，想拿来干嘛就干嘛
SIGUSR2|终止|同上
SIGVTALRM|终止|setitimer设置which参数的值为ITIMER_VIRTUAL时，超时后发送该信号

<br>

### 函数signal
```c
// signal - ANSI C signal handling
// 查了一下man手册，signal函数如下
#include <signal.h>
void (*signal(int sig, void (*func)(int)))(int);
// 参数时整型sig和指向参数类型时int，返回类型是void的函数，signal是一个函数指针，指向的函数具有以上两个参数并返回一个指针，指向参数是int型的函数。
// or in the equivalent but easier to read typedef'd version:
typedef void (*sig_t) (int);
sig_t signal(int sig, sig_t func);
```
sig是1-31标准信号，func是收到信号时的处理行为，也就是信号处理函数；也可以使用SIG_DEF和SIG_IGN两个宏来替代。SIG_DEF表示使用信号的默认处理行为。SIG_IGN(ignore)。<br>
返回值，返回原来的信号处理函数。有时候我们在定义自己的信号📶处理函数之前会把原来的信号处理函数保存下来，这样当我们的库使用完之后需要还原原来注册的信号处理函数，避免因为我调用了我们的库而导致别人的库失效的问题。
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void handler(int s){
    write(1,"!",1);
}

int main(){
    int i = 0;
    signal(SIGINT,handler);
    for(i = 0;i<10;i++){
        write(1,"*",1);
        sleep(1);
    }
    return 0;
}
```
接下来每秒钟会打印一个(*)，当按下Ctrl+C就打印一个❕。
```c
transcheung$ time ./a.out
******^C!***^C!*
real    0m8.246s
user    0m0.002s
sys     0m0.003s
```
这就改变了传送信号的行为。通过time命令可以测试到，程序并没有持续10秒钟才结束，这是因为信号打断阻塞的系统调用，也就是说，SIGINT打断了sleep。所以这里的信号是随时接收信息的，也不会改变i的值，所以每次打断之后就会重新再跑一遍for循环。<br>

### 竞争