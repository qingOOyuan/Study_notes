#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

#define JACK2ROSE 1
#define SIZE 100

struct msgbuf
{
	long msgtype;
	char msgtext[SIZE];
};

int main(int argc, char **argv)
{
	int msgid = msgget(ftok(".", 1), IPC_CREAT|0666);

	struct msgbuf msg;
	while(1)
	{
		bzero(&msg, sizeof(msg));
		msgrcv(msgid, &msg, SIZE, JACK2ROSE, 0);

		printf("from Jack: %s", msg.msgtext);
	}

	return 0;
}
