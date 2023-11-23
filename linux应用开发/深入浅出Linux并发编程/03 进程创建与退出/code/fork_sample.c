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

int a = 100; //全局变量

int main(int argc, char **argv)
{
	int b = 200; //栈区(局部变量)
	printf("[%d]\n", __LINE__);

	int *p = malloc(sizeof(int)); //堆区(动态开辟)
	*p = 300;

	pid_t pid = fork();

	if(pid > 0) // parent
	{
		sleep(1); //睡眠一秒，让子进程先执行
		printf("[parent]a:  %d, parent_addr a = %p\n", a, &a); //100
		printf("[parent]b:  %d, parent_addr b = %p\n", b, &b); //200
		printf("[parent]*p: %d, parent_addr p = %p\n", *p, p); //300
	}

	if(pid == 0) // child
	{
		a  = 1000;
		b  = 2000;
		*p = 3000;
		printf("[child]a:  %d, child_addr a = %p\n", a, &a); //1000
		printf("[child]b:  %d, child_addr b = %p\n", b, &b); //2000
		printf("[child]*p: %d, child_addr p = %p\n", *p, p); //3000
	}

	printf("[%d]\n", __LINE__);

	return 0;
}

#if 0

root@NanoPC-T4:/home/work/linux_应用开发/03_fork_exit# ./fork_sample
[19]
[child]a:  1000, child_addr a = 0x556cc53010
[child]b:  2000, child_addr b = 0x7fc5e16338
[child]*p: 3000, child_addr p = 0x556e59b670
[44]
[parent]a:  100, parent_addr a = 0x556cc53010
[parent]b:  200, parent_addr b = 0x7fc5e16338
[parent]*p: 300, parent_addr p = 0x556e59b670
[44]
root@NanoPC-T4:/home/work/linux_应用开发/03_fork_exit#

从结果可以看出来：子进程修改的值对父进程没有影响。但是变量的地址都是一样的，数据却是不一样的。怎么理解？
答：这里打印出来的是逻辑地址，也就是父子进程的逻辑地址是一样的，但是物理地址肯定是不一样的。

根据《unix 高级环境编程》中的一句话：子进程和父进程继续执行fork调用之后的指令，子进程是父进程的副本。
例如：子进程获取父进程数据空间，堆和栈的副本。注意，这是子进程所拥有的副本。父子进程并不共享这些存储空间部分。父子进程共享正文段（就是代码段.text）。

如果在文件a.txt中存放了字符串hello world，然后父子进程分别去读文件，会发现文件描述符偏移了2次。

父子进程之间数据共享结果如下：
全局变量           栈区(局部变量)           堆区(动态开辟)            文件

不共享             不共享                   不共享           		   共享文件偏移量 

#endif
