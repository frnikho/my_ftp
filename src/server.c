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
#include "ftp.h"

void signal_callback_handler(int signum)
{
    quit = 1;
}

int send_msgs(int client_fd, const char *msg)
{
    int a = 0;
    #ifdef DEBUG
    printf("[DEBUG] => send message '%s'\n", msg);
    #endif
    if (msg == NULL)
        a = write(client_fd, NOT_DEFINED_VALUE, strlen(NOT_DEFINED_VALUE));
    else
        a = write(client_fd, msg, strlen(msg));
    return a;
}

int send_msg(int client_fd, const char *msg)
{
    int a = 0;
    #ifdef DEBUG
    printf("[DEBUG] => send message '%s'\n", msg);
    #endif
    if (msg == NULL) {
        a = write(client_fd, NOT_DEFINED_VALUE, strlen(NOT_DEFINED_VALUE));
    } else {
        a = write(client_fd, msg, strlen(msg));
        write(client_fd, " \r\n", 3);
    }
    return a;
}

int server_run(server_t *s)
{
    signal(SIGINT, signal_callback_handler);
    int port = htons(s->addr_in.sin_port);
    printf(SERVER_STARTUP_MSG, ADDR(s->addr_in.sin_addr), port);
    while (quit != 1) {
        FD_ZERO(&s->fds);
        FD_SET(s->sock_fd, &s->fds);
        for (int i = 0; i < BACKLOG; i++)
            s->client[i]->fd != -1 ? FD_SET(s->client[i]->fd, &s->fds) : 0;
        if (select(FD_SETSIZE, &s->fds, NULL, NULL, &s->timeout) == -1)
            break;
        handle_client(s);
    }
    printf("server stopped ! quit %d\n", quit);
    return (0);
}

int server(long port, const char *fp)
{
    server_t *serv = server_init((int) port, fp);
    if (!serv) {
        printf("can't launch ftp server !\n");
        return (-1);
    }
    server_run(serv);
    server_close(serv);
    return (0);
}