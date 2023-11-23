#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//read、write使用无缓冲技术
int main(int argc, char const *argv[])
{
	int src_fd, des_fd;
	int read_ret;
	char read_buf[128] = {0};

	if(argc < 3)
	{
		printf("please input src and des file\n");
		return -1;
	}	

	src_fd = open(argv[1], O_RDONLY);
	if (src_fd < 0)
	{
		printf("open src file %s failure\n", argv[1]);
		return -2;
	}
	printf("open src file %s success\n", argv[1]);

	des_fd = open(argv[2], O_CREAT | O_WRONLY, 0777);
	if (des_fd < 0)
	{
		printf("open des file %s failure\n", argv[2]);
	}
	printf("open des file %s success\n", argv[2]);

	//start read write
	while(1)
	{
		read_ret = read(src_fd, read_buf, 128);
		write(des_fd, read_buf, read_ret);
		if (read_ret < 128)
		{
			printf("read file %s end\n", argv[1]);
			break;
		}
	}

	close(src_fd);
	close(des_fd);
	
	return 0;
}
