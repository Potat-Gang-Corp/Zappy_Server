/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** add_item_to_map
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"
/**
* @file add_item_to_map.c
* @brief add item to map
*/

const char *get_items(item_type_t item)
{
    const char *(*functions[MAX_ITEMS + 1])() = {
            get_food,
            get_linemate,
            get_deraumere,
            get_sibur,
            get_mendiane,
            get_phiras,
            get_thystame,
            get_egg,
            get_player,
            get_unknown
    };
    const char *item_name = functions[item]();

    return item_name;
}

void display_item(items_t *item)
{
    while (item) {
        printf("Item: %s\n", get_items(item->type));
        item = item->next;
    }
}

void add_item_to_tiles(tile_t *tile, item_type_t type)
{
    items_t *new_item = malloc(sizeof(items_t));

    if (!new_item){
        return;
    }
    new_item->type = type;
    new_item->next = tile->items;
    tile->items = new_item;
}

void place_randomly_items(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.5;
    int total_linemate = map->width * map->height * 0.3;
    int total_deraumere = map->width * map->height * 0.15;
    int total_sibur = map->width * map->height * 0.1;
    int total_mendiane = map->width * map->height * 0.1;
    int total_phiras = map->width * map->height * 0.08;
    int total_thystame = map->width * map->height * 0.05;
    int tile_index = 0;
    item_type_t type;

    srand(time(NULL));

    for (int i = 0; i < total_food; i++) {
        tile_index = rand() % total_tiles;
        type = FOOD;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_linemate; i++) {
        tile_index = rand() % total_tiles;
        type = LINEMATE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_deraumere; i++) {
        tile_index = rand() % total_tiles;
        type = DERAUMERE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_sibur; i++) {
        tile_index = rand() % total_tiles;
        type = SIBUR;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_mendiane; i++) {
        tile_index = rand() % total_tiles;
        type = MENDIANE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_phiras; i++) {
        tile_index = rand() % total_tiles;
        type = PHIRAS;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    for (int i = 0; i < total_thystame; i++) {
        tile_index = rand() % total_tiles;
        type = THYSTAME;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void setting_map(void)
{
    map_t *map = get_map_instance();

    place_randomly_items(map);
}
