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


int check_cmd_name(const char *name, const char *to_compare)
{
    char *upper = malloc(sizeof(char) * (strlen(to_compare) + 1));
    int i = 0;
    for (; to_compare[i] && to_compare[i] != '\n' && to_compare[i] != ' '; i++) {
        if (islower(to_compare[i]))
            upper[i] = (char) toupper(to_compare[i]);
        else if isprint(to_compare[i])
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

int handle_commands(server_t *server, client_t *client, char *cmd)
{

    cmd_t cmds[20] = {USER_CMD, PASS_CMD, CWD_CMD, MODE_CMD, REIN_CMD, QUIT_CMD, DUMP_CMD, PASV_CMD, SYST_CMD, FEAT_CMD, PWD_CMD, TYPE_CMD, PORT_CMD, LIST_CMD,
        END_CMDS};
    long code = 0;
    for (int i = 0; cmds[i].cmd != 0; i++) {
        char *cpy = malloc(sizeof(char ) * strlen(cmd));
        if (check_cmd_name(cmds[i].name, strtok(strcpy(cpy, cmd), " ")) == 1) {
            code = cmds[i].cmd(server, client, cmd);
            break;
        }
        free(cpy);
    }
    if (code != 0) {
        char code_str[3];
        sprintf(code_str, "%ld", code);
        send_msg(client->fd, code_str);
    }
    return (0);
}