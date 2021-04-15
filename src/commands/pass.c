/*
** EPITECH PROJECT, 2021
** pass.c
** File description:
** c file
*/

#include <stdio.h>
#include "ftp.h"

int pass_cmd(server_t *serv, client_t *client, char *cmd)
{
    printf("PASS CMD!\n");
    return (230);
}