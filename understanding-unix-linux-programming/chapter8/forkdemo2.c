#include<stdio.h>
void main(){
    printf("First: my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("Last: my pid is %d\n", getpid());
}
