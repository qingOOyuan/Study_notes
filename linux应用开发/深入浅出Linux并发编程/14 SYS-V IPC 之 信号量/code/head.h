#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#define DATA 0
#define SPACE 1

#define SHMSIZE 2

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminf *__buf;
};
