#include "head.h"

void shutdown_sem(int sig)
{
	sem_close(data);
	sem_close(space);

	sem_unlink(DATA);
	sem_unlink(SPACE);

	exit(0);
}

int main(void)
{
	int shmid = shmget(ftok(".", 1), SHMSIZE, IPC_CREAT|0666);
	char *addr = shmat(shmid, NULL, 0);

	data = sem_open(DATA,  O_CREAT, 0666, 0);
	space= sem_open(SPACE, O_CREAT, 0666, 1);


	while(1)
	{
		// ask for data
		sem_wait(data);

		fprintf(stderr, "%c", *addr);

		// release space
		sem_post(space);
	}

	return 0;
}
