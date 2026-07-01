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
    char *pipe_path = "/tmp/my_new_fifo";
    // 创建有名管道文件，权限0664
    if (mkfifo(pipe_path, 0664) != 0)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 以只写模式打开管道
    fd = open(pipe_path, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    // 循环读取终端输入，写入管道
    while ((read_num = read(STDIN_FILENO, buf, 100)) > 0)
    {
        write(fd, buf, read_num);
    }

    
    if (read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("发送数据到管道完成 进程终止\n");
    close(fd);

    if(unlink(pipe_path) == -1)//释放管道，清除对应的特殊文件，匿名管道直接关掉即可
    {
         perror("unlink");//ctrl+d终止
    }

    return 0;
}
