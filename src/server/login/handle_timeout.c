/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_timeout
*/

#include "../../../include/struct_server.h"
#include "../../../include/get_instance.h"
#include "../../../include/server.h"

void handle_timeout_login(void)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    client_t *cli = server->clients;
    client_t *next_cli = NULL;

    while (cli != NULL) {
        next_cli = cli->next;
        cli->cycle++;
        printf("cycle = %d\n", cli->cycle);
        if (cli->logged == false && cli->cycle == (5 * game->freq)) {
            dprintf(cli->socket, "Connexion Timeout\n");
            remove_client(cli->socket);
            cli = next_cli;
            continue;
        }
        cli = next_cli;
    }
}
