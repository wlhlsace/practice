#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    int a = 0;
    int* arr = malloc(sizeof(int) * 100);
    int i = 0;
    for(; i < 100; i++){
        arr[i] = 0;
    }
    pid = fork();

    switch(pid){
        case 0:
            //child
            printf("child a:");
            scanf("%d", &a);
            for(i = 0; i < 100; i++){
                arr[i] = 9;
            }
            while(1);
            break;
        case -1:
            perror("FAILED");
            break;
        default:
            //parent
            printf("parent");
            while(1);
            //scanf("%d", &a);
            break;
    }
    return 0;
}
