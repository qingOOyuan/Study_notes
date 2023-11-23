#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 100

int main(int argc, char **argv)
{
	int logfd = open("mylog", O_CREAT | O_WRONLY, 0644);

	mkfifo("fifo", 0666);

	int fifofd = open("fifo", O_RDWR);
	char buf[SIZE];
	int ret;

	while(1)
	{
		bzero(buf, SIZE);
		ret = read(fifofd, buf, SIZE);
		printf("ret = %d\n",ret);
		
		write(logfd, buf, strlen(buf));
	}

	return 0;
}
