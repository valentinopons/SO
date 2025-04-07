#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <signal.h> 

void programa(){
    __pid_t pid = fork();
    if (pid == 0){
        printf("soy juan\n");
    }
    
    
}