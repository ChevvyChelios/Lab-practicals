// tcp_server_keepalive.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>           // close()
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/tcp.h>      // for TCP_KEEP* options (optional)

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Enable SO_KEEPALIVE
    int optval = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0) {
        perror("setsockopt SO_KEEPALIVE failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Optionally set TCP_KEEPIDLE, TCP_KEEPINTVL, TCP_KEEPCNT (Linux only)
    /*
    int keep_idle = 10;   // seconds before starting keepalive
    int keep_intvl = 3;   // interval between probes
    int keep_cnt = 5;     // number of probes before dropping

    setsockopt(server_fd, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(keep_idle));
    setsockopt(server_fd, IPPROTO_TCP, TCP_KEEPINTVL, &keep_intvl, sizeof(keep_intvl));
    setsockopt(server_fd, IPPROTO_TCP, TCP_KEEPCNT, &keep_cnt, sizeof(keep_cnt));
    */

    // Configure address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d with SO_KEEPALIVE enabled...\n", PORT);

    addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to client: %s\n", inet_ntoa(client_addr.sin_addr));

    // Receive data
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes = read(client_fd, buffer, BUFFER_SIZE);
        if (bytes <= 0) {
            printf("Client disconnected or connection lost.\n");
            break;
        }
        printf("Received from client: %s\n", buffer);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

