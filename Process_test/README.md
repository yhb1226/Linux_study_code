# 本节主要学习进程之间的应用
    主要包括fork复制出父进程和子进程、execve+fork在进程中进行跳转、匿名管道、有名管道（管道的意义在与进程之间不能进行通信）

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

### 消息队列








注：

    a.局部变量的定义

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

    用消息队列通信时候为什么后面的要去掉
```makefile
    producer:producer.c
        $(CC) -o $@ $^

    consumer:consumer.c
        $(CC) -o $@ $^
```



