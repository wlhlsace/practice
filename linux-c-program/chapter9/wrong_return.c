#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf env;
void handler_sigrtmin15(int signo){
    printf("recv SIGRTMIN+15\n");
    longjmp(env, 1);
}
void handler_sigrtmax15(int signo){
    printf("recv SIGRTMIN-15\n");
    longjmp(env, 2);
}
int main(){
    switch(setjmp(env)){
        case 0:
            // invoke setjmp just return 0
            break;
        case 1:
            printf("return from SIGRTMIN+15\n");
            break;
        case 2:
            printf("return from SIGRTMIN-15\n");
            break;
        default:
            break;
    }

    signal(SIGRTMIN+15, handler_sigrtmin15);
    signal(SIGRTMIN-15, handler_sigrtmax15);

    while(1);
    return 0;
}
