/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications
*/

#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

void notice_graphic_move_cmd(client_t *cli)
{
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == true) {
            dprintf(cli_ll->socket, "ppo #%d %d %d %d\n", cli->id,
                cli->pos.x, cli->pos.y, (cli->pos.orientation + 1));
        }
    }
}

void notice_graphic_player_ejection(client_t *cli)
{
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == true) {
            dprintf(cli_ll->socket, "pex #%d\n", cli->id);
        }
    }
}
