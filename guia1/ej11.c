#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <signal.h> 

void programa(){
    __pid_t padre = getpid();
    int fd1[2];
    int fd2[2];
    pipe(fd1); // fd[0] = lectura, fd[1] = escritura
    pipe(fd2);
    __pid_t hijo1 = fork();
    if (hijo1 == 0){
        close(fd1[1]);
        int numero_recibido;
        read(fd1[0],&numero_recibido,sizeof(int));
        printf("hijo recibe el numero: %d\n",numero_recibido);
        close(fd2[0]);

    }
    if (hijo1 >0){
        close(fd1[0]);
        printf("padre envia con pid: %d envia numero 10\n",getpid());
        int numero = 10;
        write(fd1[1], &numero, sizeof(int));

        wait(NULL);
        close(fd1[1]);
        
    }
    return 0;

    
}
int main(){
    programa();
    return 0;
}