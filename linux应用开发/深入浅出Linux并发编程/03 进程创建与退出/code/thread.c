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

#include <pthread.h>

//gcc -o thread thread.c -pthread

int a = 100; //全局变量

void *callback2(void *arg)
{
    sleep(1);
    int * c = (int *)arg;
    
    printf("[%d]\n", __LINE__);
    printf("[callback2]c:  %03d, callback2_c_addr = %p\n", *c, c); //99
}

void *callback1(void *arg)
{
    int * b = (int *)arg;
    //int c = 99;
    static int c = 99;

    printf("[%d]\n", __LINE__);
    printf("[callback1]b:  %03d, callback1_b_addr = %p\n", *b, b); //200

    printf("[callback1]c:  %03d, callback1_c_addr = %p\n", c, &c);

    pthread_t  tid;
    pthread_create(&tid ,  NULL , callback2 , &c);    //传递线程1的局部变量c(栈)给线程2

    //sleep(1);

}

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

		pthread_t  tid;
	    pthread_create(&tid ,  NULL , callback1 , &b);    //传递main的局部变量b(栈)给线程1

		printf("[parent]a:  %d, parent_addr a = %p\n", a, &a); //100
		printf("[parent]b:  %d, parent_addr b = %p\n", b, &b); //200
		printf("[parent]*p: %d, parent_addr p = %p\n", *p, p); //300
		while(1)
		{
			pause(); //主程序不能退出，不然后面的线程都会退出；
		}
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


root@NanoPC-T4:/home/work/linux_应用开发/进程线程/03_fork_exit# ./thread2
[47]
[child]a:  1000, child_addr a = 0x556e13a010
[child]b:  2000, child_addr b = 0x7fe1bbed20
[child]*p: 3000, child_addr p = 0x55abe50670
[81]
[parent]a:  100, parent_addr a = 0x556e13a010
[parent]b:  200, parent_addr b = 0x7fe1bbed20
[parent]*p: 300, parent_addr p = 0x55abe50670
[32]
[callback1]b:  200, callback1_b_addr = 0x7fe1bbed20
[callback1]c:  099, callback1_c_addr = 0x7fb5f5b9d4
[23]
[callback2]c:  099, callback2_c_addr = 0x7fb5f5b9d4

从父子进程结果可以看出来：子进程修改的值对父进程没有影响。但是变量的地址都是一样的，数据却是不一样的。怎么理解？
答：这里打印出来的是逻辑地址，也就是父子进程的逻辑地址是一样的，但是物理地址肯定是不一样的。

根据《unix 高级环境编程》中的一句话：子进程和父进程继续执行fork调用之后的指令，子进程是父进程的副本。
例如：子进程获取父进程数据空间，堆和栈的副本。注意，这是子进程所拥有的副本。父子进程并不共享这些存储空间部分。父子进程共享正文段（就是代码段.text）。

如果在文件a.txt中存放了字符串hello world，然后父子进程分别去读文件，会发现文件描述符偏移了2次。

父子进程之间数据共享结果如下：
全局变量           栈区(局部变量)           堆区(动态开辟)            文件

不共享             不共享                   不共享           		   共享文件偏移量 


从线程结果可以看出来：线程之间的局部变量也是可以互相访问的，但是不能直接访问，不然会报错没定义，
应该在创建线程的时候通过传参进去，并且某线程在使用其他线程的局部变量的时候，要保证那个局部变量所在的线程没有结束，
因为局部变量是保存在栈中的，如果局部变量所在的线程结束了，局部变量会被回收，这时候其他线程再去使用该局部变量的话，是一个不确定的值，
所以可以看到，我在callback1最后加了sleep(1);目的是为了让callback2在使用callback1的局部变量c时候，callback1还没有结束，
也就是保证callback2在使用callback1的局部变量c时候，保存在callback1栈中的局部变量c还没有被回收。

静态局部变量不存在以上情况，因为局部静态变量不是保存在栈中，而是存放在内存的全局数据区，函数(线程)结束时，静态局部变量不会消失，
所以就算局部静态变量所在的线程结束了，这时候其他线程再去使用该局部静态变量也是正确的。
注意：静态局部变量也不能直接访问，不然会报错没定义，也应该在创建线程的时候通过传参进去。

能够直接使用的是全局变量；

#endif
