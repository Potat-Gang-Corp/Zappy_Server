/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications_egg
*/

#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

void notice_graphic_client_fork_spawn(int egg_id)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "ebo #%d\n", egg_id);
        }
    }
}
