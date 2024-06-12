/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** check_cli
*/

#include "my.h"
#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

bool is_gui(int cli_id)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_id && cli->graphic == true)
            return true;
    }
    return false;
}