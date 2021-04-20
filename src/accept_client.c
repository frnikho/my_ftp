/*
** EPITECH PROJECT, 2021
** accept_client
** File description:
** c filez
*/

#include <stdio.h>
#include <zconf.h>
#include "ftp.h"

void accept_client(server_t *serv)
{
    socklen_t *len = (socklen_t *)&serv->accept_len;
    if (FD_ISSET(serv->sock_fd, &serv->fds)) {
        int ci = accept(serv->sock_fd, (struct sockaddr *)&serv->addr_in, len);
        if (ci == 0) {
            printf("can't open client !");
            return;
        }
        int nc = add_client(serv, ci);
        if (nc == -1) {
            send_msg(ci, "cant'accept more client !\n");
            close(ci);
        }
        send_msg(ci, "220");
        printf("client n°%d connected\n", nc);
    }
}
