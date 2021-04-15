/*
** EPITECH PROJECT, 2021
** type.c
** File description:
** c file
*/

#include <zconf.h>
#include <string.h>
#include "ftp.h"

int type_cmd(server_t *server, client_t *client, char *cmd)
{
    strtok(NULL, " ");
    char *type = strtok(NULL, " ");
    if (strstr(type, "I") != NULL) {
        client->type_ftp = TYPE_BINARY;
        send_msg(client->fd, "200");
    } else if (strstr(type, "A") != NULL) {
        client->type_ftp = TYPE_ASCII;
        send_msg(client->fd, "200");
    } else {
        send_msg(client->fd, "421");
    }
    return (0);
}