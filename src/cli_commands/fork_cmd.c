/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** fork_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"

void client_fork_end(client_t *cli)
{
    server_t *server = get_instance();
    map_t *map = get_map_instance();
    client_t *graphic = NULL;
    item_type_t type = EGG;
    int tile_index = cli->pos.x + cli->pos.y * map->width;
    game_t *game = get_game_instance();
    int team_index = get_team_index_by_name(game, cli->team);

    add_egg_to_team_ll(game->teams[team_index], cli->pos.x,
        cli->pos.y, cli->egg_id_laying);
    add_item_to_tiles(map->tiles[tile_index], type);
    game->teams[team_index]->max_clients++;
    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "enw #%d #%d %d %d\n", cli->egg_id_laying,
                cli->id, cli->pos.x, cli->pos.y);
        }
    }
    cli->egg_id_laying = -1;
}

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

static void notice_graphic_client_fork_spawn(int egg_id)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "ebo #%d\n", egg_id);
        }
    }
}

void spawn_player_if_waiting(server_t *server,
    waiting_client_t *waiting_client, int team_index, int egg_id)
{
    client_t *cli;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (waiting_client->socket == cli->socket) {
            player_spawn(cli, team_index);
            notice_graphic_client_fork_spawn(egg_id);
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
            spawn_player_if_waiting(server, waiting_client,
                team_index, egg->egg_id);
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
