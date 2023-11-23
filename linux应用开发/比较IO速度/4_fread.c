#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//fread、fwrite使用全缓存技术
int main(int argc, char const *argv[]) 
{
	FILE *src_fp, *des_fp;
	int read_ret;
	char read_buf[128] = {0};

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
		read_ret = fread(read_buf, 1, 128, src_fp);
		if (read_ret < 128)
		{
			printf("read file %s end\n", argv[1]);
			break;
		}
		fwrite(read_buf, 1, read_ret, des_fp);
	}
	fwrite(read_buf, 1, read_ret, des_fp);

	fclose(src_fp);
	fclose(des_fp);

	return 0;
}
