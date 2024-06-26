/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_mct_constructor
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdlib.h>
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include "../../include/struct_map.h"
#include "../../include/get_instance.h"
#include "map.h"
#include "commands_gui.h"

void setup_tiles_with_items(map_t *map) {
    map->tiles = malloc(sizeof(tile_t *) * map->width * map->height);
    for (int i = 0; i < map->width * map->height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->items = NULL; // Initially no items
        // Example setup: Add items to a specific tile
        if (i == (map->width / 2 + map->height / 2 * map->width)) { // Center tile
            items_t *new_item = malloc(sizeof(items_t));
            new_item->type = FOOD;
            new_item->next = malloc(sizeof(items_t));
            new_item->next->type = LINEMATE;
            new_item->next->next = NULL;
            map->tiles[i]->items = new_item;
        }
    }
}

void free_map_tiles(map_t *map) {
    for (int i = 0; i < map->width * map->height; i++) {
        items_t *item = map->tiles[i]->items;
        while (item) {
            items_t *next = item->next;
            free(item);
            item = next;
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
}

map_t *setup_map_mct_cmd(int width, int height) {
    map_t *map = malloc(sizeof(map_t));
    map->width = width;
    map->height = height;
    setup_tiles_with_items(map);
    return map;
}

