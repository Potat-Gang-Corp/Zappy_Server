/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** op_cli_ll
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

/**
* @file op_cli_ll.c
* @brief operations on the linked list of clients
*/

client_t *find_client_and_prev(int cli_socket, client_t **prev_out)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    *prev_out = NULL;
    while (cli != NULL) {
        if (cli->socket == cli_socket) {
            return cli;
        }
        *prev_out = cli;
        cli = cli->next;
    }
    return NULL;
}

int remove_found_client(client_t *prev, client_t *cli)
{
    server_t *server = get_instance();

    if (cli == NULL)
        return 0;
    if (prev == NULL) {
        server->clients = cli->next;
    } else {
        prev->next = cli->next;
    }
    close(cli->socket);
    if (cli->team != NULL) {
        free(cli->team);
    }
    free(cli);
    return 0;
}

int remove_client(int cli_socket)
{
    client_t *prev;
    client_t *cli = find_client_and_prev(cli_socket, &prev);

    if (remove_found_client(prev, cli) == 84)
        return 84;
    return 0;
}
