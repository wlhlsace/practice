#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void my_err(const char* err_string, int line){
    fprintf(stderr, "line: %d ", line);
    perror(err_string);
    exit(1);
}

int my_read(int fd){
    int len;
    int ret;
    int i;
    char read_buf[64];
    if(lseek(fd, 0, SEEK_END) == -1){
        perror("lseek");
    }
    if((len = lseek(fd, 0, SEEK_CUR)) == -1){
        perror("lseek");
    }
    if((lseek(fd, 0, SEEK_SET)) == -1){
        perror("lseek");
    }
    printf("len: %d\n", len);
    if((ret = read(fd, read_buf, len)) < 0){
        perror("read");
    }
    for(i = 0; i < len; i++){
        printf("%c", read_buf[i]);
    }
    printf("\n");

    return ret;
}

int main(){
    int fd;
    char write_buf[32] = "Hello world";
    if((fd = open("example_63.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1){
        perror("open");
    }else{
        printf("create file success\n");
    }
    if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf)){
        perror("write");
    }
    my_read(fd);

    printf("/*------------------*/\n");
    if(lseek(fd, 10, SEEK_END) == -1){
        perror("lseek");
    }
    if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf)){
        perror("write");
    }
    my_read(fd);

    close(fd);
    return 0;
}
