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
    //1.首先创建消息队列的基本参数
    struct mq_attr arry;
    arry.mq_maxmsg = 10;    // 消息队列最大消息数
    arry.mq_msgsize = 100;  // 单条消息最大字节数
    arry.mq_flags = 0;
    arry.mq_curmsgs = 0;

    //和前面的共享内存定义的方式类似，只允许月个以/开头且只能有一个
    char *mq_name = "/copy_mq";
    //类似fd标志符
    mq_unlink("/copy_mq");   // 删除可能残留的旧队列
    mqd_t mqfd = mq_open(mq_name,O_RDWR|O_CREAT,0664,&arry);
    if(mqfd == (mqd_t)-1)
    {
        perror("mq_open"); 
        exit(EXIT_FAILURE);
    }

    pid_t cpid = fork();
    if(cpid == (pid_t)-1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(cpid == 0){
        int i = 0;
        char send_buf[100] = {0};
        //设置一下响应超时的时间
        struct timespec time_info;
        for(i;i < 10;i++)
        {
            //只是为了清空残余的数值，并不是为了防止循环溢出
            memset(send_buf, 0, 100);
            // 设置接收超时时间,这要设置成0,如果使用宏定义会报错
            clock_gettime(0, &time_info);
            time_info.tv_sec += 15;

            sprintf(send_buf,"子给父第%d次发消息\n",(int)(i+1));
            // 1.用 mq_open 打开的消息队列描述符;2.字符数组的地址，3.例如 read_buf;4.大小;5.优先级;6.填写NULL是其期无限期阻塞，此处设置了阻塞时间
            if(mq_timedsend(mqfd,send_buf,strlen(send_buf),0,&time_info) == -1)
            {
                perror("mq_timedsend");
                exit(EXIT_FAILURE);
            }

            printf("子第%d次的消息发送完成\n",(int)(i+1));
            //发送端加入睡眠为了接收方有节奏进行
            sleep(1);
        }
    }else{
        int i = 0;
        char receive_buf[100] = {0};
        //设置一下响应超时的时间
        struct timespec time_info;
        for(i;i < 10;i++)
        {
            memset(receive_buf, 0, 100);
            // 设置接收超时时间,这要设置成0,如果使用宏定义会报错
            clock_gettime(0, &time_info);
            time_info.tv_sec += 15;
            if(mq_timedreceive(mqfd,receive_buf,100,0,&time_info) == -1)
            {
                perror("mq_timedreceive");
                exit(EXIT_FAILURE);
            }
            printf("父第%d次的消息接收完成:%s",(int)(i+1),receive_buf);
        }

        waitpid(cpid, NULL, 0); // 等待子进程接收完成

    }

    // 关闭消息队列描述符
    close(mqfd);
    // 父进程负责删除消息队列对象
    if (cpid > 0)
    {
        mq_unlink(mq_name);
    }

    return 0;
}
