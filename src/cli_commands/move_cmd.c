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
#include "../../include/notifications.h"

int cmd_left(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);

    (void)command_type;
    cli->pos.orientation = (cli->pos.orientation + 4) % 4;
    cli->cd = 7 / get_game_instance()->freq;
    dprintf(cli->socket, "ok\n");
    notice_graphic_move_cmd(cli);
    return 0;
}

int cmd_right(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);

    (void)command_type;
    if (cli == NULL) {
        return -1;
    }
    cli->pos.orientation = (cli->pos.orientation + 1) % 4;
    cli->cd = 7 / get_game_instance()->freq;
    dprintf(cli->socket, "ok\n");
    notice_graphic_move_cmd(cli);
    return 0;
}

void move_player(client_t *cli, game_t *game)
{
    int dx = 0;
    int dy = 0;

    switch (cli->pos.orientation) {
        case NORTH:
            dy = -1;
            break;
        case SOUTH:
            dy = 1;
            break;
        case EAST:
            dx = 1;
            break;
        case WEST:
            dx = -1;
            break;
    }
    cli->pos.x = (cli->pos.x + dx + game->width) % game->width;
    cli->pos.y = (cli->pos.y + dy + game->height) % game->height;
}

int cmd_forward(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    item_type_t type = PLAYER;
    int current_index = cli->pos.x + cli->pos.y * game->width;
    int new_index;

    (void)command_type;
    delete_item_from_tiles(map->tiles[current_index], type);
    move_player(cli, game);
    new_index = cli->pos.x + cli->pos.y * game->width;
    add_item_to_tiles(map->tiles[new_index], type);
    dprintf(cli->socket, "ok\n");
    cli->cd = 7 / game->freq;
    notice_graphic_move_cmd(cli);
    return 0;
}
