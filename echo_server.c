/* A simple echo server using TCP */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h> 
#include <unistd.h>

#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		512	/* buffer length */

int echod(int);
void reaper(int);

int main(int argc, char **argv)
{
	int 	sd, new_sd, client_len, port;
	struct	sockaddr_in server, client;

	switch(argc){
	case 1:
		port = SERVER_TCP_PORT;
		break;
	case 2:
		port = atoi(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %d [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	/* Bind an address to the socket	*/
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}

	/* queue up to 5 connect requests  */
	listen(sd, 5);

	(void) signal(SIGCHLD, reaper);

	while(1) {
	  client_len = sizeof(client);
	  new_sd = accept(sd, (struct sockaddr *)&client, &client_len);
	  if(new_sd < 0){
	    fprintf(stderr, "Can't accept client \n");
	    exit(1);
	  }
	  switch (fork()){
	  case 0:		/* child */
		(void) close(sd);
		exit(echod(new_sd));
	  default:		/* parent */
		(void) close(new_sd);
		break;
	  case -1:
		fprintf(stderr, "fork: error\n");
	  }
	}
}
/*	echod program	*/
int echod(int sd){


struct PDU{
	  char type;
	  unsigned int length;
	  char data[300];
	} client_send, client_receive;	


FILE *fo;
FILE *fi;
char file_data[300];


while(1){

read(sd, &client_receive, BUFLEN);
	  client_receive.data[client_receive.length]='\0';
	    printf("\nRECV:%c, %d, %s \n", client_receive.type, client_receive.length, client_receive.data);
	  //Initiating download request from client
	  if (client_receive.type == 'D'){
	  printf("File download requested.\n");
	  //Check if file exists
	  if (access(client_receive.data,F_OK)!=-1){
	  printf("Checking if file exists.\n");
	  client_send.type = 'F';
	  fo = fopen(client_receive.data, "rb");
	  printf("Retreiving data from file to send to client.\n");
	  fread(file_data, 1,300,fo);
	  strcpy(client_send.data, file_data);
	  
	
	  
	 
	  
	client_send.length = strlen(client_send.data);
	printf("Sending file contents to client.\n");
	write(sd, &client_send, sizeof(client_send));
	fclose(fo);
	  
	  //Send error message to client when file can't be downloaded
	  }else{
	  printf("Unable to send file to client.\n");
		client_send.type='E';
		strcpy(client_send.data,"Unable to retreive file on server.\n");
		client_send.length=strlen(client_send.data);
		write(sd,&client_send,sizeof(client_send));
	  
	  }
	  
	  
	  //Reply back to client when client initiates upload request
	  }else if(client_receive.type == 'U'){
	  client_send.type='R';
	  strcpy(client_send.data, "Server is ready.\n");
	  
	  client_send.length=strlen(client_send.data);
	  write(sd,&client_send,sizeof(client_send));
	  
	  //Initiate upload form client
	  }else if(client_receive.type == 'F'){
	  
	  fi = fopen("uploaded.txt", "ab");
	 	printf("Downloading file from client.\n");
	   	fwrite(client_receive.data,1,strlen(client_receive.data),fi);
	   	fclose(fi);
	  //Initiate directory change
	  }else if(client_receive.type == 'P'){
	  
	  
	  //Initiate directory change request from client
	   if (chdir(client_receive.data)==0){
	      printf("Directory changed.\n");
	      client_send.type='R';
	      strcpy(client_send.data,"Successfully changed server directory.\n");
	      client_send.length=strlen(client_send.data);
	    }
	    else {
	      printf("Failed to change directory\n");
	      client_send.type='E';
	      strcpy(client_send.data,"Failed to change server directory.");
	      client_send.length=strlen(client_send.data);
	    }
	    write(sd,&client_send,sizeof(client_send));
	  
	  //Initiate file name requests from client
	  }else if(client_receive.type == 'L'){
	  printf("Retreiving file names from directory.\n");
	  char filenames[300]="";
	  
	DIR           *d;
  	struct dirent *dir;
  	chdir(client_receive.data);
  	d = opendir(".");
  if (access(client_receive.data,F_OK)!=-1){
  if (d){
    while ((dir = readdir(d)) != NULL){
      //printf("%s\n", dir->d_name);
      strcat(filenames, dir->d_name);
      strcat(filenames, " ");
    }

    closedir(d);
    client_send.type = 'I';
  strcpy(client_send.data, filenames);

  client_send.length= strlen(client_send.data);
  printf("Sending file names to client.\n");
write(sd,&client_send,sizeof(client_send));	  
  }
  
  }else{
  printf("Unable to retreive filenames.\n");
  client_send.type='E';
		strcpy(client_send.data,"Unable to retreive filenames on server.\n");
		client_send.length=strlen(client_send.data);
		write(sd,&client_send,sizeof(client_send));
  
  }
  
  
}else{
	printf("Invalid operation.\n");
	client_send.type='E';
		strcpy(client_send.data,"Invalid opereation.\n");
		client_send.length=strlen(client_send.data);
		write(sd,&client_send,sizeof(client_send));
}



}

	

	return(0);
}

/*	reaper		*/
void	reaper(int sig)
{
	int	status;
	while(wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}
