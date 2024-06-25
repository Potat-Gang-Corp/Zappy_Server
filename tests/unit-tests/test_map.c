/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map
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

Test(init_map, test_init_map_no_failure) {
    map_t *map = malloc(sizeof(map_t));
    map->width = 10;
    map->height = 10;
    map->tiles = malloc(map->width * map->height * sizeof(tile_t *));
    
    for (int i = 0; i < map->width * map->height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
    }

    init_map(map, map->width, map->height);
    for (int x = 0; x < map->width; x++) {
        for (int y = 0; y < map->height; y++) {
            int index = x + y * map->width;
            cr_assert_not_null(map->tiles[index], "Tile at index %d should not be NULL", index);
            cr_assert_eq(map->tiles[index]->x, x);
            cr_assert_eq(map->tiles[index]->y, y);
        }
    }
    for (int i = 0; i < map->width * map->height; i++) {
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}
