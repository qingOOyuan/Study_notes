#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
char global = 'X';

void *routine(void *arg)
{
	#ifdef RDLOCK
	pthread_rwlock_rdlock(&rwlock);
	#elif WRLOCK
	pthread_rwlock_wrlock(&rwlock);
	#endif
	
	int i = 100000;
	while(i > 0)
	{
		fprintf(stderr, "[%c:%c]", *(char *)arg, global);
		i--;
	}
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_rwlock_init(&rwlock, NULL);

	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, routine, "1");
	pthread_create(&t2, NULL, routine, "2");
	pthread_create(&t3, NULL, routine, "3");

	pthread_exit(NULL);
}