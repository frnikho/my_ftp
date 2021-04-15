/*
** EPITECH PROJECT, 2021
** test_client.c
** File description:
** unit test
*/

#include <criterion/criterion.h>
#include <ftp.h>

Test(client, basic_usage)
{
    client_t *client = init_client(10, NULL);
    cr_expect_str_eq(client->working_directory, DEFAULT_DIR);
    cr_expect_eq(client->fd, 10);
}

Test(client, directory)
{
    client_t *client = init_client(10, "/home/helloworld");
    cr_expect_str_eq(client->working_directory, "/home/helloworld");
    cr_expect_null(client->username);
    cr_expect_null(client->password);
    cr_expect_eq(10, client->fd);
    cr_expect_eq(client->in_transfert, 0);
}