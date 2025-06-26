#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main() {
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr*)&server_address,
	sizeof(server_address));
    if(connection_status == -1) {
        printf("There was an error making a connection to the remote socket\n");
        return 1;
    }

    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);

    send(network_socket, &number, sizeof(number), 0);

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);
    
    printf("The server says the number is: %s\n", server_response);

    close(network_socket);
    return 0;
}