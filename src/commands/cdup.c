/*
** EPITECH PROJECT, 2021
** cdup.c
** File description:
** c file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ftp.h"

int cdup_cmd(server_t *server, client_t *client, char *cmd)
{
    char *path = client->working_directory;
    char **path_folder = str_split(path, '/');

    char *new_path = malloc(sizeof(char) * 128);
    for (int i = 0; path_folder[i]; i++) {
        if (path_folder[i+1] == NULL)
            break;
        strcat(new_path, path_folder[i]);
        strcat(new_path, "/");
    }
    client->working_directory = new_path;
    char *msg = malloc(sizeof(char) * 128);
    sprintf(msg, "250 \"%s\"", new_path);
    send_msg(client->fd, msg);
    free(msg);
    return (0);
}