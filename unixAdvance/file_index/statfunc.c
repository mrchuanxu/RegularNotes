#include "../include/apue.h"

int main(int argc,char *argv[]){
    struct stat buf;
    char *ptr;
    printf("%s\n",argv[1]);
    if(stat(argv[1],&buf)<0)
        printf("stat error");
    if(S_ISREG(buf.st_mode))
            ptr = "regular";
        else if(S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if(S_ISCHR(buf.st_mode))
            ptr = "charactrt special";
        else if(S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if(S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if(S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if(S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "**unknow mode **";
        printf("%s\n",ptr);
    // 所以stat是结合着S_ISDIR这些标志符号来使用的
}