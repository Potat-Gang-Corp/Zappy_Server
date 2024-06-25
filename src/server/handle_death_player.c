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
    signal(SIGPIPE, SIG_IGN);
    server_t *server = get_instance();
    client_t *cli_ll = NULL;

    for (cli_ll = server->clients; cli_ll != NULL; cli_ll = cli_ll->next) {
        if (cli_ll->graphic == true) {
            dprintf(cli_ll->socket, "pdi #%d\n", cli->id);
        }
    }
    if ((dprintf(cli->socket, "dead\n")) < 0) {
        perror("dprintf failed");
    }
}

bool update_player_status(client_t *cli)
{
    if (cli->inventory.food == 0) {
        printf("alice\n");
        notice_player_death_event(cli);
        remove_client(cli->socket, true);
        return false;
    } else {
        cli->time_to_live += 126;
        cli->inventory.food--;
        return true;
    }
}

bool handle_player_death(client_t *cli)
{
    if (cli->time_to_live > 0) {
        cli->time_to_live--;
        return true;
    } else if (cli->time_to_live == 0) {
        return update_player_status(cli);
    }
    return true;
}
