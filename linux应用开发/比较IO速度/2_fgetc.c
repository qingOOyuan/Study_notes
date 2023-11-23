#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//fgetc和fputc（单个字符的读写），这两函数有缓存，但不是行缓存，也不是全缓存
int main(int argc, char const *argv[])
{
	FILE *src_fp, *des_fp;
	int read_ret;

	if(argc < 3)
	{
		printf("please input src and des file\n");
		return -1;
	}	

	src_fp = fopen(argv[1],"r");
	if (src_fp == NULL)
	{
		printf("open src file %s failure\n", argv[1]);
		return -2;
	}
	printf("open src file %s success\n", argv[1]);

	des_fp = fopen(argv[2],"w");
	if (des_fp == NULL)
	{
		printf("open des file %s failure\n", argv[2]);
	}
	printf("open des file %s success\n", argv[2]);

	//start read write
	while(1)
	{
		read_ret = fgetc(src_fp);
		if (feof(src_fp))
		{
			printf("read file %s end\n", argv[1]);
			break;
		}
		fputc(read_ret,des_fp);
	}

	fclose(src_fp);
	fclose(des_fp);

	return 0;
}

