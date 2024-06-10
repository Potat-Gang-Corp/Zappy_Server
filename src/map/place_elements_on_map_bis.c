/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** place_elements_on_map_bis
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"

int place_phiras_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_phiras = map->width * map->height * 0.2;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_phiras; i++) {
        tile_index = rand() % total_tiles;
        type = PHIRAS;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}

int place_thystame_on_map(map_t *map)
{
    int total_tiles = map->width * map->height;
    int total_thystame = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_thystame; i++) {
        tile_index = rand() % total_tiles;
        type = THYSTAME;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
    return 0;
}
