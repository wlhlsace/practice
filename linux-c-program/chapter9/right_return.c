#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#define ENV_UNSAVE 0
#define ENV_SAVED 1

int flag_saveenv = ENV_UNSAVE;
jmp_buf env;

void handler_sigrtmin15(int signo){
    if(flag_saveenv == ENV_UNSAVE)
        return;
    printf("recv SIGRTMIN+15\n");
    sleep(5);
    printf("in handler_sigrtmin15, after sleep\n");
    siglongjmp(env, 1);
}

int main(){
    switch(sigsetjmp(env, 1)){
        case 0:
            // invoke setjmp just return 0
            printf("case 0\n");
            flag_saveenv = ENV_SAVED;
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        default:
            break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);

    signal(SIGTERM, handler_sigrtmin15);

    while(1);
    return 0;
}
