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
	int fd[2];

	pipe(fd); // fd[0] for reading, fd[1] for writting

	//如果设置管道fd[0]为非阻塞，则不等待，读不到数据直接返回
	int ret = 0;
    int flag = fcntl(fd[0], F_GETFL);
    fcntl(fd[0], F_SETFL, flag | O_NONBLOCK);

	pid_t pid = fork();

	// parent
	if(pid > 0)
	{
		char buf[100];
		bzero(buf, 100);
		//文件描述符的基础属性是阻塞属性，调用read函数读空管道时，read函数就会阻塞；
		//读取数据是直接将数据拿走，并不是拷贝，验证：再次用read函数读取，管道为空，函数会阻塞不会执行后面语句
		ret = read(fd[0], buf, 100);	
		printf("from child: %s, ret = %d\n", buf, ret);
	}

	// child
	else if(pid == 0)
	{
		sleep(2);
		char *msg = "hey! dad!";
		//文件描述符的基础属性是阻塞属性，一直调用write函数将管道写满时，write函数会阻塞，经过测试大小是65536字节
		write(fd[1], msg, strlen(msg));
	}

	return 0;
}
