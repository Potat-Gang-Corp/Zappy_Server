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

void look_orientation(int *x, int *y, position_t pos, int *st)
{
    map_t *map = get_map_instance();

    switch (pos.orientation) {
        case 0:
            *x = (pos.x + st[1] + map->width) % map->width;
            *y = (pos.y - st[0] + map->height) % map->height;
            break;
        case 1:
            *x = (pos.x + st[0] + map->width) % map->width;
            *y = (pos.y + st[1] + map->height) % map->height;
            break;
        case 2:
            *x = (pos.x - st[1] + map->width) % map->width;
            *y = (pos.y + st[0] + map->height) % map->height;
            break;
        case 3:
            *x = (pos.x - st[0] + map->width) % map->width;
            *y = (pos.y - st[1] + map->height) % map->height;
            break;
    }
}

int cross_items_ll(items_t *item, char **msg, size_t msg_size)
{
    while (item) {
        if (append_to_msg(msg, &msg_size, " ") == -1) {
            return 84;
        }
        if (append_to_msg(msg, &msg_size, get_items(item->type)) == -1) {
            return 84;
        }
        item = item->next;
    }
    return 0;
}

int check_to_append(int offset, char **msg, size_t msg_size)
{
    if (offset < 1) {
        append_to_msg(msg, &msg_size, ",");
    }
    return 0;
}
