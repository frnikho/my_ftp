/*
** EPITECH PROJECT, 2021
** list.c
** File description:
** c file
*/

#include "ftp.h"

int list_cmd(server_t *server, client_t *client, char *cmd)
{
    send_msg(client->fd, "125");
    send_msg(client->fd, "-rw-rw-rw- 1 user group 0 Feb 9 09:38 \\ subdirectory\\ file.txt");
    send_msg(client->fd, "-rw-rw-rw- 1 user group 0 Feb 9 09:38 \\ subdirectory\\ file.txt");
    send_msg(client->fd, "150");
    send_msg(client->fd, "226");
    return (0);
}