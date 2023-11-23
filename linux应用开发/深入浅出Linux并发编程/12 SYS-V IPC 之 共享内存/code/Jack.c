#include "head.h"

int main(int argc, char **argv)
{
	key_t key = ftok(".", 1);
	int shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);

	char *addr1 = shmat(shmid, NULL, 0);

	bzero(addr1, SHMSIZE);
	fgets(addr1, SHMSIZE, stdin);

	shmdt(addr1);
	return 0;
}
