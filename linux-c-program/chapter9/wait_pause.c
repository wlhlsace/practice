#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define UNHAPPEN 0
#define HAPPENED 1

int flag_happen;
void handler_sigint(int signo){
    flag_happen = HAPPENED;
}
int main(){
    if(signal(SIGINT, handler_sigint) == SIG_ERR){
        perror("signal");
        exit(1);
    }
    while(flag_happen == UNHAPPEN){
        pause();
    }
    printf("after event happened\n");
    return 0;
}
