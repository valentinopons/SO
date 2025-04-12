#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <signal.h> 
#include <unistd.h>

void programa(){
    int fd[2];
    pipe(fd);
    __pid_t pid1 = fork();
    if (pid1 == 0){
        close(fd[0]); // cierro lectura
        dup2(fd[1], STDOUT_FILENO); // ESPECIFICO QUE LA SALIDA DE LA TERMINAL SE ESCRIBA EN LA ENTRADA DEL PIPE
        char *args[] = {"ls", "-al", NULL};
        execvp("ls", args);  
        close(fd[1]);

    }
    __pid_t pid2 = fork();
    if (pid2 == 0){
        close(fd[1]); // cierro escritura
        dup2(fd[0],STDIN_FILENO);
        char *args[] = {"wc", NULL};  // Ejecuta 'wc'
        execvp("wc", args);
        close(fd[0]); 
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    
}

int main(){
    programa();
}