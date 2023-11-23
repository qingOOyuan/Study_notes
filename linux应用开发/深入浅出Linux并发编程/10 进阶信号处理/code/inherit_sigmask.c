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

	/*
	** sigmask WILL be inherit to child process
	** therefore, child process will block SIGQUIT
	** until proceeding unblock action.
	*/
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGQUIT);
	sigprocmask(SIG_BLOCK, &sig, NULL);

	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		fprintf(stderr, "child: %d\n", getpid());

		/*
		** during this period of 20s, if this process
		** receive signal SIGQUIT, it will be blocked.
		** until child process call sigprocmask() to
		** unblock it.
		**
		** NOTE: child process WILL inherit sigmask from
		** their parent, and then won't associate with
		** each other.
		*/
		int count = 10;
		while(count > 0)
		{
			printf("%d\n", count--);
			sleep(1);
		}

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
