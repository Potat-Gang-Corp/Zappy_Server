/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** operation_on_map
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

void delete_item_from_tiles(tile_t *tile, item_type_t type)
{
    items_t *item = tile->items;
    items_t **link = &tile->items;

    while (item != NULL) {
        if (item->type == type) {
            *link = item->next;
            free(item);
            return;
        }
        link = &item->next;
        item = item->next;
    }
}

int checking_item_existence(items_t *item, item_type_t type)
{
    printf("type = %d\n", type);
    while (item) {
        if (item->type == type) {
            return 0;
        }
        item = item->next;
    }
    return 1;
}
