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

/**
 * @file fork_cmd.c
 * @brief File handling the Fork command
*/
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

static void setup_waiting_client(int socket, int team_index)
{
    char s[1024];
    char coordinates[1024];
    int len;

    len = snprintf(s, sizeof(s), "%d\n",
        get_game_instance()->teams[team_index]->max_clients);
    write(socket, s, len);
    len = snprintf(coordinates, sizeof(coordinates),
    "%d %d\n", get_game_instance()->width, get_game_instance()->height);
    write(socket, coordinates, len);
}

int spawn_player_if_waiting(waiting_client_t *waiting_client, int team_index)
{
    client_t *new_client = calloc(1, sizeof(client_t));
    int so;

    if (new_client == NULL) {
        perror("calloc");
        close(waiting_client->socket);
        return 84;
    }
    add_cli_to_ll(new_client, new_client->socket);
    new_client->socket = waiting_client->socket;
    new_client->team = strdup(waiting_client->team);
    new_client->logged = true;
    so = new_client->socket;
    printf("Added client from waiting list with socket %d\n", so);
    player_spawn(new_client, team_index);
    setup_waiting_client(so, team_index);
    return 0;
}

static void handle_spawn(int team_index, egg_t *egg, waiting_client_t *wait_c)
{
    int ret = 0;
    int id_save = egg->egg_id;

    ret = spawn_player_if_waiting(wait_c, team_index);
    if (ret == 0)
        notice_graphic_client_fork_spawn(id_save);
    else
        fprintf(stderr, "Error spawning player\n");
}

void handle_team_egg_laying(server_t *server, team_t *team, int team_index)
{
    egg_t *egg = team->egg;
    waiting_client_t *waiting_client = NULL;

    while (egg != NULL && team->max_clients > 0 &&
        !TAILQ_EMPTY(&server->waiting_list)) {
        waiting_client = get_waiting_client(server, team->name);
        team->max_clients--;
        if (waiting_client != NULL) {
            handle_spawn(team_index, egg, waiting_client);
        }
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
