#include "head.h"

void seminit(int semid, int semnum, int val)
{
	union semun a;

	a.val = val;
	semctl(semid, semnum, SETVAL, a);
}

// P operation
void sem_p(int semid, int semnum)
{
	struct sembuf a[1];
	a[0].sem_num = semnum;
	a[0].sem_op = -1;
	a[0].sem_flg = 0;

	semop(semid, a, 1);
}

// V operation
void sem_v(int semid, int semnum)
{
	struct sembuf a[1];
	a[0].sem_num = semnum;
	a[0].sem_op = 1;
	a[0].sem_flg = 0;

	semop(semid, a, 1);
}
