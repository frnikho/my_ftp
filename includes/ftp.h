/*
** EPITECH PROJECT, 2021
** ftp.h
** File description:
** header file
*/

#ifndef FTP_INCLUDES_FTP_H_
#define FTP_INCLUDES_FTP_H_

#define DEBUG 1

#define READ_SIZE 4096

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

#define LIST_P "%s 0 nico nico 	%ld avril 14 17:00 %s \r\n"

#include <netinet/in.h>

enum DATA_MODE {
    PASSIVE_MODE,
    ACTIVE_MODE,
};

enum TRANSFER_MODE {
    FLUX,
    BLOCK,
    COMPRESSED
};

enum TYPE_FTP {
    TYPE_ASCII,
    TYPE_BINARY
};

typedef struct client_s {
    int fd; // TODO Need be used in the futur
    char *working_directory;
    char *username;
    char *password;
    enum TRANSFER_MODE transfer_mode;
    enum TYPE_FTP type_ftp;
    int in_transfert;

    int pass_fd;
    struct sockaddr_in pass_in;
    fd_set pass_fds;
    socklen_t pass_len;

    int port_fd;
    struct sockaddr_in port_in;
    fd_set port_fds;
    socklen_t port_len;

    enum DATA_MODE data_mode;

} client_t;

typedef struct server_s {
    const char *default_dir;
    int sock_fd;
    struct sockaddr_in addr_in;
    struct timeval timeout;
    fd_set fds;
    client_t **client;
    socklen_t accept_len;
} server_t;

char **str_split(char *c, char split);

server_t *server_init(int port, const char *default_dir);
int server_close(server_t *server);
int server(long port, const char *fp);

void accept_client(server_t *serv);
client_t *init_client(int fd, const char *default_dir);
int add_client(server_t *server, int client_fd);
void handle_client(server_t *serv);
int remove_client(server_t *server, int client_fd);

int send_msg(int client_fd, const char *msg);
int send_msgs(int client_fd, const char *msg);

int handle_commands(server_t *server, client_t *client, char *cmd);
int handle_data(server_t *server);

static int quit;

#endif //FTP_INCLUDES_FTP_H_