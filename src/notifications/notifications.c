/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications
*/

#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

void notice_player_take_object(client_t *cli, item_type_t type)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pgt %d %d\n", cli->socket, type);
        }
    }
}

void notice_player_set_object(client_t *cli, item_type_t type)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pdr %d %d\n", cli->socket, type);
        }
    }
}

void notice_graphic_egg_destruction(int egg_id)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "edi #%d\n", egg_id);
        }
    }
}

void notice_graphic_init(client_t *cli)
{
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == false) {
            dprintf(cli->socket, "pnw #%d %d %d %d %d %s\n", cli_ll->socket,
                cli_ll->pos.x, cli_ll->pos.y, (cli_ll->pos.orientation + 1),
                cli_ll->level, cli_ll->team);
        }
    }
}

void notice_graphic_client(client_t *cli, char *team_name)
{
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == true) {
            dprintf(cli_ll->socket, "pnw #%d %d %d %d %d %s\n", cli->socket,
                cli->pos.x, cli->pos.y, (cli->pos.orientation + 1), cli->level,
                team_name);
        }
    }
}
