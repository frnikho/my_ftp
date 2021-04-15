/*
** EPITECH PROJECT, 2021
** qui.c
** File description:
** c file
*/

#include <ftp.h>
#include <stdio.h>

int quit_cmd(server_t *server, client_t *client, char *cmd)
{
    printf("QUIT\n");
    send_msg(client->fd, "221");
    if (!client->in_transfert)
        remove_client(server, client->fd);
    return (0);
}