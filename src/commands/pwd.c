/*
** EPITECH PROJECT, 2021
** pwd.c
** File description:
** c file
*/

#include <zconf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ftp.h"

int pwd_cmd(server_t *server, client_t *client, char *cmd)
{
    char *msg = malloc(sizeof(char) * 128);
    if (client->working_directory == NULL) {
        sprintf(msg, "257 \"%s\"", DEFAULT_DIR);
        printf("default pwd\n");
    } else {
        sprintf(msg, "257 \"%s\"", client->working_directory);
    }
    send_msg(client->fd, msg);
    free(msg);
    return (0);
}