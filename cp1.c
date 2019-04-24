#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644
void oops(char *, char *);

int main(int ac, char *av[]){
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    if(ac != 3){
        fprintf(stderr, "usage: %s source\n", *av);
        exit(1);
    }
    if((in_fd = open(av[1], O_RDONLY)) == -1){
        oops("can't open", av[1]);
    }
    if((out_fd = creat(av[2], COPYMODE)) == -1){
        oops("can't creat", av[2]);
    }
    printf("ori: %s, des: %s\n", av[1], av[2]);
    printf("infd: %d\n", in_fd);
    printf("outfd: %d\n", out_fd);
    //char a;
    //scanf("get:", &a);
    while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0){
        if((write(out_fd, buf, n_chars)) != n_chars){
            oops("err write", av[2]);
        }
        if(n_chars == -1){
            oops("err read", av[1]);
        }
    }
    if(close(in_fd) == -1 || close(out_fd) == -1){
        oops("err close", "");
    }
}

void oops(char *s1, char *s2){
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(2);
}