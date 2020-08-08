//gcc -o client client.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 52579
#define SIZE 3


int main(void)
{
    int status;

    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // struct about the connection destination
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect server
    status = connect(sock, (struct sockaddr *)&server, sizeof(server));
    if (status == -1)
    {
        perror("connect");
    } else {
        printf("connected\n");
    }

    // input
    float input[SIZE*SIZE] = {
        0.f, 1.f, 2.f,
        3.f, 4.f, 5.f,
        6.f, 7.f, 8.f
    };

    // send
    status = send(sock, input, sizeof(input), 0);
    if (status == -1)
    {
        perror("send");
    } else {
        printf("send\n");
    }

    // recieve
    float output[SIZE] = {};
    status = recv(sock, output, sizeof(output), 0);
    if (status == -1)
    {
        perror("recv");
    } else {
        printf("received\n");
    }

    // print received data
    printf("[ ");
    for(size_t i=0; i<SIZE; ++i)
    {
        printf("%f ", output[i]);
    }
    printf("]\n");

    // close socket
    close(sock);

    return 0;
}