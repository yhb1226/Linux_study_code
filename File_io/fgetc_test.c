#include <stdio.h>
int main(int argc, char const *argv[])
{
    
    char *name = "io.txt";
    FILE *nowfile = fopen(name,"r");
    if(nowfile == NULL)
    {
        printf("打开失败\n");
    }else{

        printf("打开成功\n");
    }

    char a = fgetc(nowfile);
    while(a != EOF)
    {
        printf("%c",a);
        a = fgetc(nowfile);
    }
    printf("\n");
    // 读取文件内容，fgets读取文件数据的方法
    /**
     * char *_restrict _s: 接收读取到的字符串
     * int _n: 接收数据的长度
     * FILE *_restrict _stream: 打开要读取的文件
     * return: 成功返回自身 失败返回NULL 可以直接使用while
     * char * fgets (char * _restrict _s, int _n, FILE *_restrict _stream)
     */
    int fileclose = fclose(nowfile);
    if(fileclose == EOF)
    {
        printf("关闭失败");

    }else{

        printf("关闭成功\n");
    }


    
    return 0;
}
