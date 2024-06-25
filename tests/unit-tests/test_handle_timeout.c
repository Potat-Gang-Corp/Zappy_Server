/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_handle_timeout
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include <time.h>

Test(timeout_testing, handle_timeout_login)
{
    server_t *server = get_instance();
    client_t *cli = malloc(sizeof(client_t));
    cr_assert_not_null(cli, "Client allocation failed");
    cli->cycle = 120;
    cli->logged = false;
    cli->socket = 1;
    cli->next = NULL;
    server->clients = cli;
    handle_timeout_login();
    remove_client(cli->socket, true);
    cr_assert_null(server->clients, "Client was not removed after timeout");
}

Test(timeout_testing, handle_timeout_logged)
{
    server_t *server = get_instance();
    client_t *cli = malloc(sizeof(client_t));
    cr_assert_not_null(cli, "Client allocation failed");
    cli->cycle = 120;
    cli->logged = true;
    cli->socket = 1;
    cli->next = NULL;
    server->clients = cli;
    handle_timeout_login();
    remove_client(cli->socket, true);
    cr_assert_null(server->clients, "Client was not removed after timeout");
}