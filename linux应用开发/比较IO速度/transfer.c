#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	DIR *dp;
	int fd, ret;
	int src_fd, des_fd;
	struct dirent *dir;
	char server[128] = {0};
	char file[128] = {0};
	char buf[128] = {0};

start:
	//一、输入服务器的地址：路径和目录名
	printf("please input server PATH and Didrectory name\n");
	scanf("%s",server);

	//二、列出服务器中有哪些子目录和文件
	dp = opendir(server);
	if (dp == NULL)
	{
		printf("open server_dir:%s failure\n", server);
		goto start;
	}
	printf("open server_dir:%s success\n", server);

	while(1)
	{
		dir = readdir(dp);
		if (dir == NULL)
			break;
		else
		{
			printf("inode = %ld\t file_name = %s\n", dir->d_ino, dir->d_name);
		}
	}

	//三、开始下载
	//1: 输入要从服务器下载的文件名 或 上传文件到服务器的文件名,然后打开该源文件
	printf("\n Please input download file\n");
	scanf("%s",file);
	src_fd = open(strcat(strcat(server,"/"),file),O_RDONLY);
	if (src_fd < 0)
	{
		printf("open download file:%s failure\n", file);
		return -1;
	}
	printf("open download file:%s success\n", file);

	//2:在当前目录打开/新建目标文件
	des_fd = open(file, O_CREAT | O_WRONLY, 0777);
	if (des_fd < 0)
	{
		printf("creat file:%s failure\n", file);
		return -2;
	}
	printf("creat file:%s success\n", file);

	//3:开始拷贝
	while(1)
	{
		ret = read(src_fd, buf, 128);
		if (ret < 128)
			break;
		write(des_fd, buf, ret);
	}
	write(des_fd, buf, ret);

	close(src_fd);
	close(des_fd);  
	closedir(dp);

	return 0;
}