#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void my_read(int fd, char* buf){
    while(read(fd, buf, BUFSIZ) > 0){
        printf("read:\n %s \n", buf);
        printf("#  #  #  #  #\n");
    }
}

void move_pointer(int fd, int offset, int mode){
    if(lseek(fd, offset, mode) == -1){
        perror("lseek");
        exit(1);
    }
    printf("lseek suc\n");
}

int main(){
    int fd;
    char buf[BUFSIZ];
    char* write_buf = "This is the write line\n";
    //int write_offset = 0;
    int write_offset = 10;

    //if((fd = open("testfile.txt", O_RDWR | O_APPEND)) == -1){
    if((fd = open("testfile.txt", O_RDWR)) == -1){
        perror("open testfile.txt");
        exit(1);
    }
    my_read(fd, buf);

    // if open file with O_APPEND, lseek didn't work.
    //move_pointer(fd, write_offset, SEEK_END);
    //move_pointer(fd, write_offset, SEEK_CUR);
    //move_pointer(fd, 100, SEEK_SET);
    // move pointer to behind EOF
    //move_pointer(fd, -100, SEEK_SET);
    // move pointer to before head
    move_pointer(fd, 0, SEEK_END);

    if(write(fd, write_buf, strlen(write_buf)) != strlen(write_buf)){
        perror("write");
        exit(1);
    }
    printf("write suc\n");

    move_pointer(fd, 0, SEEK_SET);
    my_read(fd, buf);

    close(fd);
    return 0;
}
