#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void handler(int s){
    write(1,"!",1);
}
struct point{
    int x,y;
}p;

int main(){
    p.x = 1;
    char c = '\72';
    int i = 0;
    signal(SIGINT,handler);
    for(i = 0;i<10;i++){
        write(1,"*",1);
        sleep(1);
    }
    return 0;
}