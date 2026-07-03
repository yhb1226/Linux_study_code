#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    struct mq_attr arry;
	arry.mq_curmsgs = 0;
	arry.mq_flags = 0;
	arry.mq_maxmsg = 10;//最大消息队列个数
	arry.mq_msgsize = 100;//队列的每个消息最大的字节数

	char *mq_name = "/copy_mq";
	//创建消息队列
	mqd_t mqfd = mq_open(mq_name,O_RDWR|O_CREAT,0664,&arry);
	if(mqfd == (mqd_t)-1)
	{
		perror("mq_open");
		exit(EXIT_FAILURE);
	}

    while (1)
	{

		char buf[100] = {0};
        memset(buf,0,100);
		struct timespec time_info;
		// 设置接收超时时间,这要设置成0,如果使用宏定义会报错
        clock_gettime(0, &time_info);
        time_info.tv_sec += 15;
		//消息队列是不能用read来读取的
		ssize_t receive_num = mq_timedreceive(mqfd,buf,100,0,&time_info);
		//判断读取到的数据是否出错
		if(receive_num == -1)
		{ 
			//等待超时也会返回-1,并且进行双重判断，看是超时报错还是本身报错
			if(errno == ETIMEDOUT)
			{
				printf("等待超时....\n");
				continue;
			}else{
				perror("mq_timedreceive");
				exit(EXIT_FAILURE);
			}

		}else if(receive_num == 1 && buf[0] == (char)EOF){//当对方发送一长条长度为0的消息可能也会返回0,因此作双重判断

			printf("接收结束准备退出\n");
			break;
		}
		//mq_timedreceive不会在末尾加上\0所以可能是一个非法字符，还是用实际字符receive_num接收好一些
        write(STDOUT_FILENO,buf,receive_num);

	} 
	
	// 关闭消息队列描述符
    close(mqfd);
    // 清除消息队列
	mq_unlink(mq_name);









    return 0;
}
