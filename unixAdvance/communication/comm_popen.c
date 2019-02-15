#include "../include/apue.h"
#include <sys/wait.h>

#define PAGER "${PAGER:-more}"
// "${PAGER:-more}" 如果shell变量PAGER已经定义，且其值非空，则使用其值，否则使用字符串more

int main(int argc, char **argv){
    char line[MAXLINE];
    FILE *fpin,*fpout;

    if(argc!=2) err_quit("usage comm_popen.t <pathname>");
    if((fpin = fopen(argv[1],"r"))==NULL) err_sys("can;t open %s",argv[1]);
    // 会写向子进程
    if((fpout = popen(PAGER,"w"))==NULL) err_sys("popen error");

    while(fgets(line,MAXLINE,fpin)!=NULL){
        if(fputs(line,fpout) == EOF) err_sys("fputs error to pipe");
    }
    if(ferror(fpin)) err_sys("fgets error");
    if(pclose(fpout) == -1) err_sys("pclose error");

    exit(0);
}