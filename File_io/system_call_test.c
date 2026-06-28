#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    // 打开文件
    int fd = open("io.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("打开文件失败\n");//perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024]; //用于存放读取的数据
    ssize_t bytes_read;

        /*
        * int _fd: 文件描述符
        * void *_buf: 存放数据
        * size_t _nbytes: 读取数据的长度
        * return: ssize_t -> long int : 读取到数据的字节长度 成功大于0 失败-1
        * ssize_t read (int _fd, void *_buf, size_t _nbytes)
        */
    while ((bytes_read = read(fd, &buffer, sizeof(buffer))) > 0)
    {
        // 文件描述符类型的 stdin -> 0
        // stdout -> 1  stderr -> 2
        /*
         * int _fd: 文件描述符
         * const void *_buf: 要写出的数据
         * size_t _n: 写出的长度
         * return: 成功返回写出数据的长度 失败返回-1
         * ssize_t write (int _fd, const void *_buf, size_t _n)
         */
        write(STDOUT_FILENO, &buffer, bytes_read);//写到控制台上去STDOUT_FILENO
    }

    if (bytes_read == -1)
    {
        printf("读取文件出错\n");//perror("read");
    }
    /*
     * 关闭打开的文件描述符
     * return: 成功返回0 失败返回-1
     */
    printf("\n");
    close(fd);
    return 0;
}