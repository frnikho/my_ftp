/*
** EPITECH PROJECT, 2021
** client.c
** File description:
** c file
*/

#include <ftp.h>
#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>

int add_client(server_t *server, int client_fd)
{
    for (int i = 0; i < BACKLOG; i++) {
        if (server->client_fd[i] == -1) {
            server->client_fd[i] = client_fd;
            FD_SET(client_fd, &server->fds);
            return (i);
        }
    }
    return (-1);
}

int remove_client(server_t *server, int client_fd)
{
    for (int i = 0; i < BACKLOG; i++) {
        if (server->client_fd[i] == client_fd) {
            server->client_fd[i] = -1;
            FD_CLR(client_fd, &server->fds);
            return (CLIENT_DISCONNECT);
        }
    }
    return (-1);
}

int check_client_command(server_t *serv, int client)
{
    char *buffer = calloc(1, FD_SETSIZE);
    read(client, buffer, FD_SETSIZE);
    if (buffer == 0 || buffer[0] == 0) {
        return remove_client(serv, client);
    }
    handle_commands(serv, client, buffer);
    return (0);
}

void handle_client(server_t *serv)
{
    if (FD_ISSET(serv->sock_fd, &serv->fds)) {
        int ci = accept(serv->sock_fd, (struct sockaddr *)&serv->addr_in, (socklen_t *)&serv->accept_len);
        if (ci == -1) {
            printf("can't accept more client !\n");
            return;
        }
        int nc = add_client(serv, ci);
        send_msg(ci, "220");
        printf("client n°%d connected\n", nc);
    }
    for (int i = 0; i < BACKLOG; i++) {
        int client = serv->client_fd[i];
        if (client == -1)
            continue;
        if (FD_ISSET(client, &serv->fds) > 0) {
           int a = check_client_command(serv, client);
           if (a == CLIENT_DISCONNECT) {
               printf("client n°%d disconnected\n", i);
           }
        }
    }
}