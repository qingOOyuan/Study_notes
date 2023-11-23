#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t space, data;

void *routine(void *arg)
{
	char *buf = (char *)arg;

	while(1)
	{
		sem_wait(&data);
		printf("bytes: %d\n", strlen(buf));
		sem_post(&space);
	}
}

int main(void)
{
	sem_init(&space, 0, 1);
	sem_init(&data,  0, 0);

	char buf[32];
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)buf);

	while(1)
	{
		sem_wait(&space);
		bzero(buf, 32);
		fgets(buf, 32, stdin);
		sem_post(&data);
	}
}
