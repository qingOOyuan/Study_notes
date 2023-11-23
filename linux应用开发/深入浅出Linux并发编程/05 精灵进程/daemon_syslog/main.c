#include <unistd.h>
#include "daemon.h"

int main(void)
{
	daemon_init();	

	while(1)
	{
		syslog(LOG_DAEMON, "I am a daemonAAA!");
		sleep(2);
	}

	return 0;
}

#if 0
守护进程已经与所属的控制终端失去了联系。因此从终端输入的字符不可能达到守护进程
守护进程中用常规方法（如printf）输出的字符也不可能在终端上显示出来。
所以，文件描述符为0、1和2 的3个文件（常说的输入、输出和报错）已经失去了存在的价值，也应被关闭。
#endif
