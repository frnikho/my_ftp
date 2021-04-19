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
#include "ftp.h"

char *get_perm(char *path, char *filename)
{

    char *np = malloc(sizeof(char) * 256);
    strcat(np, path);
    strcat(np, "/");
    strcat(np, filename);

    struct stat fs;
    stat(np, &fs);
    char *perm = malloc(sizeof(char) * 1024);
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

int list_cmd(server_t *server, client_t *client, char *cmd)
{
    char str[4096];
    struct sockaddr_in s_in;
    socklen_t size = sizeof(s_in);

    DIR *dir;
    struct dirent *_dir;
    if ((dir = opendir(client->working_directory)) == NULL) {
        send_msg(client->fd, "425");
        return (0);
    }
    send_msg(client->fd, "150");

    while ((_dir = readdir(dir)) != NULL) {
        char *perm = get_perm(client->working_directory, _dir->d_name);
        struct stat fs;
        stat(_dir->d_name, &fs);

        #ifdef DEBUG
        printf("[DEBUG] => %s %lu nico nico \t%ld avril 14 17:00 %s\n", perm, fs.st_nlink, fs.st_size, _dir->d_name);
        #endif
        dprintf(client->port_fd, "%s %lu nico nico \t%ld avril 14 17:00 %s\n", perm, fs.st_nlink, fs.st_size, _dir->d_name);
        free(perm);
    }


    close(client->port_fd);
    client->port_fd = -1;
    send_msg(client->fd, "226 Directory send.");

    return (0);
}