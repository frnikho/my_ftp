/*
** EPITECH PROJECT, 2021
** dele.c
** File description:
** c file
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ftp.h"

int dele_cmd(server_t *server, client_t *client, char *cmd)
{
    strtok(cmd, " ");
    char *file = strtok(NULL, " ");

    char *fp = calloc(1, sizeof(char)*256);

    strcat(fp, client->working_directory);
    strcat(fp, "/");
    strcat(fp, file);

    free(fp);

    return (0);
}