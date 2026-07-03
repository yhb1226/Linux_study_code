#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    // 打开消息队列（和生产者同名）
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name = "/p_c_mq";
    mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0664, &attr);

    if (mqdes == (mqd_t)-1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char read_buf[100];
    struct timespec time_info;
    while (1)
    {
        memset(read_buf, 0, 100);
        
        clock_gettime(0, &time_info);
        time_info.tv_sec += 15;

        // 读取消息队列数据，失败则跳过本次
        if (mq_timedreceive(mqdes, read_buf, 100, NULL, &time_info) == -1)
        {
            perror("mq_timedreceive");
            continue;
        }

        // 判断结束信号：强制转有符号char比较，避免无符号溢出
        if (read_buf[0] == EOF)
        {
            printf("接收到生产者发送的结束信息 准备退出...\n");
            break;
        }

        printf("接收到来自生产者发送的信息%s", read_buf);
    }

    close(mqdes);
    mq_unlink(mq_name);

    return 0;
}