#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002
#define BUFFER_SIZE 256

int main() {
    // Create the client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Enable the SO_REUSEADDR option to reuse the local address
    int reuse_addr = 1;
    if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Receive a message from the server
    char server_response[BUFFER_SIZE];
    recv(client_socket, server_response, sizeof(server_response), 0);

    // Print out the server's response
    printf("Received response from server: %s\n", server_response);

    // Close the socket
    close(client_socket);

    return 0;
}