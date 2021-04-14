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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <fcntl.h>
#include "ftp.h"

server_t *server_init(int port)
{
    server_t *serv = malloc(sizeof(server_t));
    serv->sock_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL);
    if (serv->sock_fd)
        serv->addr_in = (struct sockaddr_in){AF_INET, htons(port), INADDR_ANY};

    size_t size = sizeof(serv->addr_in);
    if (bind(serv->sock_fd, (struct sockaddr *)&serv->addr_in, size)) {
        free(serv);
        return NULL;
    }
    if ((listen(serv->sock_fd, BACKLOG)) != 0) {
        free(serv);
        return NULL;
    }
    serv->timeout = (struct timeval){TIMEOUT_SEC, TIMEOUT_USEC};

    FD_ZERO(&serv->fds);
    FD_SET(serv->sock_fd, &serv->fds);
    return (serv);
}

int server_run(server_t *serv)
{
    printf("FTP server launched at: %s:%d\n", inet_ntoa(serv->addr_in.sin_addr), htons(serv->addr_in.sin_port));
    socklen_t addlen = 0;
    int connected = 0;

    while (1) {
        FD_ZERO(&serv->fds);
        FD_SET(serv->sock_fd, &serv->fds);
        FD_SET(connected, &serv->fds);
        FD_SET(1, &serv->fds);
        int rc = select(MAX(connected, serv->sock_fd)+1, &serv->fds, NULL, NULL, &serv->timeout);

        if (FD_ISSET(serv->sock_fd, &serv->fds)) {
            printf("CATCH SOMETING !\n");
            connected = accept(serv->sock_fd, (struct sockaddr *)&serv->addr_in, (socklen_t *)&addlen);
            write(connected, "hello world\n" , 13);
            printf("Hello message sent\n");
            FD_SET(connected, &serv->fds);
        }
        if (((FD_ISSET(connected, &serv->fds))) != 0) {
            printf("CLIENT SENT SOMETHINGS: %d\n", FD_SETSIZE);
            char buffer[FD_SETSIZE];
            read(connected, &buffer, FD_SETSIZE);
            buffer[FD_SETSIZE] = 0;
            printf("%s\n", buffer);
            printf("...\n");
        }
        if (FD_ISSET(1, &serv->fds)) {

        }
        if (rc == -1)
            break;

    }

    return (0);
}

int server_close(server_t *server)
{
    if (!server)
        return (-1);
    if (close(server->sock_fd) == 0)
        return (-1);
    free(server);
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