/*
** EPITECH PROJECT, 2021
** test_server.c
** File description:
** unit test
*/

#include "ftp.h"
#include <criterion/criterion.h>

Test(server, basic_usage)
{
    server_t *server = server_init(9876, "/home/");
    cr_expect_not_null(server);
    cr_expect_eq(server->timeout.tv_sec, TIMEOUT_SEC);
    cr_expect_eq(server->timeout.tv_usec, TIMEOUT_USEC);
    cr_expect_not_null(&server->addr_in);
    cr_expect_eq(9876, htons(server->addr_in.sin_port));
    server_close(server);

}

Test(server, same_port)
{
    server_t *s1 = server_init(9877, "/home/");
    server_t *s2 = server_init(9877, "/home/");
    cr_expect_not_null(s1);
    cr_expect_null(s2);
    server_close(s1);
    server_close(s2);
}