#include <signal.h>
#include <stdio.h>
#include "send_data_signo_ptr_struct.h"

void handler_sigint(int signo, siginfo_t* siginfo, void* pvoid){
    sdsptr* ptr;
        /**
        = malloc(sizeof(sdsptr));
    if(ptr == NULL){
        printf("malloc fail\n");
        exit(1);
    }
    **/
    //ptr = siginfo->si_ptr;
    sigval_t sigval = siginfo->si_value;
    ptr = sigval.sival_ptr;
    printf("recv SIGINT, the pointer data value is: a = %d, b = %c\n", ptr->a, ptr->b);
}
int main(){
    struct sigaction act;
    act.sa_sigaction = handler_sigint;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act, NULL);
    while(1);
    return 0;
}
