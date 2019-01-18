#include "../include/apue.h"
#include <fcntl.h>

int main(void){
    if(open("file.txt",O_RDWR)<0)
        err_sys("open error");
    if(unlink("file.txt")<0)
        err_sys("unlinke error");
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    exit(0);
}