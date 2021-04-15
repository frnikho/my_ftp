/*
** EPITECH PROJECT, 2021
** dump.c
** File description:
** c file
*/

#include <stdio.h>
#include "ftp.h"

int dump_cmd(server_t *server, client_t *client, char *cmd)
{
    send_msgs(client->fd, client->username);
    send_msg(client->fd, "220");
    return (0);
}