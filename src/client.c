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

client_t *init_client(int fd, const char *default_dir)
{
    client_t *client = malloc(sizeof(client_t));
    client->fd = fd;
    client->transfer_mode = FLUX;
    client->type_ftp = TYPE_BINARY;
    client->username = NULL;
    client->password = NULL;
    if (default_dir == NULL)
        client->working_directory = DEFAULT_DIR;
    else
        client->working_directory = (char *) default_dir;
    client->in_transfert = 0;
    return client;
}

int add_client(server_t *server, int client_fd)
{
    for (int i = 0; i < BACKLOG; i++) {
        if (server->client[i]->fd == -1) {
            server->client[i]->fd = client_fd;
            FD_SET(client_fd, &server->fds);
            return (i);
        }
    }
    return (-1);
}

int remove_client(server_t *server, int client_fd)
{
    for (int i = 0; i < BACKLOG; i++) {
        if (server->client[i]->fd == client_fd) {
            FD_CLR(client_fd, &server->fds);
            server->client[i]->fd = -1;
            return (DISC);
        }
    }
    return (-1);
}

int check_client_command(server_t *serv, client_t *client)
{
    char *buffer = calloc(1, FD_SETSIZE);
    read(client->fd, buffer, FD_SETSIZE);
    if (buffer == 0 || buffer[0] == 0) {
        return remove_client(serv, client->fd);
    }
    handle_commands(serv, client, buffer);
    return (0);
}

void handle_client(server_t *serv)
{
    for (int i = 0; i < BACKLOG; i++) {
        int client = serv->client[i]->fd;
        if (client == -1)
            continue;
        if (FD_ISSET(client, &serv->fds) > 0) {
           int a = check_client_command(serv, serv->client[i]);
           if (a == DISC) {
               printf("client n°%d disconnected\n", i);
           }
        }
    }
    if (FD_ISSET(serv->sock_fd, &serv->fds)) {
        int ci = accept(serv->sock_fd, (struct sockaddr *)&serv->addr_in, (socklen_t *)&serv->accept_len);
        if (ci == 0) {
            printf("can't open client !");
            return;
        }
        int nc = add_client(serv, ci);
        if (nc == -1) {
            send_msg(ci, "cant'accept more client !\n");
            close(ci);
        }
        send_msg(ci, "220");
        printf("client n°%d connected\n", nc);
    }
}