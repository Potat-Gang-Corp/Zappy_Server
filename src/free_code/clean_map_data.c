/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** clean_map_data
*/

#include "../../include/my.h"
#include "../../include/struct_game.h"
#include "../../include/server.h"
#include "../../include/get_instance.h"

void clean_item_linked_list(items_t **items)
{
    items_t *current_node;

    while (*items != NULL) {
        current_node = *items;
        *items = (*items)->next;
        free(current_node);
    }
}

void checking_existence_tile_element(tile_t *tile)
{
    if (tile != NULL) {
        clean_item_linked_list(&tile->items);
        free(tile);
    }
}

void clean_tiles_struct_bis(void)
{
    map_t *map = get_map_instance();
    tile_t *tile;

    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            tile = map->tiles[i * map->width + j];
            checking_existence_tile_element(tile);
        }
    }
}

void clean_tiles_struct(void)
{
    map_t *map = get_map_instance();

    if (map != NULL && map->tiles != NULL) {
        clean_tiles_struct_bis();
        free(map->tiles);
        map->tiles = NULL;
    }
}

void clean_map_struct(void)
{
    map_t *map = get_map_instance();

    if (map != NULL && map->tiles != NULL) {
        clean_tiles_struct();
    }
}
