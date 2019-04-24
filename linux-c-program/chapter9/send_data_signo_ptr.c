#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "send_data_signo_ptr_struct.h"

int main(int argc, char** argv){
    union sigval value;
    int signum = SIGTERM;
    pid_t pid;
    int i;
    sdsptr* ptr = malloc(sizeof(sdsptr));
    if(ptr == NULL){
        printf("malloc fail");
        exit(1);
    }
    ptr->a = 5;
    ptr->b = 'a';
    value.sival_ptr = (void*)ptr;

    if(argc != 5){
        printf("./send_data_signo_ptr <-s signum> [-p][pid]\n");
        exit(1);
    }
    for(i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-s")){
            signum = atoi(argv[i + 1]);
            continue;
        }
        if(!strcmp(argv[i], "-p")){
            pid = atoi(argv[i + 1]);
            continue;
        }
    }
    if(sigqueue(pid, signum, value) < 0){
        perror("sigqueue");
        exit(1);
    }

    /*
    free(ptr);
    ptr = NULL;
    */

    return 0;
}
