#include "head.h"

int main(int argc, char **argv)
{
	key_t key = ftok(".", 1);
	int shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);

	char *addr2 = shmat(shmid, NULL, 0);

	printf("from Jack: %s", addr2);

	shmdt(addr2);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
