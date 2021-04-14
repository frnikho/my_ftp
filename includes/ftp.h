/*
** EPITECH PROJECT, 2021
** ftp.h
** File description:
** header file
*/

#ifndef FTP_INCLUDES_FTP_H_
#define FTP_INCLUDES_FTP_H_

#define BACKLOG 1
#define PROTOCOL 0

#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0

#include <netinet/in.h>

typedef struct server_s {
    struct sockaddr_in addr_in;
    int sock_fd;
    struct timeval timeout;
    fd_set fds;
} server_t;

server_t *server_init(int port);
int server_close(server_t *server);
int server(long port, const char *fp);

#endif //FTP_INCLUDES_FTP_H_
