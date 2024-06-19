/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** look_zero_to_four
*/

#include "../../include/my.h"
#include "server.h"
#include "get_instance.h"
#include "../../include/struct_server.h"
#include "../../include/map.h"
#include "struct_client.h"

int lvl_zero(char **msg, size_t *msg_size, position_t pos)
{
    items_t *item;
    map_t *map = get_map_instance();

    item = map->tiles[pos.y * map->width + pos.x]->items;
    while (item) {
        if (append_to_msg(msg, msg_size, get_items(item->type)) == -1) {
            return -1;
        }
        if (item->next != NULL)
            append_to_msg(msg, msg_size, " ");
        item = item->next;
    }
    return 0;
}

int cmd_one(char **msg, map_t *map, position_t pos)
{
    items_t *item;
    size_t msg_size = strlen(*msg);
    int i;
    int x;
    int y;

    append_to_msg(msg, &msg_size, ",");
    for (i = 1; i <= 3; i++) {
        x = pos.x;
        y = pos.y;
        look_orientation(&x, &y, pos, i);
        item = map->tiles[y * map->width + x]->items;
        cross_items_ll(item, msg, msg_size);
        if (i != 3)
            append_to_msg(msg, &msg_size, ",");
    }
    return 0;
}

int cmd_two(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

int cmd_three(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

int cmd_four(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}
