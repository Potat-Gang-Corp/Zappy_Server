/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** look_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"    

void look_orientation(int *x, int *y, position_t pos, int i)
{
    map_t *map = get_map_instance();
    switch (pos.orientation) {
        case 0:
            *x = (pos.x + i + map->width) % map->width;
            *y = (pos.y - i + map->height) % map->height;
            break;
        case 1:
            *x = (pos.x + i + map->width) % map->width;
            *y = (pos.y + i + map->height) % map->height;
            break;
        case 2:
            *x = (pos.x - i + map->width) % map->width;
            *y = (pos.y + i + map->height) % map->height;
            break;
        case 3:
            *x = (pos.x - i + map->width) % map->width;
            *y = (pos.y - i + map->height) % map->height;
            break;
    }
}

int cross_items_ll(items_t *item, char **msg, size_t msg_size)
{
    while (item) {
        if (append_to_msg(msg, &msg_size, " ") == -1 && item->next != NULL) {
            return 84;
        }
        if (append_to_msg(msg, &msg_size, get_items(item->type)) == -1) {
            return 84;
        }
        item = item->next;
    }
    return 0;
}

int cmd_one(char **msg, map_t *map, position_t pos)
{
    items_t *item;
    size_t msg_size = strlen(*msg);

    append_to_msg(msg, &msg_size, ",");
    for (int i = 1; i <= 3; i++) {
        int x = pos.x;
        int y = pos.y;
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

int cmd_five(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

int cmd_six(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

int cmd_seven(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

int cmd_eight(char **msg, map_t *map, position_t pos)
{
    (void) msg;
    (void) map;
    (void) pos;
    return 0;
}

