/*
** EPITECH PROJECT, 2021
** user.c
** File description:
** c file
*/

#include <ftp.h>
#include <string.h>

int user_cmd(server_t *serv, client_t *client, char *cmd)
{
    char *username = strtok(NULL, " ");
    if (username != NULL) {
        client->username = strdup(username);
    }
    return (331);
}