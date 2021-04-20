/*
** EPITECH PROJECT, 2021
** retr.c
** File description:
** c file
*/

#include <zconf.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include "ftp.h"

static char *clean_str(char *str)
{
    char *clean = malloc(sizeof(char) * strlen(str));
    int i = 0;
    for (; str[i] != 0 && isprint(str[i]); i++) {
        clean[i] = str[i];
    }
    clean[i] = 0;
    return clean;
}

int upload_file(server_t *server, client_t *client, char *filename)
{
    char *fp = calloc(1, sizeof(char) * 256);
    strcat(fp, client->working_directory);
    strcat(fp, "/");
    strcat(fp, filename);
    int file_fd = open(fp, O_RDONLY);
    if (file_fd <= 0) {
        printf("Error while opening file !");
        free(fp);
        return (0);
    }
    int read_count = 0;
    char buff = 0;
    while ((read_count = read(file_fd, &buff, 1)) == 1) {
        dprintf(client->port_fd, "%c", buff);
    }
    free(fp);
    dprintf(client->fd, "226 finish transfert\n");
    close(client->port_fd);
    return (0);
}

int retr_cmd(server_t *server, client_t *client, char *cmd)
{
    strtok(cmd, " ");
    char *filename = strtok(NULL, " ");
    upload_file(server, client, clean_str(filename));
    return (0);
}