/***************************************************************************
                          main.c  -  client
    copyright            : (C) 2024 by A.Fontquerni & S.Bernadas
    email                : afontquerni@euss.cat / sbernadas@euss.cat
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>


#define REQUEST_MSG_SIZE	1024*256
#define SERVER_PORT_NUM		80



/************************
* TCPClient
*/

int main(int argc, char *argv[]){
	
	char ip[64];
	char url[64];
	int opt = 0;
	int check = 0;

	static struct option long_options[] = {
		{"url", required_argument, 0, 'u'},
		{"ip", required_argument, 0, 'i'},
		{0, 0}
    };

	int long_index = 0;
	while ((opt = getopt_long(argc, argv, "u:i:", long_options, &long_index)) != -1) {
		switch (opt) {
		case 'u':
		sprintf (url, optarg);
			break;
		case 'i':
		sprintf (ip, optarg);
			break;
		default:
		printf("Getopt error1");;
			}}

    if (check == 0) {
		printf("Getopt error2");
		exit(EXIT_FAILURE);
    }

    else {
		
	struct sockaddr_in	serverAddr;
	char	    serverName[] = "192.168.11.249"; //Adreça IP on està el client
	int			sockAddrSize;
	int			sFd;
	int 		result;
	char		buffer[REQUEST_MSG_SIZE];
	char 		missatge[1024];
	//char buffer[1024];

	/*Crear el socket*/
	sFd=socket(AF_INET,SOCK_STREAM,0);

	/*Construir l'adreça*/
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero ((char *)&serverAddr, sockAddrSize); //Posar l'estructura a zero
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons (SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = inet_addr(serverName);

	/*Conexió*/
	result = connect (sFd, (struct sockaddr *) &serverAddr, sockAddrSize);
	if (result < 0)
	{
		printf("Error en establir la connexió\n");
		exit(-1);
	}
	printf("\nConnexió establerta amb el servidor: adreça %s, port %d\n",	inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	/*Rebre*/
	result = read(sFd, buffer, REQUEST_MSG_SIZE);
	printf("Missatge rebut del servidor(bytes %d): \n{%s}\n", result, buffer);
	sprintf(missatge, "Direccio IP del servidor web: %s\n", ip);
	printf(missatge);
	
	/*Enviar*/
	memset(buffer, 0, REQUEST_MSG_SIZE);
	memset(missatge, 0, 1024);
	sprintf(missatge, "HELO 1457962\n");
	sprintf(buffer,missatge); //Copiar missatge a buffer
	result = write(sFd, buffer, strlen(buffer));
	printf("Missatge enviat a servidor(bytes %d): \n{%s}\n\n",	result, buffer);
	
	/*Rebre*/
	result = read(sFd, buffer, REQUEST_MSG_SIZE);
	printf("Missatge rebut del servidor(bytes %d): \n{%s}\n", result, buffer);
	
	/*Enviar*/
	memset(buffer, 0, REQUEST_MSG_SIZE);
	sprintf(missatge, "GET %s HTTP1.0\n", url);
	sprintf(buffer,missatge); //Copiar missatge a buffer
	result = write(sFd, buffer, strlen(buffer));
	printf("Missatge enviat a servidor(bytes %d): \n{%s}\n\n",	result, buffer);


	/*Rebre*/
	memset(buffer, 0, REQUEST_MSG_SIZE);
	result = read(sFd, buffer, REQUEST_MSG_SIZE);
	printf("Missatge rebut del servidor(bytes %d): \n{%s}\n",	result, buffer);

	/*Tancar el socket*/
	close(sFd);

	return 0;
	}
}
