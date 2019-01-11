// #include <fcntl.h>
// #include <unistd.h>


// int creat(const char* path,mode_t mode);
// int close(int fd);
// off_t lseek(int fd,off_t offset,int whence);
#include "../include/apue.h"


int main(void){
    // if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)  //   测试为-1而不是0
    //     printf("can't seek");
    // else
    //     printf("seek ok!");
    char *str = "123abc456";
    int i = 0;
    i = atoi(str);
    printf("%d\n",i);
    char name[L_tmpnam],line[MAXLINE];
    FILE *fp;
    printf("%s\n",tmpnam(NULL));
    tmpnam(name);
    printf("%s\n",name);

    if((fp=tmpfile())==NULL) // 创建一个临时文件
        err_sys("tmpfile error");
    fputs("one line of output\n",fp); // 写到临时文件
    rewind(fp); // read it back
    if(fgets(line,sizeof(line),fp)==NULL)
        err_sys("fgets error");
    fputs(line,stdout);
    exit(0);
}