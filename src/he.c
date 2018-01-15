#include"he.h"
struct client_info {
	int sockno;
	char ip[INET_ADDRSTRLEN];
};

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *semsg(void *sock)
{
	struct client_info cl = *((struct client_info *)sock);
	int i,y,len; char msg[500],res[500]; int cli;
	wr: printf("\nClient sock :");
		scanf("%d",&cli);
	printf("\nMessage:");
	memset(msg,'\0',sizeof(msg));
	memset(res,'\0',sizeof(res));
	while(1)
	{	
		
		
		scanf("%s",msg);
		
		strcpy(res,"Server:");
		strcat(res,msg);
		len = write(cli,res,strlen(res));
		if(len < 0)
		{
			perror("message not sent");
			exit(1);
		}
		
		if(msg[0]=='0') goto wr;
		memset(msg,'\0',sizeof(msg));
		memset(res,'\0',sizeof(res));
		
	}
		
	
}

void *recvmg(void *sock)
{
	struct client_info cl = *((struct client_info *)sock);
	char msg[500],res[500];
	int len;
	int i;
	int j;
	
	while((len = recv(cl.sockno,msg,500,0)) > 0) {
		msg[len] = '\0';
		printf("\n%s",msg);
		
		
		memset(msg,'\0',sizeof(msg));
	}
	
	pthread_mutex_lock(&mutex);
	printf("%s disconnected\n",cl.ip);
	
	
	
	pthread_mutex_unlock(&mutex);
}
void *recvmg2(void *sock)
{
	int their_sock = *((int *)sock);
	char msg[500];
	int len;
	while((len = recv(their_sock,msg,500,0)) > 0) {
		msg[len] = '\0';
		printf("\n%s",msg);
		//fputs(msg,stdout);
		memset(msg,'\0',sizeof(msg));
	}
}

