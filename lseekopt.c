#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define MYWRITE
#define MOVEOFFSET 100

int main(int ac, char *av[]){
    printArgs(ac, av);
    readfile(av[1]);
}

int readfile(char *fn){
    int fd;
    int retval = -1;
    int len = 20;
    char buf[1024];
#ifdef MYWRITE
    if((fd = open(fn, O_RDWR)) == -1){
#else
    if((fd = open(fn, O_RDONLY)) == -1){
#endif
        perror("open file failed");
        return retval;
    }
    if(read(fd, &buf, len) != len){
        perror("read file failed");
        return myclose(fd, -1);
    }
    printf("read: %s\n", buf);
    
    if(lseek(fd, MOVEOFFSET, SEEK_END) == -1){
        perror("lseek 100 failed");
        return myclose(fd, -1);
    }
#ifdef MYREAD
    if(read(fd, &buf, len) != len){
        perror("after move read file failed");
        return myclose(fd, -1);
    }
    printf("after move read: %s\n", buf);
#endif
#ifdef MYWRITE
    char mwc[] = "THE TEST WRITE STR";
    if(write(fd, &mwc, sizeof(mwc)) != sizeof(mwc)){
        perror("after move write file failed");
        return myclose(fd, -1);
    }
    printf("after move write SUC\n");
#endif
    
    return myclose(fd, 0);
}

int myclose(int fd, int retval){
    if(close(fd) == -1){
        perror("close file failed");
        retval = -1;
    }
    return retval;
}

int printArgs(int argc, char **argv){
    int i;
    printf("argc = %d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
}
