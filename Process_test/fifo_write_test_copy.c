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
    //首先创建一个路径，一般取在/tmp下面
    char *pipe_path = "/tmp/my_new_fifo";   // 换一个全新的名字
    //接着创建有名管道
    //只要运行到了这一部卡住了，此时需要手动清理rm /tmp/my_new_fifo,因为没有运行到后面是无法正常回收的
    if(mkfifo(pipe_path,0664) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    //接着再打开管道，并且再把标识符fd定义出来(README.md)
    if ((fd = open(pipe_path,O_WRONLY)) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buf[100];
    //常用ssize_t定义的来接受我们实际上读到了多少数据
    ssize_t read_num;
    //由于并不知道每次放多少，所以给一个buf缓冲区，一次性最多读取100个字节
    //read(STDIN_FILENO,buf,100);
    if((read_num = read(STDIN_FILENO,buf,100))>0)
    {
        write(fd,buf,read_num);
    }

    if(read_num < 0)
    {
        printf("出错");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("写入端完成传输\n"); 
    close(fd);

    //一般哪个调用管道，哪个就去清理相对应的路径
    if(unlink(pipe_path) == -1)
    {
        perror("unlink");
    }

    return 0;
}
