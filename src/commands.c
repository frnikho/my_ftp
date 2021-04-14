/*
** EPITECH PROJECT, 2021
** commands.c
** File description:
** c file
*/

#include <ftp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *extract_cmd(char *cmd)
{
    char *str = calloc(1, strlen(cmd));
    for (int i = 0; i < cmd[i]; i++) {
        if (cmd[i] == '\r' && cmd[i+1] != 0 && str[i+1] == '\n') {
            str[i] = 0;
            return str;
        }
        str[i] = cmd[i];
    }
    str[strlen(cmd)+1] = 0;
    return str;
}

int user_cmd(server_t *serv, int client_fd)
{
    printf("USER CMD !\n");
    return (331);
}

int pass_cmd(server_t *serv, int client_fd)
{
    printf("PASS CMD!\n");
    return (230);
}

int handle_commands(server_t *server, int client_fd, char *old_cmd)
{
    cmd_t cmds[10] = {{"USER", user_cmd}, {"PASS", pass_cmd}, {0, 0}};
    char *ptr = strtok(extract_cmd(old_cmd), " ");
    long code = 0;

    for (int i = 0; cmds[i].cmd != 0; i++) {
        if (strcmp(cmds[i].name, ptr) == 0) {
            code = cmds[i].cmd(server, client_fd);
        }
    }

    if (code != 0) {
        char code_str[3];
        sprintf(code_str, "%ld", code);
        send_msg(client_fd, code_str);
    }
    return (0);
}