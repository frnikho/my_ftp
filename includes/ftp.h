/*
** EPITECH PROJECT, 2021
** ftp.h
** File description:
** header file
*/

#ifndef FTP_INCLUDES_FTP_H_
#define FTP_INCLUDES_FTP_H_

#define BACKLOG 3
#define PROTOCOL 0

#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0

#include <netinet/in.h>

typedef struct server_s {
    struct sockaddr_in addr_in;
    int sock_fd;
    struct timeval timeout;
    fd_set fds;
    int *client_fd;
    socklen_t accept_len;
} server_t;

server_t *server_init(int port);
int server_close(server_t *server);
int server(long port, const char *fp);

int add_client(server_t *server, int client_fd);
void handle_client(server_t *serv);
int remove_client(server_t *server, int client_fd);

int send_msg(int client_fd, const char *msg);

volatile int quit;

#endif //FTP_INCLUDES_FTP_H_
