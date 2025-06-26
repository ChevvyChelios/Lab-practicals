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
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    char server_message[BUFFER_SIZE] = "Hello";

    while (1) {
        // Receive data from the client
        struct sockaddr_in client_address;
        socklen_t addr_len = sizeof(client_address);
        char client_message[BUFFER_SIZE];

        recvfrom(server_socket, client_message, sizeof(client_message), 0, (struct sockaddr *)&client_address, &addr_len);

        // Print out the client's message
        printf("Received message from %s:%d: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), client_message);

        // Send a response back to the client
        sendto(server_socket, server_message, sizeof(server_message), 0, (struct sockaddr *)&client_address, addr_len);
    }

    // Close the socket
    close(server_socket);

    return 0;
}