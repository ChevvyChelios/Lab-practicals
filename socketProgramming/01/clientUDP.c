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
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    char client_message[BUFFER_SIZE] = "Hello, server!";
    char server_response[BUFFER_SIZE];

    // Send the message to the server
    sendto(client_socket, client_message, sizeof(client_message), 0, (struct sockaddr *)&server_address, sizeof(server_address));

    // Receive the response from the server
    recvfrom(client_socket, server_response, sizeof(server_response), 0, NULL, NULL);

    // Print out the server's response
    printf("Received response from server: %s\n", server_response);

    // Close the socket
    close(client_socket);

    return 0;
}