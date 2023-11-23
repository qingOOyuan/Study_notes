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

void f1(void)
{
	printf("[%s] is calling...\n", __FUNCTION__);
}

void f2(void)
{
	printf("[%s] is calling...\n", __FUNCTION__);
}

int main(int argc, char **argv)
{
	atexit(f1);
	atexit(f2);

	printf("abcd"); //这里没有加\n，用_exit(0)是不会冲刷到屏幕显示的

#ifdef _EXIT  //gcc -o exit_sample exit_sample.c -D_EXIT
	_exit(0);
#else
	exit(0);
#endif

}

#if 0

原型：

void exit(int status);
void _exit(int status);
如果进程正常退出，status一般为0，如果是非正常退出，一般非0
这个值会放在该进程的“尸体”(PCB)里面，等待父进程回收

exit()退出时，会自动冲刷(flush)标准I/O残留到内核的数据，
如果进程注册了“退出处理函数”，还会自动执行这些函数，而_exit()会直接退出

#endif

