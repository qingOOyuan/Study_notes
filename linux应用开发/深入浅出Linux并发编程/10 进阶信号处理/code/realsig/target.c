#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int sig)
{
	fprintf(stderr, "catch %d.\n", sig);
}

int main(int argc, char **argv)
{
	sigset_t sigs;
	sigemptyset(&sigs);

	int i;
	for(i=SIGHUP; i<=SIGRTMAX; i++)
	{
		if(i == SIGKILL || i == SIGSTOP)
			continue;

		signal(i, sighandler);
		sigaddset(&sigs, i);
	}

	printf("[%d]: blocked signals for a while...\n", getpid());
	sigprocmask(SIG_BLOCK, &sigs, NULL);
	sleep(10);

	printf("[%d]: unblocked signals.\n", getpid());
	sigprocmask(SIG_UNBLOCK, &sigs, NULL);
	
	return 0;
}
