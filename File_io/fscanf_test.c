#include <stdio.h>
int main(int argc, char const *argv[])
{
    char*filename = "use.txt";
    FILE*use = fopen(filename,"r");
    if(use == NULL)
    {

        printf("失败\n");
    }else{

        printf("成功\n");
    }

        /**
     * FILE *_restrict _stream: 打开的文件
     * const char *_restrict _format: 带有格式化的字符串（固定格式接收）
     * ...可变参数: 填写格式化的字符串（接收数据提前声明的变量）
     * return: 成功匹配到的参数的个数 如果匹配失败返回0 报错或者文件结束EOF
     * int fscanf (FILE *_restrict _stream,const char *_restrict _format, ...)
     */

    char name[30];
    int age;
    char wife[50];

    int fscanfr = fscanf(use,"%s %d %s",name,&age,wife);
    if(fscanfr == EOF)
    {

        printf("失败\n");
    }else{

        printf("成功接收到参数有%d个\n",fscanfr);
        printf("%s在%d时候爱上了%s\n",name,age,wife);
    }


    int result = fclose(use);
    if(result == EOF)
    {

        printf("失败\n");
    }else{

        printf("成功\n");
    }


    return 0;
}
