/*
** EPITECH PROJECT, 2021
** cmd.h
** File description:
** header file
*/

#ifndef FTP_INCLUDES_CMD_H_
#define FTP_INCLUDES_CMD_H_

#include "ftp.h"

#define USER_CMD {"USER", user_cmd}
#define PASS_CMD {"PASS", pass_cmd}
#define CWD_CMD {"CWD", cwd_cmd}
#define MODE_CMD {"MODE", mode_cmd}
#define REIN_CMD {"REIN", rein_cmd}
#define QUIT_CMD {"QUIT", quit_cmd}
#define DUMP_CMD {"DUMP", dump_cmd}

typedef struct cmd_s {
    char *name;
    int (*cmd) (server_t *server, client_t *client, char *cmd);
} cmd_t;

int mode_cmd(server_t *serv, client_t *client, char *cmd);
int rein_cmd(server_t *serv, client_t *client, char *cmd);
int cwd_cmd(server_t *serv, client_t *client, char *cmd);
int user_cmd(server_t *serv, client_t *client, char *cmd);
int pass_cmd(server_t *serv, client_t *client, char *cmd);
int quit_cmd(server_t *server, client_t *client, char *cmd);
int dump_cmd(server_t *server, client_t *client, char *cmd);

int check_cmd_name(const char *name, const char *to_compare);
#endif //FTP_INCLUDES_CMD_H_
