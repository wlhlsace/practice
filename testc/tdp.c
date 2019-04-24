#include<stdio.h>
#include<stdlib.h>
typedef struct{
    char a;
    int b;
}TestStruct;
void main(){
    TestStruct* tsp;
    TestStruct* tsp2;
    tsp = malloc(sizeof(TestStruct));
    tsp -> a = 'a';
    tsp -> b = 1;
    printf("1.tsp: %d\n", tsp);
    printf("1.&tsp:  %x\n", &tsp);
    free(tsp);
    printf("1.tsp: %d\n", tsp);
    printf("1.&tsp:  %x\n", &tsp);
    tsp2 = malloc(sizeof(TestStruct));
    tsp2 -> a = 'c';
    tsp2 -> b = 3;
    printf("1.tsp2: %d\n", tsp2);
    printf("1.&tsp2:  %x\n", &tsp2);
//    free(tsp2);
    tsp = malloc(sizeof(TestStruct));
    tsp -> a = 'b';
    tsp -> b = 2;
    printf("2.tsp: %d\n", tsp);
    printf("2.&tsp:  %x\n", &tsp);
}
