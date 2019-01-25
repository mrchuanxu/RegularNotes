#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
    pid_t pid;
    int i = 0;
    for(i = 0;i<10;i++){
        fflush(NULL);
        pid = fork();
        if(pid<0){
            perror("fork() error");
            exit(1);
        }else if(0==pid){
            printf("pid = %d\n",getpid());
            sleep(10);
            exit(0);
        }
    }
    return 0;
}