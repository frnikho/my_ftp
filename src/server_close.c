/*
** EPITECH PROJECT, 2021
** server_close.c
** File description:
** c file
*/

#include "ftp.h"
#include <zconf.h>
#include <stdlib.h>

int server_close(server_t *server)
{
    if (!server)
        return (-1);
    close(server->sock_fd);
    for (int i = 0; i < BACKLOG; i++) {
        if (server->client[i]->fd != -1) {
            close(server->client[i]->fd);
            free(server->client[i]);
        }
    }
    free(server->client);
    free(server);
    return (0);
}