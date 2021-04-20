/*
** EPITECH PROJECT, 2021
** pasv.c
** File description:
** c file
*/

#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <zconf.h>
#include "ftp.h"

int pasv_cmd(server_t *server, client_t *client, char *cmd)
{
    if (client->pass_fd != -1) {
        close(client->pass_fd);
    }
    client->pass_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    client->pass_in = (struct sockaddr_in){AF_INET, htons(0), INADDR_ANY};
    socklen_t size = sizeof(client->pass_in);
    if (bind(client->pass_fd, (struct sockaddr *)&client->pass_in, size)==-1) {
        printf("Error while binding !\n");
        return (0);
    }
    if (listen(client->pass_fd, 1) == -1) {
        printf("Error while listening !\n");
        return (0);
    }
    int p1 = ntohs(client->pass_in.sin_port) / 256;
    int p2 = ntohs(client->pass_in.sin_port) % 256;
    dprintf(client->fd, "227 Pasv (127, 0, 0, 1, %d, %d).\r\n", p1, p2);
    return (0);
}