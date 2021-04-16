/*
** EPITECH PROJECT, 2021
** cwd.c
** File description:
** c file
*/

#include <string.h>
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <ctype.h>
#include "ftp.h"

char *clean_str(char *str)
{
    char *clean = malloc(sizeof(char) * strlen(str));
    int i = 0;
    for (; str[i] != 0 && isprint(str[i]); i++) {
        clean[i] = str[i];
    }
    clean[i] = 0;
    return clean;
}

int cwd_cmd(server_t *serv, client_t *client, char *cmd)
{
    strtok(cmd, " ");
    char *pwd = strtok(NULL, " ");
    if (pwd == NULL)
        return (420);
    client->working_directory = clean_str(pwd);

    send_msg(client->fd, "250");
    return (200);
}