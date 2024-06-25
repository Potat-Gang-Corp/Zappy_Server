/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** place_elements_on_map
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"
#include "map.h"

void count_items_on_map(int *counter_items, tile_t *tile)
{
    items_t *item = tile->items;

    while (item) {
        counter_items[item->type]++;
        item = item->next;
    }
}

void refill_food(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.5;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[FOOD]; i++) {
        tile_index = rand() % total_tiles;
        type = FOOD;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void refill_linemate(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.3;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[LINEMATE]; i++) {
        tile_index = rand() % total_tiles;
        type = LINEMATE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void refill_deraumere(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.15;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[DERAUMERE]; i++) {
        tile_index = rand() % total_tiles;
        type = DERAUMERE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void refill_sibur(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[SIBUR]; i++) {
        tile_index = rand() % total_tiles;
        type = SIBUR;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}
