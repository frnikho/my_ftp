/*
** EPITECH PROJECT, 2021
** cwd.c
** File description:
** c file
*/

#include <string.h>
#include <stdio.h>
#include <zconf.h>
#include "ftp.h"

int cwd_cmd(server_t *serv, client_t *client, char *cmd)
{
    char *new_cmd = strtok(cmd, " ");
    char *pwd = strtok(NULL, " ");
    printf("pwd: %s\n", pwd);
    client->working_directory = pwd;
    return (0);
}