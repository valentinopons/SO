#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

/*
       Abraham
          |
        Homero     
    |    |     |
    Bart  Lisa  Maggie


*/

    int exec(const char* arg){
    if (arg == NULL)
    {
        return 0;
    }else{
        execl(arg);
    }
    return 1;
    
}

 void soyYo(char* nombre){
    printf("soy %s y ya termine", nombre);
    exit(0);
 }

void imprimirFamilia(){
    __pid_t pid = fork();
    if (pid == 0){    
        __pid_t bart = fork();
        if (bart == 0){
            soyYo("bart");
        }
        __pid_t lisa = fork();
        if (lisa == 0){
            soyYo("lisa");
        }
        __pid_t magie = fork();
        if ( magie == 0){
            soyYo("magie");
        }
        __pid_t pidh;
        while (pidh = wait(NULL) > 0){ //wait = -1 si todos los hijos muertos, wait > 0 si quedan
            printf("termina hijo \n");
        }
        printf("termnina homero \n");
        
    }else{
        wait(NULL);
        printf("Abrham termino");
    }
    
    

    
}


int main(){
    imprimirFamilia();
    return 0;
}