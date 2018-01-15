#include"he.h"
void *semsg(void *sock);
void *recvmg(void *sock);
extern pthread_mutex_t mutex;
extern int clients[100],n;
struct client_info {
	int sockno;
	char ip[INET_ADDRSTRLEN];
	
};
int main(int argc,char** argv)
{
	struct sockaddr_in my_addr,their_addr;
	int my_sock;
	int their_sock;
	socklen_t their_addr_size;
	int portno;
	pthread_t sendt,recvt;
	char msg[500];
	int len;
	struct client_info cl,c[100];
	char ip[INET_ADDRSTRLEN];
	if(argc > 2) {
		printf("too many arguments");
		exit(1);
	}
	portno = atoi(argv[1]);
	my_sock = socket(AF_INET,SOCK_STREAM,0);
	memset(my_addr.sin_zero,'\0',sizeof(my_addr.sin_zero));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(portno);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	their_addr_size = sizeof(their_addr);
	char res[600];
	if(bind(my_sock,(struct sockaddr *)&my_addr,sizeof(my_addr)) != 0) {
		perror("binding unsuccessful");
		exit(1);
	}

	if(listen(my_sock,5) != 0) {
		perror("listening unsuccessful");
		exit(1);
	}

	while(1)
	 {

		if((their_sock = accept(my_sock,(struct sockaddr *)&their_addr,&their_addr_size)) < 0) 
		{
			perror("accept unsuccessful");
			exit(1);
		}
		pthread_mutex_lock(&mutex);
		inet_ntop(AF_INET, (struct sockaddr *)&their_addr, ip, INET_ADDRSTRLEN);
		printf("%s connected to sock %d\n",ip,their_sock);
		cl.sockno = their_sock;
		strcpy(cl.ip,ip);
		clients[n] = their_sock;
		n++;
		pthread_create(&recvt,NULL,recvmg,&cl);
		pthread_create(&sendt,NULL,semsg,&cl);
		
		//pthread_join(recvt,NULL);

		pthread_mutex_unlock(&mutex);
	}
	return 0;
}
