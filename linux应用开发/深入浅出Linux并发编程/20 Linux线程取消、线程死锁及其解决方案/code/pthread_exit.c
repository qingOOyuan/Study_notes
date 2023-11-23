#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <pthread.h>

void *routine(void *arg)
{
	int i = 10000;
	while(i > 0)
	{
		fprintf(stderr, "%c", 'X');
		i--;
	}
	char *msg = "hello";
	pthread_exit((void *)msg);
}

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	// void *p;
	// pthread_join(tid, &p);

	// printf("%s\n", (char *)p);

	pthread_exit(NULL);
}
