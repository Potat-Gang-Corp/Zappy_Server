/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_login_phase
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/struct_client.h"

void player_spawn(client_t *cli, int team_index)
{
    map_t *map = get_map_instance();
    game_t *game = get_game_instance();
    egg_t *egg_head = game->teams[team_index]->egg;

    if (!map->tiles) {
        return;
    }
    add_item_to_tiles(map->tiles[egg_head->x_pos +
        egg_head->y_pos * game->width], PLAYER);
    delete_item_from_tiles(map->tiles[egg_head->x_pos +
        egg_head->y_pos * game->width], EGG);
    cli->pos.x = map->tiles[egg_head->x_pos +
        egg_head->y_pos * game->width]->x;
    cli->pos.y = map->tiles[egg_head->x_pos +
        egg_head->y_pos * game->width]->y;
    cli->pos.orientation = rand() % 4;
    game->teams[team_index]->egg = egg_head->next;
    free(egg_head);
    egg_head = NULL;
}

void notice_graphic_client(client_t *cli, char *team_name)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->graphic == true) {
            dprintf(graphic->socket, "pnw #%d %d %d %d %d %s\n", cli->socket,
                cli->pos.x, cli->pos.y, (cli->pos.orientation + 1), cli->level,
                team_name);
        }
    }
}

int handle_team_full(client_t *cli, int i, char *team_name)
{
    game_t *game = get_game_instance();
    char s[1024];
    char coordinates[1024];
    int len;

    if (game->teams[i]->max_clients < 1 && game->teams[i]->egg == NULL) {
        add_to_waiting_list(cli->socket, team_name);
        write(cli->socket, "This team is full, please wait\n",
            strlen("This team is full, please wait\n"));
    } else {
        game->teams[i]->max_clients -= 1;
        len = snprintf(s, sizeof(s), "%d\n", game->teams[i]->max_clients);
        write(cli->socket, s, len);
        len = snprintf(coordinates, sizeof(coordinates),
            "%d %d\n", game->width, game->height);
        write(cli->socket, coordinates, len);
        player_spawn(cli, i);
        notice_graphic_client(cli, team_name);
    }
    return 0;
}

static void notice_graphic_client_player_connected(client_t *cli)
{
    server_t *server = get_instance();
    client_t *players = NULL;

    for (players = server->clients; players != NULL; players = players->next) {
        if (players->graphic == false) {
            dprintf(cli->socket, "pnw #%d %d %d %d %d %s\n", players->socket,
                players->pos.x, players->pos.y,
                (players->pos.orientation + 1), players->level,
                players->team);
        }
    }
}

static void egg_on_map_localisation(egg_t *egg, client_t *cli)
{
    while (egg != NULL) {
        dprintf(cli->socket, "smg egg #%d %d %d\n", egg->egg_id,
            egg->x_pos, egg->y_pos);
            egg = egg->next;
    }
}

static void notice_graphic_client_egg_layed(client_t *cli)
{
    game_t *game = get_game_instance();
    egg_t *egg = NULL;

    for (int i = 0; i < game->nb_teams; i++) {
        egg = game->teams[i]->egg;
        egg_on_map_localisation(egg, cli);
    }
}

int detect_team_validity(char *team_name, client_t *cli)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            cli->logged = true;
            cli->team = strdup(team_name);
            return handle_team_full(cli, i, team_name);
        }
        if (strcmp(team_name, "GRAPHIC") == 0) {
            dprintf(cli->socket, "msz %d %d\n", game->width, game->height);
            cli->logged = true;
            cli->graphic = true;
            notice_graphic_client_player_connected(cli);
            notice_graphic_client_egg_layed(cli);
            return 0;
        }
    }
    return 84;
}

void handle_cli_login(client_t *cli, char *command)
{
    char *msg = "Wrong team name, please try again\n";

    if (cli->logged == false && detect_team_validity(command, cli) == 0)
        return;
    if (cli->logged == false && detect_team_validity(command, cli) == 84) {
        write(cli->socket, msg, strlen(msg));
        return;
    }
}
