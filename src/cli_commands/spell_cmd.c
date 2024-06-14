/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** spell_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"

int cmd_broadcast(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    return 0;
}

int cmd_fork(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    map_t *map = get_map_instance();
    game_t *game = get_game_instance();
    item_type_t type = EGG;
    int tile_index = cli->pos.x + cli->pos.y * map->width;

    (void)command_type;
    for (int j = 0; j < game->player_slots; j++) {
        if (strcmp(game->teams[j]->name, cli->team) == 0) {
            add_item_to_tiles(map->tiles[tile_index], type);
            add_egg_to_team_ll(game->teams[j], cli->pos.x, cli->pos.y);
            game->teams[j]->max_clients++;
        }
    }
    cli->cd = 42 / game->freq;
    dprintf(cli_socket, "ok\n");
    return 0;
}

int cmd_incantation(char *command_type, int cli_socket)
{
    (void)command_type;
    (void)cli_socket;
    return 0;
}
