#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    
    printf("Server is listening on port 9002...\n",);
    
    int client_socket = accept(server_socket, NULL, NULL);
    
    int number;
    recv(client_socket, &number, sizeof(number), 0);
    
    char *response = (number % 2 == 0) ? "Even" : "Odd";
    send(client_socket, response, strlen(response) + 1, 0);

    close(client_socket);
    close(server_socket);
    return 0;
}