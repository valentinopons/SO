#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "constants.h"

int start1;
int generate_random_number(){
	return (rand() % 50);
}
void process(int fd[][2],int leftPipe[2],int rightPipe[2], int i, int n){
	printf("proceso normal \n");
	int k = 1;
	int num;
	
	
	//CIERRO PIPES QUE NO USO
	for (int j = 0; j < n; j++){
		if (fd[j][PIPE_WRITE] != rightPipe[PIPE_WRITE]) close(fd[j][PIPE_WRITE]);
		if (fd[j][PIPE_READ]  != leftPipe[PIPE_READ])   close(fd[j][PIPE_READ]);
	}
	
	while (1){
		k = read(leftPipe[PIPE_READ],&num, sizeof(num));
		if(k == 0){
			break;
		}
		sleep(1);

		printf("soy hijo numero: %i recibi: %i", i, num);
		num++;
		printf(" mando el numero: %i \n",num);
		write(rightPipe[PIPE_WRITE],&num,sizeof(num));
	}
		close(leftPipe[PIPE_READ]);
		close(rightPipe[PIPE_WRITE]);
		exit(0);
}

void special_process(int fd[][2],int leftPipe[2],int rightPipe[2],int n,int fd1[2], int fd2[2]){
	int secret_num = generate_random_number();
	printf("el numero especial es: %i \n", secret_num);

	int k;
	//CIERRO PIPES QUE NO USO
	for (int j = 0; j < n; j++){
		if (fd[j][PIPE_WRITE] != rightPipe[PIPE_WRITE]) close(fd[j][PIPE_WRITE]);
		if (fd[j][PIPE_READ]  != leftPipe[PIPE_READ])   close(fd[j][PIPE_READ]);
	}

	close(fd1[PIPE_WRITE]);
	close(fd2[PIPE_READ]);

	
	read(fd1[PIPE_READ], &k, sizeof(k));
	printf("soy EL ELEGIDO: %i recibi del padre: %i mando el numero: %i\n", start1, k,k+1);
	close(fd1[PIPE_READ]);
	k++;
	sleep(1);
	write(rightPipe[PIPE_WRITE],&k,sizeof(k));
	
	while(1){
		read(leftPipe[PIPE_READ],&k,sizeof(k));
		printf("soy hijo especial numero: %i recibi: %i mando el numero: %i\n", start1, k, k+1);
		sleep(1);
		if (k > secret_num){
			break;
		}
		k++;
		write(rightPipe[PIPE_WRITE],&k, sizeof(k));

	}
		write(fd2[PIPE_WRITE], &k, sizeof(k)); //mando resultado al padre
		close(fd2[PIPE_WRITE]);

		close(leftPipe[PIPE_READ]);
		close(rightPipe[PIPE_WRITE]);

	
	exit(0);
}

int main(int argc, char **argv)
{	
	//Funcion para cargar nueva semilla para el numero aleatorio
	srand(time(NULL));

	int status, pid, n, start, buffer;
	n = atoi(argv[1]);
	buffer = atoi(argv[2]);
	start = atoi(argv[3]);
	start1 = start;

	if (argc != 4){ printf("Uso: anillo <n> <c> <s> \n"); exit(0);}
    
  	/* COMPLETAR */
    printf("Se crearán %i procesos, se enviará el caracter %i desde proceso %i \n", n, buffer, start);
    
	//creo pipes
	int fd[n][2];
	int fd1[2]; // pipe que conecta padre con el elegido
	int fd2[2]; // pipe que conecta al elegido con el padre
	pipe(fd1);
	pipe(fd2);
	for (int i = 0; i < n; i++){
		pipe(fd[i]);
	}

	for (int i = 0; i < n; i++){
		pid_t child = fork();
		if (child == 0){
			if (i == start){
				if (i == 0){
					special_process(fd, fd[n-1], fd[i],n,fd1, fd2);
				} else {
					special_process(fd, fd[i-1], fd[i],n,fd1, fd2);
				}
				// ya hace exit dentro, no sigue
			} else if (i == 0){
				process(fd, fd[n-1], fd[i], i, n);
			} else {
				process(fd, fd[i-1], fd[i], i, n);
			}
			
			
		}
		sleep(1);
		
	}

	//cierro pipes del padre
	
	for (int i = 0; i < n; i++){
		close(fd[i][PIPE_READ]);
		close(fd[i][PIPE_WRITE]);
	}

	printf("Padre comienza!!!\n");
	printf("padre envia: %i\n", buffer);
	write(fd1[PIPE_WRITE], &buffer, sizeof(buffer)); //le mando al elegido el buffer para que comience
	close(fd1[PIPE_WRITE]);
	close(fd1[PIPE_READ]); // cierro  lectura para pipe padre -> elegido


	
	read(fd2[PIPE_READ], &buffer, sizeof(buffer));
	close(fd2[PIPE_READ]);
	close(fd2[PIPE_WRITE]);// cierro pipe escritura elegido -> padre

	printf("numero final es: %i",buffer);

	

    /* COMPLETAR */
	return(0);
}
