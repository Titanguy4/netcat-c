#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/server.h"
#include "../include/client.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s [-l -p port] | [ip port]\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "-p") == 0 && argc >= 4)
    {
        int port = atoi(argv[3]);
        run_server(port);
    }
    else if (argc >= 3)
    {
        char *ip = argv[1];
        int port = atoi(argv[2]);
        printf("[MODE CLIENT] IP: %s, Port: %d\n", ip, port);
        run_client(ip, port);
    }
    else
    {
        printf("Arguments invalides.\n");
        return 1;
    }
    return 0;
}