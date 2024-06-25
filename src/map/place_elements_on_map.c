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

int place_food_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.5;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food; i++) {
        tile_index = rand() % total_tiles;
        type = FOOD;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_linemate_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_linemate = map->width * map->height * 0.3;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_linemate; i++) {
        tile_index = rand() % total_tiles;
        type = LINEMATE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_deraumere_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_deraumere = map->width * map->height * 0.15;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_deraumere; i++) {
        tile_index = rand() % total_tiles;
        type = DERAUMERE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_sibur_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_sibur = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_sibur; i++) {
        tile_index = rand() % total_tiles;
        type = SIBUR;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_mendiane_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_mendiane = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_mendiane; i++) {
        tile_index = rand() % total_tiles;
        type = MENDIANE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}
