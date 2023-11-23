#include <stdio.h>

int main(void)
{
	int i=1;
	while(1)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}

	return 0;
}
