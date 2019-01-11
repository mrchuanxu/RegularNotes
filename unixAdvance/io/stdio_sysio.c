#include "../include/apue.h"

/***
 * 为3个标准流
 * 以及一个与普通文件相关联的流
 * 打印有关缓冲的状态信息***/

void pr_stdio(const char*,FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE*);
int buffer_size(FILE*);

int main(void){
    FILE *fp; // 定义一个文件指针
    fputs("enter any c\n",stdout); // 绑定到输出流
    if(getchar()==EOF) // 读取输入流
        err_sys("getchar error");
    fputs("on line to standard error\n",stderr);

    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);

    if((fp = fopen("./file.txt","r"))==NULL) // 只读方式打开一个文件
        err_sys("fopen error");
    if(getc(fp) == EOF) // 读取文件，一直读到末尾
        err_sys("getc error");
    pr_stdio("./file.txt",fp);
    exit(0);
}

// 接下来看一下pr_stdio
void pr_stdio(const char *name,FILE *fp){
    printf("stream = %s,",name);
    if(is_unbuffered(fp)) // 请往下看is_unbuffered函数
        printf("unbuffered"); // 不带缓冲
    else if(is_linebuffered(fp))
        printf("line buffered"); // 行缓冲
    else
        printf("fully buffered"); // 全缓冲
    printf(",buffer size = %d\n",buffer_size(fp));
}

int is_unbuffered(FILE *fp){
    return (fp->_flags & __SNBF);
}
int is_linebuffered(FILE *fp){
    return (fp->_flags & __SLBF);
}
int buffer_size(FILE *fp){
    return (fp->_bf._size);
}