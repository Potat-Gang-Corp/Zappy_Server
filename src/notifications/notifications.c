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
