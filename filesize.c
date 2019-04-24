#include<stdio.h>
#include<sys/stat.h>

int main(){
    struct stat infobuf;
    if(stat("/etc/passwd", &infobuf) == -1){
        perror("error");
    }else{
        printf("file size: %d\n", infobuf.st_size);
    }
}
