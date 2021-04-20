/*
** EPITECH PROJECT, 2021
** port.c
** File description:
** c file
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <zconf.h>
#include "ftp.h"

struct sockaddr_in create_addr(int port, const char *addr)
{
    struct sockaddr_in ad = {
        AF_INET,
        htons(port),
        inet_addr(addr)
    };
    return ad;
}

int init_data_socket(client_t *client, int port, char *address)
{
    if (client->port_fd == -1)
        close(client->port_fd);
    client->port_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    if (client->port_fd == -1) {
        printf("Can't startup client port socket");
        return (0);
    }
    struct sockaddr_in addr = create_addr(port, address);
    int *f = &client->port_fd;
    printf("%s : %d\n", inet_ntoa(addr.sin_addr), addr.sin_port);
    int rt = connect((*f), (const struct sockaddr *) &addr, sizeof(addr));
    if (rt == -1) {
        printf("Error while connecting to server !\n");
    } else {
        printf("Connected to the data server !\n");
        send_msg(client->fd, "200");
        client->data_mode = PASSIVE_MODE;
    }
    return (0);
}

int port_cmd(server_t *server, client_t *client, char *cmd)
{
    if (client->username == NULL) {
        send_msg(client->fd, "530");
        return (0);
    }
    char **port = str_split(cmd, ',');
    char *aa1 = str_split(port[0], ' ')[1];
    long a1 = strtol(aa1, NULL, 10);
    long a2 = strtol(port[1], NULL, 10);
    long a3 = strtol(port[2], NULL, 10);
    long a4 = strtol(port[3], NULL, 10);
    long p1 = strtol(port[4], NULL, 10);
    long p2 = strtol(port[5], NULL, 10);
    char *adr = malloc(sizeof(char) * 128);
    sprintf(adr, "%d.%d.%d.%d", a1, a2, a3, a4);
    int p = p1*256+p2;
    init_data_socket(client, p, adr);
    return (0);
}