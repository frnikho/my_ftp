/*
** EPITECH PROJECT, 2021
** port.c
** File description:
** c file
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "ftp.h"

int port_cmd(server_t *server, client_t *client, char *cmd)
{
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
    int p = htons(p1*256+p2);
    printf("%s : %d\n", adr, p);

    return (200);
}