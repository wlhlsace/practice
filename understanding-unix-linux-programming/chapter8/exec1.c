#include<stdio.h>

void main(){
    char *arglist[3];
    arglist[0] = "ls";
    arglist[1] = "-1";
    arglist[2] = 0;
    printf("*** about to exec ls -l\n");
    execvp("ls", arglist);
    printf("*** ls is done.\n");
}
