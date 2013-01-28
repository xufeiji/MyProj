#include "get_json.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>



void p(char *msg)
{
#if 0
	printf("%s\n", msg);
#endif
}

void get_json(char* recv_buf, char* key)
{
	char * p_buf;
	FILE * fp;
	char send_buf[100] =  "GET https://api.douban.com/v2/book/search";
	char *host = "api.douban.com";
	struct hostent *site = NULL;
	struct sockaddr_in me;
	memset(&me, 0, sizeof(struct sockaddr_in));
				
	site = gethostbyname(host);
	if (site == NULL)
	{
		perror("gethostbyname");
	}
	p("gethostbyname");
	memcpy(&me.sin_addr, site-> h_addr_list[0], site-> h_length);
	p("memcpy");
	me.sin_family = AF_INET;
	me.sin_port = htons(80);
	int socket_des = socket(AF_INET,SOCK_STREAM,0);

	p("socket");
	if (socket_des == -1)
	{
		printf("socket create error!!!");
		return ;
	}

	p("connect");	
	if (connect(socket_des, (struct sockaddr *)&me,sizeof(struct sockaddr)) == -1)
	{
		printf("connect error!!!");
		return ;
	}
			
	p("send");
	sprintf(send_buf, "%s?q=%s\n", send_buf, key);
	send(socket_des,send_buf,strlen(send_buf),0);
	send(socket_des,"\n",strlen("\n"),0);

	char buf[5] = {0};
	p("read");
	p_buf = recv_buf;
	while (read(socket_des, buf, 1)> 0)
	{
		sprintf(p_buf++, "%c", buf[0]);
	}
	printf( "%s\n", recv_buf);
	fp = fopen("buf.txt", "w");
	if (fp == 0)
		exit(1);
	fprintf(fp, recv_buf);
	fclose(fp);
	p("close");
	close(socket_des);
}
