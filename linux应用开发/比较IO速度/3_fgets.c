#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//fgets、fputs使用行缓冲技术
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
		//在读字符时遇到end-of-file，则eof指示器被设置，如果还没读入任何字符就遇到这种情况，则stream保持原来的内容，返回NULL；
		//也即返回eof NULL只会发生在没有读取任何字符时发生，如果我当前读了一些数据到read_buf，然后文件结束遇到eof，他不会返回NULL
		//读取错误也会返回NULL，所以我们不能根据NULL来判断是否到了文件结尾，应该用feof
		fgets(read_buf, 128, src_fp);
		if (feof(src_fp)) //对于feof而言，他的工作原理是，站在光标所在位置，向后看看还有没有字符，如果有返回0，如果没有返回非0
		{
			printf("read file %s end\n", argv[1]);
			break;
		}
		fputs(read_buf, des_fp);
	}

	fclose(src_fp);
	fclose(des_fp);

	return 0;
}
