#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define SHOWHOST
void show_info(struct utmp* utbufp);
void show_time(long timeval);

int main(){
    struct utmp *utbufp, *utmp_next();
    if(utmp_open(UTMP_FILE) == -1){
        perror(UTMP_FILE);
        exit(1);
    }
    while((utbufp = utmp_next()) != ((struct utmp*)NULL)){
        show_info(utbufp);
    }
    utmp_close();
    return 0;
}

void show_info(struct utmp* utbufp){
    if(utbufp->ut_type != USER_PROCESS){
        return;
    }
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    //printf("%10ld", utbufp->ut_time);
    show_time(utbufp->ut_time);
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp->ut_host);
#endif
    printf("\n");
}

void show_time(long timeval){
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp+4);
}
