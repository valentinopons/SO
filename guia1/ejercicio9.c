#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <signal.h> 

char s[10] = "si";
__pid_t ping_pid;
__pid_t pong_pid;

// DEVUELVO PONG
void handle_SIGUSR1(int sig) {
    printf("pong y mi numero de pid es: %d \n", getpid());
    
}

void pong(){
    ping_pid = getpid();
    pong_pid = fork();
    int i = 0;
    signal(SIGUSR1, handle_SIGUSR1);
    while (strcmp(s,"si") == 0){
        if (i<3){

            if (pong_pid == 0){ //hijo
                break;
                } 
            if (pong_pid > 0){ //padre
                printf("ping y mi numero de pid es: %d \n", pong_pid);
                kill(ping_pid, SIGUSR1);
                sleep(2);
            }   
            
            i++;
        }else{
            printf("quiere seguir? \n ");
            scanf("%s",s);
            i = 0;
        }       
    }
    if (pong_pid == 0){
        while (1)
        {}
        
    }
    
    kill(pong_pid, SIGTERM);
    

}
int main(){
    pong();
    return 0;
}
   
    
    
    
    
    
