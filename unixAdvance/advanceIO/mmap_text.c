#include "../include/apue.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define FNAME "./advance.txt"

int main(void){
    int fd,i;
    char *str;
    struct stat statres;
    int count = 0;

    fd = open(FNAME,O_RDONLY);

    if(fd<0){
        err_sys("open()");
    }

    // 通过stat获得文件大小
    if(fstat(fd,&statres)<0){
        err_sys("fstat()");
    }

    str = mmap(NULL,statres.st_size,PROT_READ,MAP_SHARED,fd,0);
    // 映射区可读
    if(str == MAP_FAILED)
        err_sys("mmap()");

    close(fd);

    for(i = 0;i<statres.st_size;i++){
        // 访问文本文件，所以可以把映射的内存看作是一个大字符串处理
        if(str[i] == 's'){
            count++;
        }
    }

    printf("count = %d\n",count);

    // 解除映射 否则会造成内存泄漏
    munmap(str,statres.st_size);
}