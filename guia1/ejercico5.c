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
 void soyYo(char* nombre){
    printf("soy %s y mi pid es: %d\n", nombre ,getpid());
    exit(0);
 }
void imprimirFamilia(){
    printf("soy Abrham y mi pid es: %d\n", getpid() );
    __pid_t pid = fork();
    if (pid == 0)
    {
        printf("soy Homero y mi pid es: %d\n", getpid());
        
        __pid_t bart = fork();
        if (bart == 0)
        {
            soyYo("bart");
        }
        __pid_t lisa = fork();
        if (lisa == 0)
        {
            soyYo("lisa");
        }
        __pid_t magie = fork();
        if ( magie == 0)
        {
            soyYo("magie");
        }
        
        
    }

    
}


int main(){
    imprimirFamilia();
    return 0;
}