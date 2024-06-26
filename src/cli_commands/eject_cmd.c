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
#include "look.h"

/**
 * @file eject_cmd.c
 * @brief File handling the eject
*/
void delete_egg(egg_t **egg, egg_t **prev_egg, egg_t **curr_egg)
{
    map_t *map = get_map_instance();

    notice_graphic_egg_destruction((*curr_egg)->egg_id);
    delete_item_from_tiles(map->tiles[(*curr_egg)->x_pos +
        (*curr_egg)->y_pos * map->width], EGG);
    if (*prev_egg == NULL) {
        *egg = (*curr_egg)->next;
    } else {
        (*prev_egg)->next = (*curr_egg)->next;
    }
    free(*curr_egg);
    *curr_egg = (*prev_egg == NULL) ? *egg : (*prev_egg)->next;
}

void destroy_eggs(egg_t *egg, int x, int y)
{
    egg_t *tmp = egg;
    egg_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->x_pos != x || tmp->y_pos != y) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        delete_egg(&egg, &prev, &tmp);
    }
}

void move_and_restore_orientation(client_t *tmp, game_t *game,
    int new_orientation)
{
    int old_orientation = tmp->pos.orientation;

    tmp->pos.orientation = new_orientation;
    move_player(tmp, game);
    tmp->pos.orientation = old_orientation;
}

void push_players_to_tile(client_t *cli, int x, int y)
{
    server_t *server = get_instance();
    client_t *tmp = server->clients;
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    int new_index;

    while (tmp != NULL) {
        if (tmp->pos.x == x && tmp->pos.y == y &&
            tmp->socket != cli->socket &&
            tmp->graphic == false && tmp->logged == true) {
            dprintf(tmp->socket, "eject: %d\n", cli->pos.orientation);
            delete_item_from_tiles(map->tiles[tmp->pos.x +
                tmp->pos.y * game->width], PLAYER);
            move_and_restore_orientation(tmp, game, cli->pos.orientation);
            new_index = tmp->pos.x + tmp->pos.y * game->width;
            add_item_to_tiles(map->tiles[new_index], PLAYER);
            notice_graphic_player_ejection(tmp);
        }
        tmp = tmp->next;
    }
}
