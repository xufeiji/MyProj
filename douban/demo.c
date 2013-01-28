#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc,char **argv)
{
	if (argc<2){
		printf( "Please input the hostName. Example:\n %s www.baidu.com\n ",argv[0]);
		return;
	}
	char *host = argv[1];
	struct hostent *site = NULL;
	struct sockaddr_in me;
	memset(&me, 0, sizeof(struct sockaddr_in));
				
	printf("%s\n",host);
	site = gethostbyname(host);
	memcpy(&me.sin_addr, site-> h_addr_list[0], site-> h_length);
	me.sin_family = AF_INET;
	me.sin_port = htons(80);
	int socket_des = socket(AF_INET,SOCK_STREAM,0);
	if (socket_des == -1)
	{
		printf("socket create error!!!");
		return 1;
	}
	if (connect(socket_des, (struct sockaddr *)&me,sizeof(struct sockaddr)) == -1)
	{
		printf("connect error!!!");
		return 1;
	}
																																
	char host_str[100]={0};
	sprintf(host_str,"Host: %s\n",host);
	send(socket_des,"GET / HTTP/1.0\n",strlen("GET / HTTP/1.0\n"),0);
	send(socket_des,host_str,strlen(host_str),0);
	send(socket_des,"\n",strlen("\n"),0);

	char buf[5] = {0};
	while (read(socket_des, buf, 1)> 0)
		printf( "%c ",buf[0]);
	printf( "\n ");
	close(socket_des);

	return 0;
}
