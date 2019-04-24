#include <stdio.h>
#include <signal.h>
#define UNHAPPEN 0
#define HAPPENED 1

int flag_happen;
void handler_sigint(int signo){
    flag_happen = HAPPENED;
}
int main(){
    printf("-----ALERT ! CPU 100%-----\n");
    if(signal(SIGINT, handler_sigint) == SIG_ERR){
        perror("signal");
        exit(1);
    }
    while(1){
        if(flag_happen == HAPPENED){
            printf("event happened\n");
            break;
        }
    }
    return 0;
}
