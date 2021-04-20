/*
** EPITECH PROJECT, 2021
** cwd.c
** File description:
** c file
*/

#include <string.h>
#include <zconf.h>
#include <stdlib.h>
#include <ctype.h>
#include "ftp.h"

static char *clean_str(char *str)
{
    char *clean = calloc(1, sizeof(char) * (strlen(str) + 10));
    for (int i = 0; str[i] != 0 && isprint(str[i]); i++)
        clean[i] = str[i];
    return clean;
}

int start_with(const char *str, const char *compare)
{
    if (strncmp(str, compare, strlen(compare)) == 0)
        return 1;
    return 0;
}

int cwd_cmd(server_t *serv, client_t *client, char *cmd)
{
    strtok(cmd, " ");
    char *pwd = strtok(NULL, " ");
    if (pwd == NULL)
        return (420);
    if (!start_with(clean_str(pwd), "/")) {
        strcat(client->working_directory, "/");
        strcat(client->working_directory, clean_str(pwd));
    } else {
        client->working_directory = clean_str(pwd);
    }
    send_msg(client->fd, "250");
    return (0);
}