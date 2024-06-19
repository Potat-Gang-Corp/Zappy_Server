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
    items_t *prev_item = NULL;

    while (item != NULL) {
        if (item->type != type) {
            prev_item = item;
            item = item->next;
            continue;
        }
        if (prev_item == NULL) {
            tile->items = item->next;
        } else {
            prev_item->next = item->next;
        }
        free(item);
        return;
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
