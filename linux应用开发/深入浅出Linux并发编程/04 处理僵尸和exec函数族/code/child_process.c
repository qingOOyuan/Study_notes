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

int main(int argc, char **argv)
{
	printf("(child) PID: %d, PPID: %d\n", getpid(), getppid());

	int i;
	for(i=0; i<argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	sleep(3);

	exit(88);
}
