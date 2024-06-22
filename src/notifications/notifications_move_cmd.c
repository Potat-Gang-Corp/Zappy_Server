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

void condition_to_notify_gui(int status, client_t *cli, int x, int y)
{
    if (status == 0) {
        dprintf(cli->socket, "pie %d %d ok\n", x, y);
    } else {
        dprintf(cli->socket, "pie %d %d ko\n", x, y);
    }
}

void notice_gui_end_incantation(int x, int y, int status)
{
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == true) {
            condition_to_notify_gui(status, cli_ll, x, y);
        }
    }
}
