/*
** EPITECH PROJECT, 2021
** server_init.c
** File description:
** c file
*/

#include <ftp.h>
#include <stdlib.h>

int init_queue(server_t *serv)
{
    serv->timeout = (struct timeval){TIMEOUT_SEC, TIMEOUT_USEC};
    FD_ZERO(&serv->fds);
    FD_SET(serv->sock_fd, &serv->fds);
    serv->client = malloc(sizeof(client_t*) * (BACKLOG + 1));
    for (int i = 0; i < BACKLOG; i++) {
        serv->client[i] = init_client(-1, serv->default_dir);
    }
    serv->client[BACKLOG] = 0;
    serv->client[BACKLOG] = 0;
    serv->accept_len = 0;
    return 0;
}

server_t *server_init(int port, const char *default_dir)
{
    server_t *serv = malloc(sizeof(server_t));
    serv->default_dir = default_dir;
    serv->sock_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    int true = 1;
    setsockopt(serv->sock_fd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
    if (serv->sock_fd)
        serv->addr_in = (struct sockaddr_in){AF_INET, htons(port), INADDR_ANY};
    size_t size = sizeof(serv->addr_in);
    if (bind(serv->sock_fd, (struct sockaddr *)&serv->addr_in, size) != 0) {
        free(serv);
        return NULL;
    }
    if ((listen(serv->sock_fd, BACKLOG)) != 0) {
        free(serv);
        return NULL;
    }
    init_queue(serv);
    quit = 0;
    return (serv);
}
