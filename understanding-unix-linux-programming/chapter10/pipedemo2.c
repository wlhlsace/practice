#include<stdio.h>
#include<stdlib.h>
#define CHILD_MESS  "I want cookie\n"
#define PAR_MESS    "testing ... \n"
#define oops(m, x)  {perror(m); exit(x);}
void main(){
    int pipefd[2];
    int len;
    char buf[BUFSIZ];
    int read_len;
    if(pipe(pipefd) == -1){
        oops("can't pipe", 1);
    }
    switch(fork()){
        case -1:
            oops("can't fork", 2);
        case 0:
            len = strlen(CHILD_MESS);
            while(1){
                if(write(pipefd[1], CHILD_MESS, len) != len){
                    oops("child write pipefd[1]", 3);
                }
                sleep(5);
            }
        default:
            len = strlen(PAR_MESS);
            while(1){
                if(write(pipefd[1], PAR_MESS, len) != len){
                    oops("parent write pipefd[1]", 4);
                }
                sleep(1);
                read_len = read(pipefd[0], buf, BUFSIZ);
                if(read_len < 0)    break;
                write(1, buf, read_len);
            }
    }
}
