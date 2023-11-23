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
#include <signal.h>

int main(int argc, char **argv)
{
	pid_t p1;
	scanf("%d", &p1);

	union sigval a;
	bzero(&a, sizeof(a));
	a.sival_int = 100;

	sigqueue(p1, SIGINT, a); // --> kill()

	return 0;
}
