#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void *routine(void *arg)
{
	pthread_detach(pthread_self());

	sleep(1);

	char *msg = "abcd";
	pthread_exit((void *)msg);
}

int main(void)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);
	//pthread_create(&tid, &attr, routine, NULL);

	void *ret;
	if((errno=pthread_join(tid, &ret)) == 0)
	{
		printf("ret: %s\n", (char *)ret);
	}
	else
	{
		perror("pthread_join() faild");
	}

	pthread_exit(NULL);
}
