#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_json.h"
#include "json.h"
#include "print_book.h"


#define BUFSIZE (1024*1024)

int main(int argc,char **argv)
{
	struct obj * p_obj;
	char * recv_buf = (char *)malloc(sizeof(char) * BUFSIZE);
	if (recv_buf == 0)
	{
		perror("malloc");
		exit(1);
	}
	memset(recv_buf, 0, BUFSIZE);

#if 1
#if 0
	int fp = open("buf.txt", O_RDONLY);
	read(fp, recv_buf, BUFSIZE);
	close(fp);
	printf("%s\n", recv_buf);
#else
	get_json(recv_buf, "driver");
#endif
#else

	strcpy(recv_buf, "{\"firstName\": [\"123\", \"234\", 22, {\"hello\":[\"world\"], \"lin\":\"huanhuan\"}], \"lastName\":{\"coolboy4me\":\"helinshu\", \"huanhuan\":\"2B\"}, \"email\": {\"firstName\": \"Brett\", \"lastName\":\"McLaughlin\", \"email\": {\"coolboy4me\":\"helinshu\", \"huanhuan\":\"2B\"}}}");
#endif
	ana_json(recv_buf, sizeof recv_buf, &p_obj);
//{\"coolboy4me\":\"helinshu\", \"huanhuan\":\"2B\"}
	free(recv_buf);

	print_book(p_obj, 0);
	return 0;
}
