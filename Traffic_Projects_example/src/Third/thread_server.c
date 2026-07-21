// thread_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9096
#define BUF_SIZE 1024

void *handle_client(void *arg) {
    int client_fd = *(int*)arg;
    free(arg);
    char buf[BUF_SIZE];

    while (1) {
        int n = recv(client_fd, buf, sizeof(buf), 0);
        if (n <= 0) break;
        buf[n] = '\0';
        send(client_fd, buf, n, 0);
    }

    close(client_fd);
    return NULL;
}

int main() {
    int listen_fd, *client_fd_ptr;
    struct sockaddr_in addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(listen_fd, 5);

    printf("多线程服务器，端口 %d\n", PORT);

    while (1) {
        client_fd_ptr = malloc(sizeof(int));
        *client_fd_ptr = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_fd_ptr);
        pthread_detach(tid);  // 分离线程，自动回收资源
    }

    close(listen_fd);
    return 0;
}