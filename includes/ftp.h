/*
** EPITECH PROJECT, 2021
** ftp.h
** File description:
** header file
*/

#ifndef FTP_INCLUDES_FTP_H_
#define FTP_INCLUDES_FTP_H_

#define DEBUG 1

#define BACKLOG 3
#define PROTOCOL 0
#define TIMEOUT_SEC 10
#define TIMEOUT_USEC 0
#define CLIENT_DISCONNECT 1
#define END_CMDS {0, 0}

#define SERVER_STARTUP_MSG "FTP server launched at: %s:%d\n"

#define ADDR(x) (inet_ntoa(x))

#include <netinet/in.h>

enum TRANSFER_MODE {
    FLUX,
    BLOCK,
    COMPRESSED
};

typedef struct server_s {
    struct sockaddr_in addr_in;
    int sock_fd;
    struct timeval timeout;
    fd_set fds;
    int *client_fd;
    socklen_t accept_len;
} server_t;


typedef struct client_s {
    int fd; // TODO Need be used in the futur
    char *working_directory;
    char *username;
    char *password;
} client_t;

server_t *server_init(int port);
int server_close(server_t *server);
int server(long port, const char *fp);

int add_client(server_t *server, int client_fd);
void handle_client(server_t *serv);
int remove_client(server_t *server, int client_fd);

int send_msg(int client_fd, const char *msg);

int handle_commands(server_t *server, int client_fd, char *cmd);

volatile int quit;

#endif //FTP_INCLUDES_FTP_H_
