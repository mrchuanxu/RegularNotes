#include "../include/apue.h"
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 10

static volatile int loop = 0;

static void alarm_handler(int a){
    alarm(1);
    loop = 0;
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
    do{
        fd = open(argv[1],O_RDONLY);
        if(fd<0){
            if(EINTR != errno){
                err_sys("open()");
                goto;
            }
        }
    }
}