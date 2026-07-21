// blocking_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9096
#define BUF_SIZE 1024

int main() {
    int listen_fd, client_fd;
    //struct sockaddr_in：这是 Linux 网络编程中标准的“IP地址 + 端口号”结构体，它的全称是 socket address, internet，即互联网套接字地址
    struct sockaddr_in addr, client_addr;
    /*
    sizeof(client_addr)：计算出 sockaddr_in 这个结构体在内存里占了多大空间（通常是 16 个字节）。
    socklen_t：这是专门用来存放地址长度的变量类型，可以看作是一种特殊的整数。它是 Linux 系统定义好的，专门为了和内核打交道时不会有类型不匹配的警告。
    */
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];

    //创建监听客户端连接请求的
    /*
    extern int socket (int __domain, int __type, int __protocol) __THROW;
    int __domain：填的是WIFI类型，大多数默认ipv4即可
    int __type：传输层协议，SOCK_STREAM是tcp协议(可靠，不丢包)，SOCK_DGRAM是udp协议(会丢包，但延迟低)
    int __protocol：默认0即可
    */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;       // 使用 IPv4
    addr.sin_port        = htons(PORT);   // 监听 9096 端口
    addr.sin_addr.s_addr = INADDR_ANY;   // 监听本机所有 IP 地址

    //类比：socket() 是装了一部电话，bind() 是去电信公司给这部电话申请了一个固定的电话号码（端口号）。现在别人才能打这个号码找到你。
    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    //listen：把电话设为“等待来电”模式，并设置排队人数
    listen(listen_fd, 5);

    printf("单线程阻塞服务器，端口 %d\n", PORT);

    while (1) {
        // 阻塞等待庐山派发送连接请求
        client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        printf("客户端连接\n");

        // 处理这个客户端，直到它断开
        while (1) {
            int n = recv(client_fd, buf, sizeof(buf), 0);
            if (n <= 0) {
                printf("客户端断开\n");
                close(client_fd);
                break;
            }
            buf[n] = '\0';
            printf("收到: %s", buf);
            send(client_fd, buf, n, 0);
        }
    }

    close(listen_fd);
    return 0;
}