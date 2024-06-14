/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** action_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"

waiting_client_t *get_waiting_client(server_t *server, char *team_name)
{
    waiting_client_t *waiting_client = TAILQ_FIRST(&server->waiting_list);

    while (waiting_client != NULL &&
        strcmp(waiting_client->team, team_name) != 0) {
        waiting_client = TAILQ_NEXT(waiting_client, entries);
    }
    if (waiting_client != NULL) {
        TAILQ_REMOVE(&server->waiting_list, waiting_client, entries);
    }
    return waiting_client;
}

void spawn_player_if_waiting(server_t *server,
    waiting_client_t *waiting_client, int team_index)
{
    client_t *cli;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (waiting_client->socket == cli->socket) {
            player_spawn(cli, team_index);
            printf("Player spawned\n");
        }
    }
}

void handle_team_egg_laying(server_t *server, team_t *team, int team_index)
{
    egg_t *egg = team->egg;
    waiting_client_t *waiting_client = NULL;

    while (egg != NULL && team->max_clients > 0 &&
        !TAILQ_EMPTY(&server->waiting_list)) {
        waiting_client = get_waiting_client(server, team->name);
        if (waiting_client != NULL) {
            spawn_player_if_waiting(server, waiting_client, team_index);
        }
        team->max_clients--;
        egg = egg->next;
    }
}

void handle_egg_laying(void)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    team_t *team = NULL;

    for (int i = 0; i < game->nb_teams; i++) {
        team = game->teams[i];
        if (team->egg != NULL) {
            handle_team_egg_laying(server, team, i);
        }
    }
}
