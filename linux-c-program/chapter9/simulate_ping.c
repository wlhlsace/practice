#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void send_ip(){
    printf("send request...\n");
}
void recv_ip(){
    while(1);
}
void handler_sigalarm(int signo){
    send_ip();
    alarm(2);
}
int main(){
    signal(SIGALRM, handler_sigalarm);
    raise(SIGALRM);
    recv_ip();
    return 0;
}
