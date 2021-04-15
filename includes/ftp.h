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
#define TIMEOUT_SEC 0
#define TIMEOUT_USEC 1
#define DISC 1
#define END_CMDS {0, 0}

#define DATA_PORT 52659

#define DEFAULT_DIR "/tmp"
#define NOT_DEFINED_VALUE  "[not defined]"
#define SERVER_STARTUP_MSG "FTP server launched at: %s:%d\n"
#define ADDR(x) (inet_ntoa(x))

#include <netinet/in.h>

enum TRANSFER_MODE {
    FLUX,
    BLOCK,
    COMPRESSED
};

typedef struct client_s {
    int fd; // TODO Need be used in the futur
    char *working_directory;
    char *username;
    char *password;
    enum TRANSFER_MODE transfer_mode;
    int in_transfert;
} client_t;

typedef struct server_s {
    const char *default_dir;
    int sock_fd;
    struct sockaddr_in addr_in;
    struct timeval timeout;
    fd_set fds;
    client_t **client;
    socklen_t accept_len;


    int data_fd;
    struct sockaddr_in data_in;
    fd_set data_fds;
    client_t **data_client;
    socklen_t data_len;

} server_t;


server_t *server_init(int port, const char *default_dir);
int server_close(server_t *server);
int server(long port, const char *fp);

client_t *init_client(int fd, const char *default_dir);
int add_client(server_t *server, int client_fd);
void handle_client(server_t *serv);
int remove_client(server_t *server, int client_fd);

int send_msg(int client_fd, const char *msg);
int send_msgs(int client_fd, const char *msg);

int handle_commands(server_t *server, client_t *client, char *cmd);
int handle_data(server_t *server);

volatile int quit;

#endif //FTP_INCLUDES_FTP_H_
