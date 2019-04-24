#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t pid;
    printf("process creation study\n");
    pid = fork();
    switch(pid){
        case 0:
            while(1){
                printf("background process, PID: %d, PPID: %d\n", getpid(), getppid());
                sleep(3);
            }
                break;
        case -1: perror("FAILED");
                 break;
        default: printf("parent pid: %d, child pid: %d\n", getpid(), pid);
                 break;
    }
    exit(0);
}
