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

void player_spawn(client_t *cli)
{
    srand(time(NULL));
    map_t *map = get_map_instance();
    game_t *game = get_game_instance();
    int x = rand() % game->width;
    int y = rand() % game->height;
    item_type_t type = PLAYER;
    if (!map->tiles) {
        fprintf(stderr, "Error: map->tiles is not allocated\n");
        return;
    }
    add_item_to_tiles(map->tiles[x + y * game->width], type);
    cli->pos.x = map->tiles[x + y * game->width]->x;
    cli->pos.y = map->tiles[x + y * game->width]->y;
    cli->pos.orientation = rand() % 4;
}

void notice_graphic_client(client_t *cli, char *team_name)
{
    server_t *server = get_instance();
    client_t *graphic = NULL;

    for (graphic = server->clients; graphic != NULL; graphic = graphic->next) {
        if (graphic->is_graphical == true) {
            dprintf(graphic->socket, "pnw #%d %d %d %d %d %s\n", cli->socket,
                cli->pos.x, cli->pos.y, (cli->pos.orientation + 1), cli->level,
                team_name);
        }
    }
}

int handle_team_full(client_t *cli, int team_index, char *team_name)
{
    game_t *game = get_game_instance();
    char slots[1024];
    char coordinates[1024];
    int length;

    if (game->teams[team_index]->max_clients < 1) {
        add_to_waiting_list(cli->socket, team_name);
        write(cli->socket, "This team is full, please wait\r\n",
            strlen("This team is full, please wait\r\n"));
        return 0;
    } else {
        game->teams[team_index]->max_clients -= 1;
        length = snprintf(slots, sizeof(slots), "%d\r\n", game->teams[team_index]->max_clients);
        write(cli->socket, slots, length);
        length = snprintf(coordinates, sizeof(coordinates),
            "%d %d\r\n", game->width, game->height);
        write(cli->socket, coordinates, length);
        notice_graphic_client(cli, team_name);
        player_spawn(cli);
        return 0;
    }
}

int detect_team_validity(char *team_name, client_t *cli)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            cli->status = true;
            cli->team = strdup(team_name);
            return handle_team_full(cli, i, team_name);
        }
        if (strcmp(team_name, "graphic") == 0) {
            cli->status = true;
            cli->is_graphical = true;
            return 0;
        }
    }
    return 84;
}

void handle_cli_login(client_t *cli, char *command)
{
    printf("inside handle_cli_login\n");
    char *msg = "Wrong team name, please try again\r\n";

    if (cli->status == false && detect_team_validity(command, cli) == 0)
        return;
    if (cli->status == false && detect_team_validity(command, cli) == 84) {
        write(cli->socket, msg, strlen(msg));
        return;
    }
}