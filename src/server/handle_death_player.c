/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_player_death
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/struct_client.h"

void notice_player_death_event(client_t *cli)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pdi #%d\n", cli->socket);
        }
    }
}

void handle_player_death(void)
{
    client_t *cli = NULL;
    server_t *server = get_instance();

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->time_to_live == 0) {
            notice_player_death_event(cli);
            remove_client(cli->socket);
        }
    }
}
