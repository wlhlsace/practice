#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t pid;
    char* msg;
    int k;
    printf("process creation study\n");
    pid = fork();
    switch(pid){
        case 0:
            msg = "child run";
            k = 3;
            break;
        case -1: perror("FAILED");
                 break;
        default:
            msg = "parent run";
            k = 5;
             break;
    }
    while(k > 0){
        puts(msg);
        sleep(1);
        k--;
    }
    exit(0);
}
