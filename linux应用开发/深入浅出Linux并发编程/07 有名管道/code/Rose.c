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

#define FIFONAME "myfifo"
#define SIZE 100

int main(int argc, char **argv)
{
	// NOT exist
	if(access(FIFONAME, F_OK))
	{
		mkfifo(FIFONAME, 0777);
	}

	int fd = open(FIFONAME, O_RDONLY);

	char buf[SIZE];
	while(1)
	{
		bzero(buf, SIZE);
		read(fd, buf, SIZE);

		printf("from Jack: %s", buf);
	}

	close(fd);

	return 0;
}
