//gcc -o server server.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 52579
#define SIZE 3


void inference(float* input, float* output)
{
    for (size_t i=0; i<SIZE; ++i)
    {
        for (size_t j=0; j<SIZE; ++j)
        {
            output[i] += input[SIZE*i + j];
        }
    }
}


int main(void)
{
    // create socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        return 1;
    }

    // struct about the connection destination
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // bind
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        perror("bind");
        return 1;
    }

    // listen
    int backlog = 1;
    if (listen(sock, backlog) != 0)
    {
        perror("listen");
        return 1;
    } else
    {
        printf("listen\n");
    }

    while(1)
    {
        int status;

        // accept socket
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int connected_socks = accept(sock, (struct sockaddr *)&client, &len);

        if (connected_socks == -1)
        {
            perror("accept");
        } else
        {
            printf("accepted\n");
        }

        // recieve
        float input[SIZE*SIZE] = {};
        status = recv(connected_socks, input, sizeof(input), 0);

        if (status == -1)
        {
            perror("recv");
        } else
        {
            printf("received\n");
        }

        // print recieved data
        printf("[ ");
        for (size_t i=0; i<SIZE; ++i)
        {
            for (size_t j=0; j<SIZE; ++j)
            {
                printf("%f ", input[SIZE*i + j]);
            }
        }
        printf("]\n");

        // inference
        float output[SIZE] = {};
        inference(input, output);

        // send
        status = send(connected_socks, output, sizeof(output), 0);

        if (status == -1)
        {
            perror("send");
        } else 
        {
            printf("send\n");
        }

        close(connected_socks);
    }

    close(sock);
    return 0;
}