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
        //handle_data(s);
    }
    printf("server stopped ! quit %d\n", quit);
    return (0);
}

int handle_data(server_t *server)
{
    FD_ZERO(&server->data_fds);
    FD_SET(server->data_fd, &server->data_fds);

    if (select(FD_SETSIZE, &server->data_fds, NULL, NULL, &server->timeout) == -1) {
        printf("ERROR WHILE CALLING SELECT !\n");
    }

    if (FD_ISSET(server->data_fd, &server->data_fds)) {
        int ci = accept(server->data_fd, (struct sockaddr *)&server->data_in, (socklen_t *)&server->data_len);
        if (ci == 0) {
            printf("can't open client !");
            return (0);
        }
        printf("CLIENT DATA CI %d\n", ci);
    }
}

int server_data_init(server_t *server)
{
    server->data_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    server->data_in = (struct sockaddr_in){AF_INET, htons(DATA_PORT), INADDR_ANY};
    size_t size = sizeof(server->data_in);
    if (bind(server->data_fd, (struct sockaddr *)&server->data_in, size))
        return (0);
    if (listen(server->data_fd, BACKLOG) != 0)  {
        return (0);
    }
    return (0);
}

int server(long port, const char *fp)
{
    server_t *serv = server_init((int) port, fp);
    //server_data_init(serv);
    if (!serv) {
        printf("can't launch ftp server !\n");
        return (-1);
    }
    server_run(serv);
    server_close(serv);
    return (0);
}