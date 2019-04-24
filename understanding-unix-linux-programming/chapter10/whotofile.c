#include<stdio.h>
void main(){
    int pid, fd;
    printf("run who into file\n");
    if((pid = fork()) == -1){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        printf("pid == 0\n");
        close(1);
        fd = creat("userlist", 0644);
        printf("create file: userlist, fd: %d", fd);    //TODO why, this line can't be print.
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    }
    if(pid != 0){
        wait(NULL);
        printf("Done running who\n");
    }
}
