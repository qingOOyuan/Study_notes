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
	signal(SIGINT, shutdown_sem);

	int shmid = shmget(ftok(".", 1), SHMSIZE, IPC_CREAT|0666);
	char *addr = shmat(shmid, NULL, 0);

	data = sem_open(DATA,  O_CREAT, 0666, 0);
	space= sem_open(SPACE, O_CREAT, 0666, 1);

	char *msg = "0123456789";

	int i = 0;
	while(1)
	{
		// ask for space
		sem_wait(space);

		memcpy(addr, msg+i, 1);
		i = (i+1) % 10;

		// release data
		sem_post(data);
	}

	return 0;
}
