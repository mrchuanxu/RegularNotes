/**
 * 不动笔墨不读书系列
 * 理解时钟和定时器，电子世界中的脉动
 * 
 * 时钟很重要
 * 时钟与定时器概述
 * CPU上亿个元器件都需要在时钟信号的统一节拍下协调动作才能完成需要的计算功能
 * 对于一个特定的CPU来说，节奏是固定的
 * 信号源的频率越稳定，计时就越精确；信号的频率越高，对时间的分辨率就越高
 * 
 * Linux传统间隔定时器 setitimer() 设定在未来某个时间点到期，同时可以可选地设置之后每个一段时间到期一次
 * int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
 * 
 * which可与你指定
 * ITIMER_REAL 真实时间进行度量，超时后会给创建进程发送SIGALARM信号
 * ITIMER_VIRTUAL 以进程在用户模式下的CPU时间为度量，超时后给创建进程发送SIGVALRM信号
 * ITIMER_PROF 以进程在用户模式和内核模式的CPU总时间为度量，超时后给创建进程发送SIFPROF信号
 * 虽然以上参数的最小时间单位是微秒，但是定时器实际工作时的时间分辨率与当前的系统负载、内核的时钟中断周期等都有关系，通常远远达不到1微秒的精度。
 * 
 * 查询定时器状态getitimer()
 * int getitimer(int which,struct itimerval* curr_value);
 * 
 * alarm 定时器精度要求不高，精确到秒
 * unsigned int alarm(unsigned int seconds);
 * 到期时，内核会向进程发送SIGALARM信号。
 * 
 * SIGALARM信号所打断 并返回负值标识操作没有成功完成，进一步通过errno确认错误原因是被打断
 * 
 * 克服传统定时器的局限性 POSIX定时器 能提供更加灵活的计时控制，提供更高的时间精度
 * 
 * timer_create
 * timer_settime
 * timer_delete
 * 
 * clockid 四个取值
 * timerid 是操作的对象
 * 
 * 一个进程可以支持多个同类定时器
 * 可以自定义定时器到期时的中断通知信号
 * 可以支持在定时器到期时执行线程函数，所以超时处理函数不需要遵循信号处理函数的编写标准，因为可以更加灵活
 * 支持精确到纳秒的时间精度
 * 
 * linux内核维护动态定时器 维护大量使用定时器
 * 采用了精巧的数据结构组织所有动态定时器
 * bucket链表操作，维护大量的定时器
 * 
 * 使用紧凑的数据结构，实现高效的定时器管理
 * ***/