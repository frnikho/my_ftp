/*
** EPITECH PROJECT, 2021
** syst.c
** File description:
** c file
*/

#include <stdio.h>
#include "ftp.h"

int syst_cmd(server_t *serv, client_t *client, char *cmd)
{

    printf("SYST CALLED\n");
    send_msg(client->fd, "215 UNIX Type: L8");
    return (0);
}