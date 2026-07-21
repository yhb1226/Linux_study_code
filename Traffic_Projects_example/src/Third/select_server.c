// select_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9096
#define BUF_SIZE 1024
#define MAX_CLIENTS 1024

int main() {
    int listen_fd, client_fd, max_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];

    int client_fds[MAX_CLIENTS] = {0};  // 客户端 fd 数组

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 5);

    printf("select 服务器，端口 %d\n", PORT);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(listen_fd, &readfds);
        max_fd = listen_fd;

        // 把所有客户端 fd 加入集合
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_fds[i] > 0) {
                FD_SET(client_fds[i], &readfds);
                if (client_fds[i] > max_fd) {
                    max_fd = client_fds[i];
                }
            }
        }

        // select 阻塞等待
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            continue;
        }

        // 新连接
        if (FD_ISSET(listen_fd, &readfds)) {
            client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
            // 找个空位存起来
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_fds[i] == 0) {
                    client_fds[i] = client_fd;
                    break;
                }
            }
        }

        // 检查所有客户端是否有数据
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int fd = client_fds[i];
            if (fd > 0 && FD_ISSET(fd, &readfds)) {
                int n = recv(fd, buf, sizeof(buf), 0);
                if (n <= 0) {
                    close(fd);
                    client_fds[i] = 0;
                } else {
                    buf[n] = '\0';
                    send(fd, buf, n, 0);
                }
            }
        }
    }

    close(listen_fd);
    return 0;
}