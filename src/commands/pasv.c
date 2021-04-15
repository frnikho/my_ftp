/*
** EPITECH PROJECT, 2021
** pasv.c
** File description:
** c file
*/

#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "ftp.h"

int pasv_cmd(server_t *server, client_t *client, char *cmd)
{
  /*  server->data_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    server->data_in = (struct sockaddr_in){AF_INET, htons(DATA_PORT), INADDR_ANY};
    size_t size = sizeof(server->data_in);
    if (bind(server->data_fd, (struct sockaddr *)&server->data_in, size))
        return (0);
    if (listen(server->data_fd, BACKLOG) != 0)  {
        return (0);
    }*/
    int p1 = DATA_PORT / 256;
    int p2 = 179;

    char *msg = malloc(sizeof(char) * 128);
    sprintf(msg, "227 Entering Passive Mode (127, 0, 0, 1, %d, %d)", p1, p2);
    send_msg(client->fd, msg);
    free(msg);

    return (0);
}