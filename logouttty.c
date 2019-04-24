#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

int main(int ac, char *av[]){
    printArgs(ac, av);
    logout_tty(av[1]);
}

int logout_tty(char *tty){
    int fd;
    struct utmp rec;
    int len = sizeof(struct utmp);
    int retval = -1;
    if((fd = open(UTMP_FILE, O_RDWR)) == -1){
        perror("open UTMP_FILE failed");
        return retval;
    }
    while(read(fd, &rec, len) == len){
        if(strncmp(rec.ut_line, tty, sizeof(rec.ut_line)) == 0){
            printf("find %s", tty);
            rec.ut_type = DEAD_PROCESS;
            //if(time(&rec.ut_time != -1)){//TODO why
            if(time(&rec.ut_time) != -1){//modified
                if(lseek(fd, -len, SEEK_CUR) != -1){
                    if(write(fd, &rec, len) == len){
                        retval = 0;
                        printf("logout %s", tty);
                    }
                }
            }
            break;
        }
    }
    if(close(fd) == -1){
        perror("close UTMP_FILE failed");
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
