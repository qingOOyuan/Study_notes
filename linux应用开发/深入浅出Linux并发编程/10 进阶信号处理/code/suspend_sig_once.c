#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighand(int sig)
{
	if(sig == SIGRTMIN)
		printf("receive a SIGRTMIN!\n");

	return;
}

int main(void)
{
	signal(SIGRTMIN, sighand);

	// block SIGRTMIN
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &sig, NULL);

	printf("my pid: %d, send me two SIGRTMIN in 20s.\n", getpid());
	int i = 20;
	while(i--)
	{
		printf("%d\n", i);
		sleep(1);
	}

	/*
	** If there are more than one SIGRTMIN have been sent
	** to this process before it calls the following
	** function, ONE SIGRTMIN will be delivered, and the
	** other will simply be discarded.
	**
	** Therefore, the message "receive a SIGRTMIN" should
	** be printed once when the following function return.
	*/
	sigprocmask(SIG_UNBLOCK, &sig, NULL);
	

	while(1)
		pause();

	return 0;
}
