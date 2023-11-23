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
#include <time.h>

#define SIZE 100

int main(int argc, char **argv)
{
	char msg[SIZE];
	time_t t;

	int fifofd = open("fifo", O_WRONLY);

	while(1)
	{
		bzero(msg, SIZE);
		time(&t);
		snprintf(msg, SIZE, "[%d] %s", getpid(), ctime(&t));

		write(fifofd, msg, strlen(msg));

		sleep(1);	
	}

	return 0;
}
