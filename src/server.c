/*
** EPITECH PROJECT, 2021
** server.c
** File description:
** c file
*/

#include <stdlib.h>
#include <zconf.h>
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <fcntl.h>
#include <ctype.h>
#include "ftp.h"

void signal_callback_handler(int signum)
{
    quit = 1;
}

int check_quit(const char *received)
{
    for (int i = 0; received[i]; i++) {
        if (!isprint(received[i])) {
            printf("%d -", received[i]);
        }
        if (received[i] == EOF) {
            printf("TES GRANDS MORTS\n");
        }
    }
    return (0);
}

int send_code(int client_fd, long code)
{
    write(client_fd, &code, 1);
}

int send_msg(int client_fd, const char *msg)
{
    printf("[DEBUG] => send message '%s'\n", msg);

    int a = write(client_fd, msg, strlen(msg));
    write(client_fd, "\r\n", 2); //TODO CHECK CRLF
    return a;
}

int server_run(server_t *serv)
{
    signal(SIGINT, signal_callback_handler);
    printf("FTP server launched at: %s:%d\n", inet_ntoa(serv->addr_in.sin_addr), htons(serv->addr_in.sin_port));
    while (quit != 1) {
        FD_ZERO(&serv->fds);
        FD_SET(serv->sock_fd, &serv->fds);
        for (int i = 0; i < BACKLOG; i++) {
            if (serv->client_fd[i] == -1)
                continue;
            FD_SET(serv->client_fd[i], &serv->fds);
        }
        if (select(FD_SETSIZE, &serv->fds, NULL, NULL, &serv->timeout) == -1)
            break;
        handle_client(serv);
    }
    printf("server stopped ! quit %d\n", quit);
    return (0);
}

int server(long port, const char *fp)
{
    server_t *serv = server_init((int) port);
    if (!serv) {
        printf("can't launch ftp server !\n");
        return (-1);
    }
    server_run(serv);
    server_close(serv);
    return (0);
}