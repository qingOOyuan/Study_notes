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

void f(int sig)
{
	printf("catch sig: %d\n", sig);
}

int main(int argc, char **argv)
{
	printf("my PID: %d\n", getpid());

	signal(SIGINT, f);

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGHUP);
	sigprocmask(SIG_BLOCK, &set, NULL);

	int count = 10;
	while(count > 0)
	{
		printf("count: %d\n", count);
		count--;
		sleep(1);
	}

	sigprocmask(SIG_UNBLOCK, &set, NULL);

	return 0;
}
