#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t m;

void *routine(void *arg)
{
	char *msg = (char *)arg;

	#ifdef MUTEX
	pthread_mutex_lock(&m);
	#endif
	while(*msg != '\0')
	{
		fprintf(stderr, "%c", *msg);
		usleep(100);
		msg++;
	}
	#ifdef MUTEX
	pthread_mutex_unlock(&m);
	#endif

	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_mutex_init(&m, NULL);

	pthread_t t1, t2;
	pthread_create(&t1, NULL, routine, "AAAAAAAAAAAAAAAA");
	pthread_create(&t2, NULL, routine, "BBBBBBBBBBBBBBBB");

	pthread_exit(NULL);
}