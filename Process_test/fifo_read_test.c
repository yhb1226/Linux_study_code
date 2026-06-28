#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/myfifo";
    // 创建有名管道文件，权限0664

    // if (mkfifo(pipe_path, 0664) != 0)
    // {
    //     perror("mkfifo");
    //     exit(EXIT_FAILURE);
    // }

    // 以只写模式打开管道
    fd = open(pipe_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    // 读取管道信息写入到控制台
    while ((read_num = read(fd, buf, 100)) > 0)
    {
        write(STDOUT_FILENO, buf, read_num);
    }


    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("接收数据到管道完成 进程终止\n");
    close(fd);
    return 0;
}