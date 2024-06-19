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
