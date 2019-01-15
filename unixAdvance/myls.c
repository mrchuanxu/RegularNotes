#include "include/apue.h"
#include <fcntl.h>
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc,char* argv[]){
    umask(0);
    if(creat("foo",RWRWRW)<0)
        err_sys("creat error for foo");
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH); // umask禁止所有组和其他用户的访问权限
    if(creat("bar",RWRWRW)<0)
        err_sys("creat error for bar");
    exit(0);
}
/***
 * 所以实际上，umask是用来禁止权限的
 * ***/