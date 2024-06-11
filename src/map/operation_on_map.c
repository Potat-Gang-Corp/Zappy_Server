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
    items_t *prev = NULL;

    while (item != NULL) {
        if (item->type == type) {
            if (prev == NULL) {
                tile->items = item->next;
            } else {
                prev->next = item->next;
            }
            free(item);
            return;
        }
        prev = item;
        item = item->next;
    }
}
