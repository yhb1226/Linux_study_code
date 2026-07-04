# c语言补充
    1.当函数需要返回多个变量时候，可以使用结构体一起打包带回

```c
    //打包两个参数，一个是字符串，一个是长度
    typedef struct Result{
        char *p;
        int len;
    } Result;
    //如果一个进程的多个线程同时使用到标准的输入输出  会造成冲突的问题 导致只能有一个线程使用到标准的输入输出
    // 红玫瑰执行代码的函数
    void * red_thread(void * arg)
    {
        // 初始化Result结构体
        Result *result = malloc(sizeof(Result));
    }
```
    2.定义内存以及释放问题，
```c
    //在terminate_test中使用了结构体创建的malloc
    RESULT *result = malloc(sizeof(RESULT));
    //在使用strdup时候也创建了一个malloc的内存
    char *readen = strdup("红玫瑰去了巴黎\n");//readen是一个字符指针，保存字符串的首地址，并在后面的代码当中把它复制给serial
    result->lens = strlen(readen);
    //其中真正在第二次中需要释放的内存为result->serial，而其中的readen只是一把钥匙，用将完即毁
    result->serial = readen;
    .......
    //接收返回变量的指针
    RESULT *red_result = NULL;
    RESULT *white_result = NULL;
    //其中释放内存的顺序是先释放内部年的用创建的内存，再释放外部使用的内存
    //随着线程结束时候，结构体创建的内存就消失了，而主函数接收其中的返回值，因此主函数释放内存有所不同
    free(red_result->serial);
    free(red_result);
```
    3.强制类型转换与指针自增问题
```c
    void *add_num(void* arg)
{

    int *i = (int *)arg;//主函数传入参数是int类型的，但是子线程是void* arg，所以需要强制类型转换成int类型的
    (*i)++;//*i指向在int *i时候对应的地址，对于地址上的将字数字进行加1操作
    return NULL;
}
```

