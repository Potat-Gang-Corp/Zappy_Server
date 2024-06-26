/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_timeout
*/

#include "../../../include/struct_server.h"
#include "../../../include/get_instance.h"
#include "../../../include/server.h"

/**
* @file handle_timeout.c
* @brief Contains the function that handles the timeout of a cli
*/

void handle_timeout_login(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *next_cli = NULL;

    while (cli != NULL) {
        next_cli = cli->next;
        cli->cycle++;
        if (cli->logged == false && cli->cycle == 120) {
            dprintf(cli->socket, "Connexion Timeout\n");
            remove_client(cli->socket, true);
            cli = next_cli;
            continue;
        }
        cli = next_cli;
    }
}
