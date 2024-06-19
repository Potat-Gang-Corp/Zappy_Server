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

int cmd_one(char **msg, map_t *map, position_t pos)
{
    printf("cocou\n");
    items_t *item;
    //case 0 en prendre en compte pos joueur
    item = map->tiles[pos.x + pos.y]->items;
    while (item) {
        strcat((*msg), get_items(item->type));
        item = item->next;
    }
    //case1
    int x;
    if (pos.orientation == NORTH) {
        x = pos.x - 1;
    }
        if (x < 0)
            x = map->width - 1;
        int y = pos.y - 1;
        if (y < 0)
            y = map->height - 1;
    item = map->tiles[x + y * map->width]->items;
    while (item) {
        strcat((*msg), get_items(item->type));
        item = item->next;
    }
    //case 2
    y = y + 1;
    if (y >= map->height)
        y = 0;
    item = map->tiles[x + y * map->width]->items;  
    while (item) {
        strcat((*msg), get_items(item->type));
        item = item->next;
    }
    //case 3
    y = y + 1;
    if (y >= map->height)
        y = 0;
    item = map->tiles[x + y * map->width]->items;
    while (item) {
        strcat((*msg), get_items(item->type));
        item = item->next;
    }
    printf("MSG : %s\n", (*msg));
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

