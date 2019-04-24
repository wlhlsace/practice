#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t pid;
    printf("process creation study\n");
    pid = fork();
    switch(pid){
        case 0: printf("child pid: %d, parent pid: %d\n", getpid(), getppid());
                break;
        case -1: perror("FAILED");
                 break;
        default: printf("parent pid: %d, child pid: %d\n", getpid(), pid);
                 break;
    }
    exit(0);
}
