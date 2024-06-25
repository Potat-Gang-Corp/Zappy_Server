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
#include "notifications.h"

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

int handle_team_full(client_t *cli, int i, char *team_name)
{
    game_t *game = get_game_instance();
    char s[1024];
    char coordinates[1024];
    // int len;

    if (game->teams[i]->max_clients < 1 && game->teams[i]->egg == NULL) {
        add_to_waiting_list(cli->socket, team_name);
        dprintf(cli->socket, "This team is full, please wait\n");
        remove_client(cli->socket, false);
        return 1;
    } else {
        game->teams[i]->max_clients -= 1;
        snprintf(s, sizeof(s), "%d\n", game->teams[i]->max_clients);
        dprintf(cli->socket, "%s\n", s);
        snprintf(coordinates, sizeof(coordinates),
            "%d %d\n", game->width, game->height);
        dprintf(cli->socket, "%s\n", coordinates);
        player_spawn(cli, i);
        return 0;
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
            notice_graphic_init(cli);
            print_all_teams_eggs(cli);
            cli->cd = 0;
            return 2;
        }
    }
    return 84;
}

int handle_cli_login(client_t *cli, char *command)
{
    char *msg = "Wrong team name, please try again\n";
    int ret = 0;

    ret = detect_team_validity(command, cli);
    if (ret == 2) {
        return 2;
    }
    if (ret == 1) {
        return 1;
    }
    if (cli->logged == false && ret == 84) {
        dprintf(cli->socket, "%s\n", msg);
        return 84;
    }
    cli->id = get_instance()->client_id;
    get_instance()->client_id++;
    notice_graphic_client(cli, cli->team);
    return 0;
}
