#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT        9096
#define MAX_EVENTS  10
#define BUF_SIZE    1024

int main() {
    int listen_fd, epoll_fd, client_fd;
    struct sockaddr_in addr;
    struct epoll_event ev, events[MAX_EVENTS];

    // 1. 创建监听 socket
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) { perror("socket"); exit(1); }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);
    }
    if (listen(listen_fd, 5) < 0) {
        perror("listen"); exit(1);
    }

    // 2. 创建 epoll 实例
    epoll_fd = epoll_create(1);
    ev.events  = EPOLLIN;          // 关注可读事件
    ev.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);

    printf("服务器启动，监听端口 %d ...\n", PORT);

    // 3. 事件循环
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; i++) {

            // 情况 A：新连接到来
            if (events[i].data.fd == listen_fd) {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);

                printf("新客户端连接，fd=%d\n", client_fd);

                // 把新客户端也加入 epoll 监听
                ev.events  = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev);
            }

            // 情况 B：已有客户端发来数据
            else {
                int fd = events[i].data.fd;
                char buf[BUF_SIZE];
                int n = recv(fd, buf, sizeof(buf), 0);

                if (n <= 0) {
                    // 客户端断开或出错
                    printf("客户端断开，fd=%d\n", fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
                    buf[n] = '\0';
                    printf("收到 fd=%d 的数据: %s\n", fd, buf);
                    send(fd, buf, n, 0);  // 回显
                }
            }
        }
    }

    close(listen_fd);
    close(epoll_fd);
    return 0;
}