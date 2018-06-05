/* A simple echo client using TCP */
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>



#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		512	/* buffer length */

int main(int argc, char **argv){
	
	int 	sd, port;
	struct	hostent		*hp;
	struct	sockaddr_in server;
	char	*host;
	FILE *fi;
	FILE *fo;
	
	
	
	char file_data[300];
	
	struct PDU{
	  char type;
	  unsigned int length;
	  char data[300];
	} server_send, server_receive;
	

	switch(argc){
	case 2:
		host = argv[1];
		port = SERVER_TCP_PORT;
		break;
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (hp = gethostbyname(host)) 
	  bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	else if ( inet_aton(host, (struct in_addr *) &server.sin_addr) ){
	  fprintf(stderr, "Can't get server's address\n");
	  exit(1);
	}

	/* Connecting to sd the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
	  fprintf(stderr, "Can't connect \n");
	  exit(1);
	}

	while(1){
	
	
	//Wait for user command
	printf("Command: (Type) (Argument)\n");
	  scanf(" %c %s", &server_send.type, server_send.data);
	  server_send.length=strlen(server_send.data);
	  
	  
	
	//send pdu to server
	write(sd, &server_send, sizeof(server_send));

	//receive pdu from server
	read(sd, &server_receive, BUFLEN);
	
	server_receive.data[server_receive.length]='\0';
	
	//Downloading file from server
	if(server_receive.type=='F'){
		fi = fopen("downloaded.txt", "ab");
	 	printf("Downloading file from server.\n");
	   	fwrite(server_receive.data,1,strlen(server_receive.data),fi);
	   	fclose(fi);
	  
	  //Receiving ready signal from server 	
	 }else if(server_receive.type=='R'){
	 
	
	 //If server is ready do upload
	 if(server_send.type == 'U'){
	 
	  printf("%s\n", server_receive.data);
	 //Check if file exists
	   if (access(server_send.data,F_OK)!=-1){
	  
	  server_send.type = 'F';
	  fo = fopen(server_send.data, "rb");
	  printf("Retreiving data from file to send to server.\n");
	  fread(file_data, 1,300,fo);
	  strcpy(server_send.data, file_data);
	server_send.length = strlen(server_send.data);
	printf("Sending file contents to server.\n");
	write(sd, &server_send, sizeof(server_send));
	fclose(fo);
	 
	 
	//Error message to client if file can't be uploaded
	}else{
	  printf("Unable to upload file to server.\n");
		
	  
	}
	
	//Display server message which indiates if directory change was made or not
	}else if(server_send.type == 'P'){
		 printf("%s\n", server_receive.data);
		 
	}

	

	
//Shows all files names in requested directory
}else if(server_receive.type=='I'){

printf("%s\n", server_receive.data);
//Prints any error messages sent from server
}else if (server_receive.type=='E'){
printf("%s\n", server_receive.data);
}
}
}
