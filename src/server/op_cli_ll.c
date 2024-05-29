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

int remove_client(int cli_socket)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *prev = NULL;

    while (cli != NULL) {
        if (cli->socket == cli_socket) {
            if (prev == NULL) {
                server->clients = cli->next;
            } else {
                prev->next = cli->next;
            }
            free(cli);
            return 0;
        }
        prev = cli;
        cli = cli->next;
    }
    return 84;
}
