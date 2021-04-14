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
    serv->client_fd = malloc(sizeof(int) * (BACKLOG + 1));
    for (int i = 0; i < BACKLOG; i++)
        serv->client_fd[i] = -1;
    serv->client_fd[BACKLOG] = 0;
    serv->accept_len = 0;
    return 0;
}

server_t *server_init(int port)
{
    server_t *serv = malloc(sizeof(server_t));
    serv->sock_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    if (serv->sock_fd)
        serv->addr_in = (struct sockaddr_in){AF_INET, htons(port), INADDR_ANY};
    size_t size = sizeof(serv->addr_in);
    if (bind(serv->sock_fd, (struct sockaddr *)&serv->addr_in, size)) {
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
