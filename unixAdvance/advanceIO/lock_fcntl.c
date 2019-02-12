#include "../include/apue.h"
#include <fcntl.h>
#include <sys/file.h>

void lock_tst(int fd,int type,off_t offset,int whence,off_t len){
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;
    while(1){
        lock.l_type = type;
        if((fcntl(fd,F_SETLK,&lock)) == 0){
            // 根据不同的type值给文件上锁或解锁
            switch (lock.l_type)
            {
                case F_RDLCK:
                    printf("read lock set by %d\n",getpid());
                    break;
                case F_WRLCK:
                    printf("wwwwrite lock set by %d\n",getpid());
                    break;
                case F_UNLCK:
                    printf("release lock set by %d\n",getpid());
                    break;
                default:
                    break;
            }
            return;
        }
        // 判断文件是否能上锁
        fcntl(fd,F_GETLK,&lock);
        // 判断文件不能上锁的原因
        if(lock.l_type != F_UNLCK){
            // 该文件已有写入锁
             switch (lock.l_type)
            {
                case F_RDLCK:
                    printf("read already lock set by %d\n",lock.l_pid);
                    break;
                case F_WRLCK:
                    printf("write already lock set by %d\n",lock.l_pid);
                    break;
                default:
                    break;
            }
            getchar();
        }
    }
    return;
}

int main(void){
    int fd;
    pid_t pid;
    fd = open("./advance.txt",O_RDWR|O_CREAT,0666);
    if(fd<0){
        err_sys("open()");
    }
    // 给文件上写锁
    if((pid = fork())<0)
        err_sys("fork error");
    else if(pid == 0){
        // 子进程上写锁
        lock_tst(fd,F_WRLCK,0,SEEK_SET,0);
        sleep(10);
        lock_tst(fd,F_UNLCK,0,SEEK_SET,0);
        exit(0);
    }
    sleep(5); // 先让子进程先跑
    // 父进程给文件上读取锁
    lock_tst(fd,F_RDLCK,0,SEEK_SET,0);
    getchar();
    // 给文件解锁
    lock_tst(fd,F_UNLCK,0,SEEK_SET,0);
    getchar();
    close(fd);
    exit(0);
}

