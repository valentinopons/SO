#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
	int server_socket;
    struct sockaddr_un server_addr;
	char cuenta[10];
	int res;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error");
        exit(1);
    }
	while (1){
		printf("introduzca la formula a calcular: ");
		scanf("%s", cuenta);
		write(server_socket, &cuenta, sizeof(cuenta));
		if (!strcmp(cuenta, "exit")){
			break;
		}
		
		recv(server_socket,&res,sizeof(res),0);
		printf("el resultado es: %d\n", res);
	}
	
	exit(0);

}
