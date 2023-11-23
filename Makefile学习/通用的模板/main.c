#include <stdio.h>
#include <print_hello.h>
#include <calc.h>
#include <test.h>

int main(int argc, char const *argv[])
{
	print_hello();
	printf("The factorial of 5 is:%d\n",calc(5));
	test();
	return 0;
}