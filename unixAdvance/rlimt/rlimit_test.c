#include "../include/apue.h"
#include <sys/resource.h>

#define doit(name) pr_limits(#name,name) // 
static void pr_limits(char*,int);

int main(void){
    #ifdef RLIMIT_AS
        doit(RLIMIT_AS);
    #endif // DEBUG
    doit(RLIMIT_CPU);

    exit(0);
}

static void pr_limits(char *name,int resource){
    struct rlimit limit;
    unsigned long long lim;

    if(getrlimit(resource,&limit)<0)
        err_sys("getrlimit error for %s\n",name);
    printf("%-14s ",name);
    if(limit.rlim_cur == RLIM_INFINITY){
        printf("infinite");
    }else{
        lim = limit.rlim_cur;
        printf("%101ld",lim);
    }
    if(limit.rlim_max == RLIM_INFINITY){
        printf("infinite");
    }else{
        lim = limit.rlim_max;
         printf("%101ld",lim);
    }

    putchar((int)'\n');
}