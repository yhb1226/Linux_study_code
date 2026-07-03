# 本节主要学习进程之间的应用
    主要包括fork复制出父进程和子进程、execve+fork在进程中进行跳转、匿名管道、有名管道（管道的意义在与进程之间不能进行通信）、共享内存、消息队列

## 进程间的通信

### 匿名管道(内核)

过程分为：

    1.首先创建管道，再fork两个进程；

    2.再进行两个进程的读写操作，父进程写则关闭读的功能，读写分别对应的是0和1；

    3.在读的过程可中可以使用while进行循环读取；
```c
    char str;
    while(read(pipefd[0],&str,1)>0)

        {
            write(STDOUT_FILENO,&str,1);//读取完成打印端口
        }
```

    4.最后为了防止重叠可以再打印换行后直接exit(EXIT_SUCCESS)

注： 

    a.操作整个内存块用sizeof,想要传递的是字符串内容用strlen

    b.waitpid(cpid,NULL,0);//一直等待子进程结束

### 有名管道(内核)

    1.在有名管道定义的标识符和无名中定义的都是为了后面的write()和read(),这两个的第一个变量都是传的是标识符，即需要进行读写的目标

```c
fd = open(pipe_path,O_WRONLY);//有名管道定义的标识符
int pipefd[];//无名管道定义的标识符
```
    2.运行完成后需要主动清理
```c
//首先创建一个路径，一般取在/tmp下面
    char *pipe_path = "/tmp/my_new_fifo";   // 换一个全新的名字
    //接着创建有名管道
    //只要运行到了这一部卡住了，此时需要手动清理rm /tmp/my_new_fifo,因为没有运行到后面是无法正常回收的
    if(mkfifo(pipe_path,0664) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
```
    3.exit() = 先收拾房间再离开；_exit() = 立刻消失，不管房间有多乱。

### 共享内存(share_memory)






### 消息队列(mq_test)

    1.发送和接收数组长度问题
```c
        //发送-->strlen(send_buf)实际长度
        if(mq_timedsend(mqfd,send_buf,strlen(send_buf),0,&time_info) == -1)
            {
                perror("mq_timedsend");
                exit(EXIT_FAILURE);
            }
        //接收-->100选数组最大长度，不够的会自动补0   
        if(mq_timedreceive(mqfd,receive_buf,100,0,&time_info) == -1)
            {
                perror("mq_timedreceive");
                exit(EXIT_FAILURE);
            }
```
    2.sprintf写入问题
```c
    //只是为了清空定义时候残余的数值，并不是为了防止循环溢出
        memset(send_buf, 0, 100);
    //sprintf每次都是从数组首地址开始写，无需手动清除
    sprintf(send_buf,"子给父第%d次发消息\n",(int)(i+1));
```
    3.发送过程中换行问题
```c
    //正常情况下发送的数据,在发送数据时候回车时会自动换行，不用在接收时候额外加上换行符
		if(mq_timedsend(mqfd,buf,strlen(buf),0,&time_info) == -1)
		{
		perror("mq_timedsend");
		exit(EXIT_FAILURE);
		}
```




C补充：

    1.局部变量的定义

```c
    \\以下定义的都是局部变量

    if(i == 1 ){

    }
//************************************************
    for (int i = 0; i < 10; i++) {
    int y = i * 2;   
}
//************************************************
    switch (val) {
    case 1: {
        int tmp = 5;   // 仅在这个 case 块内有效
        break;
    }
    case 2:
        // 不能直接 int tmp = 10;（除非加大括号）
        break;
//*************************************************
void func(int a, char *b) {
    // a 和 b 在 func 内部有效，属于该函数的局部变量
}
}
```
    2.结构体
```c
    //stm32中类似结构体定义
    typedef struct {
    long mq_maxmsg;
    long mq_msgsize;
    long mq_flags;
    long mq_curmsgs;
} mq_attr_t;//mq_attr_t指的是类型名，类似于int a中的int

mq_attr_t attr;//attr指的是实际名字，类似于int a中的a

    //在消息队列中使用的结构体，因为已经在引入的头文件中定义好了，所以只需要声明即可
    struct mq_attr attr;
    attr.mq_maxmsg = 10;    // 消息队列最大消息数
    attr.mq_msgsize = 100;  // 单条消息最大字节数
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    3.函数中要填入char*类型的指针时候，也可以用char buf[]一个对应的数组来代替


```

    用消息队列通信时候为什么后面的要去掉
```makefile
    producer:producer.c
        $(CC) -o $@ $^

    consumer:consumer.c
        $(CC) -o $@ $^
```



