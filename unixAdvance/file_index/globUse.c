#include "../include/apue.h"
#include <glob.h>
/***
 * 用于获取某个目录下的所有文件占用磁盘的空间
 * ***/

#define BUFSIZE 1024

int path_noloop(const char* path){
    // 去除.和..
    char *pos = strrchr(path,'/');
    if(pos){
        if((!strcmp("/.",pos))||(!strcmp("/..",pos))) return 0;
    }else if((!strcmp(".",path))||(!strcmp("..",path))) return 0;
    return 1;
}

int mydu(const char* path){
    // /a/b/c/f/g
    static char str[BUFSIZE] = "";
    glob_t globt; // {size_t gl_pathc; char **gl_pathv; size_t gl_offs;} glob_t
    int i = 0,ret = 0;
    struct stat buf;
    lstat(path,&buf);
    // path为目录文件
    if(S_ISDIR(buf.st_mode)){
        // 非隐藏文件
        snprintf(str,BUFSIZE,"%s/*",path);
        glob(str,0,NULL,&globt);
        // 隐藏文件，将两次解析的结果追加在一起，所以特殊要求使用glob_append
        glob(str,GLOB_ABEND,NULL,&globt);
        ret = buf.st_blocks;

        for(;i<globt.gl_pathc;i++){
            // 递归目录的时候要注意，目录并不是一个典型的树状结构，它是具有回路的，所以向下递归遇到.或..
            // 的时候不要进行递归了
            if(path_noloop(globt.gl_pathv[i])){
                ret+=mydu(globt.gl_pathv[i]);
            }
        }
        globfree(&globt); // 释放资源
    }else{
        ret = buf.st_blocks;
    }
    return ret;
}

int main(int argc, char** argv){
    printf("%d\n",mydu(argv[1])/2);
    exit(0);
}
