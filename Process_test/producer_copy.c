#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

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
		//阻塞读取端口输入数据
		ssize_t read_num = read(STDIN_FILENO,buf,100);
		//判断读取到的数据是否出错
		if(read_num < 0)
		{
		perror("read");
		exit(EXIT_FAILURE);
		}else if(read_num == 0){
		//当按下Ctrl+D退出时候把退出的标识符EOF发送出去，并且在按下时候返回给read_num的值是0
		char eof = EOF;
		printf("生产者即将结束退出输入\n");
		if(mq_timedsend(mqfd,&eof,1,0,&time_info) == -1)
		{
		perror("mq_timedsend");
		exit(EXIT_FAILURE);
		}
		break;

		}
		//正常情况下发送的数据
		if(mq_timedsend(mqfd,buf,strlen(buf),0,&time_info) == -1)
		{
		perror("mq_timedsend");
		exit(EXIT_FAILURE);
		}


	}
	
	// 关闭消息队列描述符
    close(mqfd);
    // 清除消息队列
	//mq_unlink(mq_name);




	return 0;
}
