#include "../include/apue.h"
#include <fcntl.h>
#include <string.h>
#include <syslog.h>

#define Fname "/tmp/out"

static FILE *fp;

static int Daemonize(void){
    pid_t pid;
    int fd;

    pid = fork();
    if(pid<0){
       // err_sys("fork error");
        return -1;
    }
    if(pid>0)
        exit(0);
    
    fd = open("/dev/null",O_RDWR);
    if(fd<0)
        return -2;
    
    dup2(fd,0);
    dup2(fd,1);
    dup2(fd,2);

    if(fd > 2)
        close(fd);
    
    setsid();
    chdir("/");
    umask(0); // 设置文件模式创建掩码
    return 0;
}

static void daemon_exit(int s){
    fclose(fp);
    closelog();
    syslog(LOG_INFO,"daemonixe exited");
    exit(0);
}

int main(){
    int i;
    struct sigaction sa;

    /***
     * 如果使用 signal(2) 函数则是这样注册信号处理函数
     * signal(SIGINT,daemon_exit);
     * signal(SIGTERM,daemon_exit);
     * signal(SIGQUIT,daemon_exit);  ***/
    // 改用sigaction
    sa.sa_handler = daemon_exit;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGQUIT);// 信号集加入了三个不同的信号
    sigaddset(&sa.sa_mask,SIGTERM);
    sigaddset(&sa.sa_mask,SIGINT);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL); // 不需要区分那个信号，只要信号来了就可以傻死进程，然后释放资源
    sigaction(SIGTERM,&sa,NULL);
    sigaction(SIGQUIT,&sa,NULL);

    openlog("mydaemon",LOG_PID,LOG_DAEMON);

    if(Daemonize()){
        syslog(LOG_ERR,"daemonize failed");
        exit(1);
    }else{
        syslog(LOG_INFO,"daemonize succssed");
    }
    fp = fopen(Fname,"w");
    if(fp == NULL){
        syslog(LOG_ERR,"fopen():%s",strerror(errno));
        exit(1);
    }

    for(i = 0;i<100;i++){
        fprintf(fp,"%d\n",i); // 每秒钟写一个序列
        fflush(fp);
        syslog(LOG_DEBUG,"%d was printed",i);
        sleep(1);
    }
    exit(0);
}
