#include"he.h"
struct client_info {
	int sockno;
	char ip[INET_ADDRSTRLEN];
};
int clients[100];
int n=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void semsg(int curr)
{
	int i,len; char msg[500],res[500]; int cli;
	
	if(fgets(msg,500,stdin) > 0) 
	{
		strcpy(res,"Server:");
		strcat(res,msg);
		len = write(curr,res,strlen(res));
		if(len < 0)
		 {
			perror("message not sent");
			exit(1);
		}
		memset(msg,'\0',sizeof(msg));
		memset(res,'\0',sizeof(res));
	}
		
	
}
void *recvmg(void *sock)
{
	struct client_info cl = *((struct client_info *)sock);
	char msg[500];
	int len;
	int i;
	int j;
	while((len = recv(cl.sockno,msg,500,0)) > 0) {
		msg[len] = '\0';
		printf("\n%s",msg);
		semsg(cl.sockno);
		memset(msg,'\0',sizeof(msg));
	}
	//semsg(cl.sockno);
	pthread_mutex_lock(&mutex);
	printf("%s disconnected\n",cl.ip);
	for(i = 0; i < n; i++) {
		if(clients[i] == cl.sockno) {
			j = i;
			while(j < n-1) {
				clients[j] = clients[j+1];
				j++;
			}
		}
	}
	n--;
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

