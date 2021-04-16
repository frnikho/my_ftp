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

char *get_perm(char *filename)
{
    struct stat fs;
    stat(filename, &fs);
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
        char *perm = get_perm(_dir->d_name);
        struct stat fs;
        stat(_dir->d_name, &fs);



        dprintf(client->port_fd, "%s 1 nico nico \t%ld avril 14 17:00 %s\n", perm, fs.st_size, _dir->d_name);
        free(perm);
    }

   /* send_msg(client->port_fd, "-rwxr-xr-x 1 nico nico   2040 avril 14 17:00 test_ftp.sh");
    send_msg(client->port_fd, "-rw-r--r-- 1 nico nico    965 avril 15 19:11 CMakeLists.txt");
    send_msg(client->port_fd, "-rwxr-xr-x 1 nico nico 125520 avril 15 23:09 myftp");*/
    close(client->port_fd);
    client->port_fd = -1;
    send_msg(client->fd, "226 Directory send.");

    return (0);
}