#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    // 创建消息队列
    struct mq_attr attr;
    attr.mq_maxmsg = 10;    // 消息队列最大消息数
    attr.mq_msgsize = 100;  // 单条消息最大字节数
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name = "/father_son_mq";
    mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0664, &attr);
    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // 创建父子进程
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // 子进程：循环接收消息
        char read_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            memset(read_buf, 0, 100);

            // 设置接收超时时间
            clock_gettime(0, &time_info);
            time_info.tv_sec += 15;
            if (mq_timedreceive(mqdes, read_buf, 100, NULL, &time_info) == -1)
            {
                perror("mq_timedreceive");
            }
            printf("子进程接收到数据:%s", read_buf);
        }
    }
    else
    {
        // 父进程：循环发送消息
        char send_buf[100];
        struct timespec time_info;
        for (size_t i = 0; i < 10; i++)
        {
            memset(send_buf, 0, 100);
            sprintf(send_buf, "父进程的第%d次发送消息\n", (int)(i + 1));

            // 设置发送超时时间
            clock_gettime(0, &time_info);
            time_info.tv_sec += 5;
            if (mq_timedsend(mqdes, send_buf, strlen(send_buf), 0, &time_info) == -1)
            {
                perror("mq_timedsend");
            }
            printf("父进程发送一条消息,休眠1s\n");
            sleep(1);
        }
        waitpid(pid, NULL, 0); // 等待子进程接收完成
    }

    // 关闭消息队列描述符
    close(mqdes);
    // 父进程负责删除消息队列对象
    if (pid > 0)
    {
        mq_unlink(mq_name);
    }

    return 0;
}