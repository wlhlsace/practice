#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void my_err(const char* err_string){
    perror(err_string);
    exit(1);
}
void handler_sigint(int signo){
    printf("recv SIGINT\n");
}
int main(){
    sigset_t newmask, oldmask, pendmask;
    if(signal(SIGINT, handler_sigint) == SIG_ERR){
        my_err("signal");
    }
    sleep(5);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        my_err("sigprocmask");
    }else{
        printf("SIGINT blocked\n");
    }
    sleep(10);

    if(sigpending(&pendmask) < 0){
        my_err("sigpending");
    }
    switch(sigismember(&pendmask, SIGINT)){
        case 0:
            printf("SIGINT is not pending\n");
            break;
        case 1:
            printf("SIGINT pending\n");
            break;
        case -1:
            my_err("sigismember");
            break;
        default:
            break;
    }

    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        my_err("sigprocmask");
    }else{
        printf("SIGINT unblocked\n");
    }

    while(1);
    return 0;
}
