#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *routine(void *arg)
{
	struct
	{
		char *buf;
		int *pdata;
		int *pspace;
	}*args;

	args = arg;

	while(1)
	{
		while(*(args->pdata) == 0);

		(*(args->pdata))--;
		printf("bytes: %d\n", strlen(args->buf));
		(*(args->pspace))++;
	}
}

int main(void)
{
	char buf[32];
	int data  = 0;
	int space = 1;

	struct
	{
		char *buf;	
		int *pdata;
		int *pspace;
	}arg={buf, &data, &space};

	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)&arg);

	while(1)
	{
		while(space == 0);

		space--;
		bzero(buf, 32);
		fgets(buf, 32, stdin);
		data++;
	}
}
