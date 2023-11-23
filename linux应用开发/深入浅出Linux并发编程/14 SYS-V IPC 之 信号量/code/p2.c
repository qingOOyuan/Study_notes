#include "head.h"

int main(void)
{
	int shmid = shmget(ftok(".", 1), SHMSIZE, IPC_CREAT|0666);
	char *addr = shmat(shmid, NULL, 0);

	int semid = semget(ftok(".", 2), 2,
			IPC_CREAT|IPC_EXCL|0666);
	if(semid > 0)
	{
		seminit(semid, DATA, 0);
		seminit(semid, SPACE, 1);
	}
	else
	{
		semid = semget(ftok(".", 2), 2, 0666);
	}

	while(1)
	{
		// ask for data
		sem_p(semid, DATA);

		fprintf(stderr, "%c", *addr);

		// release space
		sem_v(semid, SPACE);
	}

	return 0;
}
