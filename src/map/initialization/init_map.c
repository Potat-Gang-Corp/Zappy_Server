/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** init_map.c
*/

#include "my.h"
#include "struct_map.h"
#include "server.h"
#include "get_instance.h"
#include "map.h"
/**
* @file init_map.c
* @brief Initializes the map structure
*/

void second_init_map(map_t *map, int x, int y, int width)
{
    int i;

    if (!map->tiles[x + y * width]) {
        for (i = 0; i < x + y * width; i++)
            free(map->tiles[i]);
        free(map->tiles);
        free(map);
        return;
    }
}

void init_map(map_t *map, int width, int height)
{
    int x;
    int y;

    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            map->tiles[x + y * width] = malloc(sizeof(tile_t));
            second_init_map(map, x, y, width);
            map->tiles[x + y * width]->x = x;
            map->tiles[x + y * width]->y = y;
            map->tiles[x + y * width]->items = NULL;
        }
    }
    place_randomly_items(map);
}

int check_map(map_t *map)
{
    if (!map)
        return 84;
    if (!map->tiles)
        return 84;
    return 0;
}

int initialize_map(int width, int height)
{
    map_t *map = get_map_instance();

    if (!map)
        return 84;
    map->width = width;
    map->height = height;
    map->tiles = malloc(width * height * sizeof(tile_t *));
    if (!map->tiles) {
        free(map);
        return 84;
    }
    init_map(map, width, height);
    if (check_map(map) == 84)
        return 84;
    return 0;
}
