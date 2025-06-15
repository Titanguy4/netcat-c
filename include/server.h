#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

void run_server(int port);
int create_server_socket();
void init_server_addr(struct sockaddr_in *addr, int port);
void bind_server(int server_fd, struct sockaddr_in *addr);
void listen_server(int server_fd);
int accept_client(int server_fd, struct sockaddr_in *addr);

#endif