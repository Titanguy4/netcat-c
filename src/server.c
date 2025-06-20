#include "../include/server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void run_server(int port)
{
    int server_fd, client_fd;
    struct sockaddr_in addr;

    server_fd = create_server_tcp_socket();
    init_server_addr(&addr, port);
    bind_server(server_fd, &addr);
    listen_server(server_fd);

    client_fd = accept_client(server_fd, &addr);

    close(client_fd);
    close(server_fd);
}

int create_server_tcp_socket()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error during the initialization of the socket server");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void init_server_addr(struct sockaddr_in *addr, int port)
{
    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
}

void bind_server(int server_fd, struct sockaddr_in *addr)
{
    if (bind(server_fd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
    {
        perror("Error to bind server port");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[SERVER] Bind sur le port %d\n", ntohs(addr->sin_port));
}

void listen_server(int server_fd)
{
    if (listen(server_fd, 1) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[SERVER] En écoute...\n");
}

int accept_client(int server_fd, struct sockaddr_in *addr)
{
    socklen_t addrlen = sizeof(*addr);
    int client_fd = accept(server_fd, (struct sockaddr *)addr, &addrlen);
    if (client_fd < 0)
    {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("[SERVER] Connexion acceptée !\n");
    return client_fd;
}