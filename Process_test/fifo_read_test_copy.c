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

    if((fd = open(pipe_path,O_RDONLY)) == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    //如果读取时候不足100个在字节时候也可以正常读取数据，并且由read_num获得实际读取的字节
    if((read_num = read(fd,buf,100)) > 0)
    {
        write(STDOUT_FILENO,buf,read_num);
    }

    if(read_num < 0)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

   
    printf("接受完成\n");
     close(fd);

    return 0;
}

