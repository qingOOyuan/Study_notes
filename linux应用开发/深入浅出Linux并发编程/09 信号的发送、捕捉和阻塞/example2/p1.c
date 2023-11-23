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

void f(int sig, siginfo_t *info, void *arg)
{
	printf("catch sig: %d\n", sig);
	printf("extra info: %d\n", info->si_int);
}

int main(int argc, char **argv)
{
	printf("my PID: %d\n", getpid());

	struct sigaction act;
	bzero(&act, sizeof(act));
	act.sa_sigaction = f;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &act, NULL); // --> signal()

	pause();

	return 0;
}


#if 0

struct sigaction {
    void     (*sa_handler)(int); // 默认会用这个简单的函数
    void     (*sa_sigaction)(int, siginfo_t *, void *); // 这个是复杂的函数，如果要先用他的话，要设置sa_flags
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};

If SA_SIGINFO is specified in sa_flags, then sa_sigaction (instead of sa_handler) 

临时信号掩码sa_mask的设置使用信号集操作函数来操作，被设置在该掩码中的信号，在进程响应本信号期间被临时阻塞。

#endif