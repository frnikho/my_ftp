/*
** EPITECH PROJECT, 2021
** commands.c
** File description:
** c file
*/

#include "ftp.h"
#include "cmd.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*char *extract_cmd(char *cmd)
{
    char *str = calloc(1, strlen(cmd));
    for (int i = 0; i < cmd[i]; i++) {
        if (cmd[i] == '\r' && cmd[i+1] != 0 && str[i+1] == '\n') {
            str[i] = 0;
            return str;
        }
        str[i] = cmd[i];
    }
    return str;
}*/

int mode_cmd(server_t *serv, int client_id, char *cmd)
{
    return (0);
}

int rein_cmd(server_t *serv, int client_id, char *cmd)
{
    return (0);
}

int cwd_cmd(server_t *serv, int client_id, char *cmd)
{
    return (0);
}

int user_cmd(server_t *serv, int client_fd, char *cmd)
{
    printf("USER CMD !\n");
    return (331);
}

int pass_cmd(server_t *serv, int client_fd, char *cmd)
{
    printf("PASS CMD!\n");
    return (230);
}

int check_cmd_name(const char *name, const char *to_compare)
{
    char *upper = malloc(sizeof(char) * (strlen(to_compare) + 1));
    int i = 0;
    for (; to_compare[i] && to_compare[i] != '\n'; i++) {
        if (islower(to_compare[i]))
            upper[i] = (char) toupper(to_compare[i]);
        else
            upper[i] = to_compare[i];
    }
    upper[i] = 0;
    if (strcmp(name, upper) == 0) {
        free(upper);
        return (1);
    }
    free(upper);
    return (0);
}

int handle_commands(server_t *server, int client_fd, char *cmd)
{
    cmd_t cmds[10] = {USER_CMD, PASS_CMD, CWD_CMD, MODE_CMD, REIN_CMD,
        END_CMDS};
    long code = 0;
    for (int i = 0; cmds[i].cmd != 0; i++) {
        if (check_cmd_name(cmds[i].name, cmd) == 1) {
            code = cmds[i].cmd(server, client_fd, cmd);
        }
    }
    if (code != 0) {
        char code_str[3];
        sprintf(code_str, "%ld", code);
        send_msg(client_fd, code_str);
    }
    return (0);
}