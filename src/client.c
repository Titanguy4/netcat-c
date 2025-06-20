#include "../include/client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void run_client(const char *ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = create_client_socket();
    init_client_addr(&serv_addr, ip, port);
    connect_to_server(sockfd, &serv_addr);
    printf("[CLIENT] Connecté à %s:%d\n", ip, port);
    client_communication(sockfd);
    close(sockfd);
}

int create_client_socket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void init_client_addr(struct sockaddr_in *addr, const char *ip, int port)
{
    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
}

void connect_to_server(int sockfd, struct sockaddr_in *addr)
{
    if (connect(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
    {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

void client_communication(int sockfd)
{
    char buffer[1024];
    fd_set fds;
    int maxfd;
    while (1)
    {
        FD_ZERO(&fds);
        FD_SET(0, &fds); // stdin
        FD_SET(sockfd, &fds);
        maxfd = sockfd > 0 ? sockfd : 0;
        if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 0)
        {
            perror("select");
            break;
        }
        if (FD_ISSET(0, &fds))
        {
            ssize_t n = read(0, buffer, sizeof(buffer));
            if (n > 0)
            {
                if (write(sockfd, buffer, n) < 0)
                {
                    perror("write to server");
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if (FD_ISSET(sockfd, &fds))
        {
            ssize_t n = read(sockfd, buffer, sizeof(buffer));
            if (n > 0)
            {
                if (write(1, buffer, n) < 0)
                {
                    perror("write to stdout");
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
}