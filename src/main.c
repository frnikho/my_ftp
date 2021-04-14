/*
** EPITECH PROJECT, 2021
** main.c
** File description:
** c file
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp.h"

int show_usage(void)
{
    printf("./myftp -help\nUSAGE: ./myftp port path\n\tport is the port");
    printf("number on which the server socket listens\n\tpath is the path");
    printf(" to the home directory for the Anonymous user\n");
    return (84);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return show_usage();
    long port = strtol(argv[1], NULL, 10);
    if (port <= 0)
        return show_usage();
    if (server(port, argv[2]) == -1)
        return (84);
}