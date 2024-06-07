/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** init_map.c
*/

#include "my.h"
#include "struct_map.h"
/**
* @file init_map.c
* @brief Initializes the map structure
*/

void display_suite(items_t *item)
{
    while (item) {
        printf("Item: %s\n", item->type == FOOD ? "FOOD" : "RESOURCE");
        item = item->next;
    }
}

void display(struct map_s *map)
{
    items_t *item;

    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            printf("Tile at (%d, %d):\n", x, y);
            item = map->tiles[x + y * map->width]->items;
           // display_suite(item);
           display_item(item);
        }
    }
}

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

            display_item(map->tiles[x + y * width]->items);
        }
    }
    place_randomly_items(map);
}

map_t *initialize_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    map->width = width;
    map->height = height;
    map->tiles = malloc(width * height * sizeof(tile_t *));
    if (!map->tiles) {
        free(map);
        return NULL;
    }
    init_map(map, width, height);
    setting_map();
    map->display = &display;
    return map;
}
