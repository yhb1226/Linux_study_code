// fork_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define PORT 9096
#define BUF_SIZE 1024

// 回收僵尸进程
void sigchld_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    int listen_fd, client_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buf[BUF_SIZE];

    signal(SIGCHLD, sigchld_handler);  // 防止僵尸进程

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 5);

    printf("多进程服务器，端口 %d\n", PORT);

    while (1) {
        client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) continue;

        pid_t pid = fork();
        if (pid == 0) {
            // 子进程：处理客户端
            close(listen_fd);  // 子进程不需要监听 socket

            while (1) {
                int n = recv(client_fd, buf, sizeof(buf), 0);
                if (n <= 0) break;
                buf[n] = '\0';
                send(client_fd, buf, n, 0);
            }

            close(client_fd);
            exit(0);
        } else {
            // 父进程：继续接受新连接
            close(client_fd);  // 父进程不需要客户端 socket
        }
    }

    close(listen_fd);
    return 0;
}