#include <stdio.h> 
#include <unistd.h> 
int main(int argc, char* argv[]) 
{ 
   fork(); 
   fork() && fork() || fork(); 
   fork(); 
   printf("+\n");
   return 0; 
} 
