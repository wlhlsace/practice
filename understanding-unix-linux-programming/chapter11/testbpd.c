#include<stdio.h>
#include<stdlib.h>
void main(){
    int p[2];
    if(pipe(p) == -1)   exit(1);
    if(write(p[0], "hello", 5) == -1)
        perror("write pipe[0] failed");
    else
        printf("write pipe[0] worked\n");
}
