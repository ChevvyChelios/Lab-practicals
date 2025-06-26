#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002
#define BUFFER_SIZE 256

int main() {
    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Enable the SO_REUSEADDR option to reuse the local address
    int reuse_addr = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 5);

    int client_socket = accept(server_socket, NULL, NULL);

    // Send a message to the client
    char server_message[BUFFER_SIZE] = "Hello, client!";
    send(client_socket, server_message, sizeof(server_message), 0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}