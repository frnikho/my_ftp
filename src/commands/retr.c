/*
** EPITECH PROJECT, 2021
** retr.c
** File description:
** c file
*/

#include <zconf.h>
#include "ftp.h"

int retr_cmd(server_t *server, client_t *client, char *cmd)
{
    send_msg(client->port_fd, "abcdef");
    send_msg(client->port_fd, "200");
    close(client->port_fd);
    return (0);
}