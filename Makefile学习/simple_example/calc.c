#include "function.h"

int calc(int n)
{
	if (n == 1)
		return 1;
	else
		return n * calc(n - 1);
}