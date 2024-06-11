/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** move_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"

int cmd_left(char *command_type, int cli_socket)
{
    printf("Executing Left command\n");
    (void)command_type;
    client_t *cli = get_client_by_socket(cli_socket);
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\r\n");
    return 0;
}

int cmd_right(char *command_type, int cli_socket)
{
    printf("Executing Right command\n");
    (void)command_type;
    client_t *cli = get_client_by_socket(cli_socket);
    if (cli->pos.orientation == NORTH) {
        cli->pos.orientation = EAST;
    }
    if (cli->pos.orientation == EAST) {
        cli->pos.orientation = SOUTH;
    }
    if (cli->pos.orientation == SOUTH) {
        cli->pos.orientation = WEST;
    }
    if (cli->pos.orientation == WEST) {
        cli->pos.orientation = NORTH;
    }
    dprintf(cli->socket, "ok\n");
    return 0;
}

void move_player(client_t *cli, game_t *game)
{
    int dx = 0, dy = 0;

    switch (cli->pos.orientation) {
        case NORTH: dy = -1; break;
        case SOUTH: dy = 1; break;
        case EAST:  dx = 1; break;
        case WEST:  dx = -1; break;
    }
    cli->pos.x = (cli->pos.x + dx + game->width) % game->width;
    cli->pos.y = (cli->pos.y + dy + game->height) % game->height;
}

int cmd_forward(char *command_type, int cli_socket)
{
    printf("Executing Forward command\n");
    (void)command_type;
    client_t *cli = get_client_by_socket(cli_socket);
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    item_type_t type = PLAYER;
    int current_index = cli->pos.x + cli->pos.y * game->width;
    int new_index = cli->pos.x + cli->pos.y * game->width;

    delete_item_from_tiles(map->tiles[current_index], type);
    move_player(cli, game);
    add_item_to_tiles(map->tiles[new_index], type);
    dprintf(cli->socket, "ok\n");
    return 0;
}