#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void catch_sig(int sig)
{
	fprintf(stderr, "%d catch SIGQUIT.\n", getpid());
}

int main(int argc, char **argv)
{
	signal(SIGQUIT, catch_sig);

	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGQUIT);
	sigprocmask(SIG_BLOCK, &sig, NULL);

	/*
	** during this period, we will send SIGQUIT to the
	** parent process, and SIGQUIT will pending on the
	** sharing sig-queue, and this pending signal will
	** NOT inherit to its child process.
	*/
	int count = 5;
	while(count > 0)
	{
		printf("count: %d\n", count--);
		sleep(1);
	}

	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		fprintf(stderr, "child: %d\n", getpid());

		/*
		** unblock the signal SIGQUIT, child process
		** will NOT call the function catch_sig, this
		** is because the pending signals will be
		** cleared when process fork() a new process.
		**
		** NOTE: pending signals will NOT be inherit
		*/
		sigprocmask(SIG_UNBLOCK, &sig, NULL);

		pause();
	}
	
	else if(pid > 0)
	{
		fprintf(stderr, "parent: %d\n", getpid());
		sigprocmask(SIG_UNBLOCK, &sig, NULL);

		pause();
	}

	return 0;
}
