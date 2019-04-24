#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define UNHAPPEN 0
#define HAPPENED 1

int flag_happen;
void my_err(const char* err_string){
    perror(err_string);
    exit(1);
}
void handler_sigint(int signo){
    flag_happen = HAPPENED;
}
int main(){
    sigset_t newmask, oldmask, zeromask;
    if(signal(SIGINT, handler_sigint) == SIG_ERR){
        my_err("signal");
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGINT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        my_err("sigprocmask");
    }else{
        printf("SIGINT blocked\n");
    }
    while(flag_happen == UNHAPPEN){
        sigsuspend(&zeromask);
    }
    printf("after event happened\n");

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        my_err("sigprocmask");
    }

    return 0;
}
