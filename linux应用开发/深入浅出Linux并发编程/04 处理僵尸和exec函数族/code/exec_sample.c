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
	printf("[%d]\n", __LINE__);

	pid_t pid = fork();
	if(pid > 0)
	{
		printf("(parent) PID: %d, PPID: %d\n", getpid(), getppid());

		int status;
		wait(&status); //阻塞等待，会一直等到某个子进程结束，并且不能指定等待哪个子进程，只要等到一个子进程退出就结束等待，并得到该子进程的退出码。
		//waitpid(pid, &status, WNOHANG); //非阻塞等待，可以指定等待哪个子进程，如果子进程还没有退出，不等待，status得到一个没有意义的值。

		printf("child exit code: %d\n", WEXITSTATUS(status));
	}

	if(pid == 0)
	{
		//execl("./child_process", "./child_process", "abcd", NULL);

		char *arg[] = {"./child_process", "abcd", NULL};
		execv("./child_process", arg);

		//execl("/bin/ls", "ls", "-l", NULL); //不加p则要指定程序的绝对路径
		//execlp("ls", "ls", "-l", NULL);     //p意味着从环境变量里找到程序的路径

		printf("xxxx\n"); //除非上面你的execv执行不成功，才会到这里，不然在execv里面就已经退出此进程了。
	}

	return 0;
}
