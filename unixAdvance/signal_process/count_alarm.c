#include "../include/apue.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 10
#define MAXTOKEN 1024 // 令牌桶，令牌上限 保持速度的保证

// static volatile int loop = 0;
static volatile int token = 0; // 积攒令牌数量
static void alarm_handler(int a){
    alarm(1); // 其实这里只是计时了1秒 每次实现自调用
    if(token < MAXTOKEN){
        token++; // 每秒钟增加令牌 积攒后按速度播放
    }
}

int main(int argc,char **argv){
    int fd = -1;
    char buf[BUFSIZE] = "";
    ssize_t readsize = -1;
    ssize_t writesize = -1;
    size_t off = 0;

    if(argc < 2){
        fprintf(stderr,"Usage %s <filepath>\n",argv[0]);
        return 1;
    }
    do{ // 这里要open文件，一直要open文件
        fd = open(argv[1],O_RDONLY);
        if(fd<0){
            if(EINTR != errno){
                err_sys("open()");
            }
        }
    }while(fd<0);

    // loop = 1; // 设置开始循环♻️
    signal(SIGALRM,alarm_handler);// 捕捉信号
    alarm(1); //    发送信号 这是启动signal的alarm
    while(1){
        // while loop; 忙等
        // 非忙等
        while(token <=0){ // 如果令牌数量不足则等待添加令牌
            pause(); // 因为添加令牌是通过信号实现的，所以可以使用pause实现非忙等
            // 使调用进程挂起直到捕捉到一个信号
            // SIGALRM打算pause函数，然后继续执行，每次token都会被加一减一
        }
        token--; // 每次读取BUFSIZE个字节的数据就扣减令牌
        printf("token : %d\n",token);
        while((readsize = read(fd,buf,BUFSIZE))<0){ // 开始读 每秒读10个
            if(readsize < 0){
                if(EINTR == errno){
                    continue;
                }
                err_sys("error read()");
                goto e_read;
            }
        }
        if(!readsize){ // 读到了数据
            break;
        }
        off = 0;//  偏移量设为0
        do{
            writesize = write(1,buf+off,readsize); // 开始写到控制台
            off+=writesize;
            readsize-=writesize; // 全写完
        }while(readsize>0);
    }
    close(fd);
    return 0;

    e_read:
        close(fd);
}