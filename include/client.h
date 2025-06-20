#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>

void run_client(const char *ip, int port);
int create_client_socket();
void init_client_addr(struct sockaddr_in *addr, const char *ip, int port);
void connect_to_server(int sockfd, struct sockaddr_in *addr);
void client_communication(int sockfd);

#endif