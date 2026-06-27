#include <stdio.h>

int main(int argc, char const *argv[])
{
    /*
     * char *__restrict __filename: 字符串表示要打开的文件名称
     * const char *__restrict __modes: 访问模式
     * (1) r: 只读模式 如果没有文件报错
     * (2) w: 只写模式 如果文件存在清空文件 如果不存在创建新文件
     * (3) a: 只追加模式 如果文件存在末尾追加写 如果不存在创建新文件
     * (4) r+: 读写模式 文件必须存在 写入是从头一个一个覆盖
     * (5) w+: 读写模式 如果文件存在清空文件 如果不存在创建新文件
     * (6) a+: 追加读写模式 如果文件存在末尾追加写 如果不存在创建新文件
     * return: FILE * 结构体指针 表示一个文件
     *         报错返回NULL
    FILE *fopen(const char *__restrict __filename,
                 const char *__restrict __modes)
    */
   char *filename = "io.txt";
    FILE *ioFile = fopen(filename,"w");

    if(ioFile == NULL)
    {
        printf("fail打开文件失败\n");

    }else{

        printf("success打开文件成功\n");

    }

        /**
     * __stream: 需要关闭的文件
     * return: 成功返回0 失败返回EOF(负数) 通常关闭文件失败会直接报错
     * int fclose (FILE *__stream)
     */
    int result = fclose(ioFile);
    if (result == EOF)
    {
        printf("关闭文件失败\n");
    }else if (result== 0)
    {
        printf("关闭文件成功\n");
    }

    return 0;
}