/*
** EPITECH PROJECT, 2021
** list.c
** File description:
** c file
*/

#include <dirent.h>
#include <zconf.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "ftp.h"

long get_length(char *path, char *filename)
{
    char *filepath = calloc(1, sizeof(char) * 256);
    strcat(filepath, path);
    strcat(filepath, "/");
    strcat(filepath, filename);

    FILE* fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("%s: %s\n", strerror(errno), filepath);
        free(filepath);
        return (0);
    }
    fseek(fp, 0L, SEEK_END);
    long int res = ftell(fp);
    fclose(fp);
    free(filepath);
    return (res);
}

char *get_perm(char *path, char *filename)
{
    char *np = calloc(1, sizeof(char) * 256);
    strcat(np, path);
    strcat(np, "/");
    strcat(np, filename);

    struct stat fs;
    stat(np, &fs);
    char *perm = calloc(1, sizeof(char) * 1024);
    strcat(perm, (S_ISDIR(fs.st_mode)) ? "d" : "-");
    strcat(perm, fs.st_mode & S_IRUSR ? "r" : "-");
    strcat(perm, fs.st_mode & S_IWUSR ? "w" : "-");
    strcat(perm, fs.st_mode & S_IXUSR ? "x" : "-");
    strcat(perm, fs.st_mode & S_IRGRP ? "r" : "-");
    strcat(perm, fs.st_mode & S_IWGRP ? "w" : "-");
    strcat(perm, fs.st_mode & S_IXGRP ? "x" : "-");
    strcat(perm, fs.st_mode & S_IROTH ? "r" : "-");
    strcat(perm, fs.st_mode & S_IWOTH ? "w" : "-");
    strcat(perm, fs.st_mode & S_IXOTH ? "x" : "-");
    free(np);
    return (perm);
}

int display_cmd(client_t *client, struct dirent *_dir)
{
    char *perm = get_perm(client->working_directory, _dir->d_name);
    struct stat fs;
    stat(_dir->d_name, &fs);
    long len = get_length(client->working_directory, _dir->d_name);
    dprintf(client->port_fd, LIST_P, perm, len, _dir->d_name);
    free(perm);
    return (0);
}

int list_cmd(server_t *server, client_t *client, char *cmd)
{
    DIR *dir;
    struct dirent *_dir;
    if ((dir = opendir(client->working_directory)) == NULL) {
        send_msg(client->fd, "425");
        return (0);
    }
    send_msg(client->fd, "150");
    while ((_dir = readdir(dir)) != NULL) {
        if (strcmp(_dir->d_name, "..") == 0 || strcmp(_dir->d_name, ".") == 0)
            continue;
        display_cmd(client, _dir);
    }
    close(client->port_fd);
    client->port_fd = -1;
    send_msg(client->fd, "226 Directory send.");
    return (0);
}