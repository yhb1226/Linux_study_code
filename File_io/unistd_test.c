#include <stdio.h>      
#include <unistd.h>     
#include <fcntl.h>
/*
要用底层文件打开/控制 → 包含 <fcntl.h>

要用内存、转换、退出等通用功能 → 包含 <stdlib.h>

要用系统调用（读写、fork、进程 ID 等） → 包含 <unistd.h>
*/
int main()
{
    
    /*
    * char *_path: 打开文件的路径
    * int _oflag: 打开文件的模式
    * (1) O_RDONLY 只读模式
    * (2) O_WRONLY 只写模式
    * (3) O_RDWR 读写模式
    * (4) O_CREAT 如果不存在创建文件
    * (5) O_APPEND 追加写模式
    * (6) O_TRUNC 截断文件长度为0
    * ...可变参数: O_CREAT 创建文件的权限 0664
    * return: 文件描述符 如果打开文件失败 返回-1 同时设置全局变量errno表示对应的错误
    * int open (const char *_path, int _oflag, ...)
    */

    /*
    * 文件权限使用八进制数表示，每位数字由以下权限值相加得到：
    *   r(读) = 4,  w(写) = 2,  x(执行) = 1
    * 例如：6 = 4+2（读写），4 = 4（只读）
    *
    * 权限分为三组：所有者(user)、所属组(group)、其他人(other)。
    *
    * 0664 含义：
    *   所有者：6 → 读写
    *   所属组：6 → 读写
    *   其他人：4 → 只读
    *
    * 前导 0 表示八进制整数。
    * 仅在 open() 的 oflag 包含 O_CREAT 时才需要提供第三个参数（权限）。
    * 实际创建文件的权限还受 umask 影响：最终权限 = 0664 & ~umask。
    */

    //Linux操作系统有文件权限保护，默认创建的文件会被删除掉其他用户的写权限
    int result = open("io1.txt",O_RDONLY | O_CREAT,0664);

    if(result == -1)
    {

        printf("打开失败");
    }else{

        printf("打开成功\n");
    }


    return 0;
}
