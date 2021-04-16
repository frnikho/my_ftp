/*
** EPITECH PROJECT, 2021
** list.c
** File description:
** c file
*/

#include <dirent.h>
#include <zconf.h>
#include <stdio.h>
#include "ftp.h"

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
/*    while ((_dir = readdir(dir)) != NULL) {
        _dir->d_name;
        send_msg(client->pass_fd, "");
    }*/

    printf("pass fd : %d\n", client->port_fd);

    send_msg(client->port_fd, "-rwxr-xr-x 1 nico nico   2040 avril 14 17:00 test_ftp.sh");
    send_msg(client->port_fd, "-rw-r--r-- 1 nico nico    965 avril 15 19:11 CMakeLists.txt");
    send_msg(client->port_fd, "-rwxr-xr-x 1 nico nico 125520 avril 15 23:09 myftp");
    close(client->port_fd);
    client->port_fd = -1;
    send_msg(client->fd, "226 Directory send.");

    return (0);
}