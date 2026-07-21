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
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 5);

    printf("单线程阻塞服务器，端口 %d\n", PORT);

    while (1) {
        // 阻塞等待连接
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