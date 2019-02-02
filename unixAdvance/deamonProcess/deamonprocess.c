#include "../include/apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>

void daemonize(const char *cmd){
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;

    // 更改文件权限屏蔽字 => 不屏蔽
    umask(0);
    // 获得最大的文件描述符的数目
    if(getrlimit(RLIMIT_NOFILE,&r1)<0)
        err_quit("%s:can't get file limit",cmd);
    // session leader to lose controlling tty
    if((pid=fork())<0)
        err_quit("%s:can't fork",cmd);
    else if(pid!=0)
        exit(0); // 父进程退出 留下孤儿进程
    // 脱离控制终端 PID
    // 成为组长进程 PGID
    // 成为会话组首个进程 SID
    setsid();
    // 忽略sighup信号
    // 当终端退出，会发送该信号给会话组长，默认处理方式退出
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP,&sa,NULL)<0){
        err_quit("sigaction");
        exit(-1);
    }
    // 再次fork 让守护进程不再担当会话组长，防止他打开终端
    if((pid = fork())<0)
    {
        perror("fork");
        exit(-1);
    }
    if(pid!=0){
        // 父进程退出
        printf("%d\n",pid);
        exit(0);
    }
    // 改变文件目录 改变工作目录
    if(chdir("/")<0){
        err_quit("chdir");
        exit(-1);
    }
    // 关闭文件描述符 所有
    if(r1.rlim_max == RLIM_INFINITY)
        r1.rlim_max = 1024;
    for(i = 0;i<r1.rlim_max;++i)
        close(i);
    // 重定向标准输入、标准输出、错误 到/dev/null
    fd0 = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd,LOG_CONS,LOG_DAEMON);
    if(fd0!=0||fd1!=1||fd2!=2){
        syslog(LOG_ERR,"unexpected file descriptors %d %d %d",fd0,fd1,fd2);
        exit(-1);
    }
    while(1){
        printf("hello world");
    }
}

int main(int argc,char *argv[]){
    daemonize(argv[0]);
    exit(0);
}