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


Test(map_processing, compute_tile_stock_correctly) {
    map_t *map = setup_map_mct_cmd(10, 10);
    int x = 5, y = 5;  // Center of the map
    int message_len = 0;

    char *message = process_tile_and_get_message(map, x, y, &message_len);
    cr_assert_str_not_empty(message, "Message should not be null.");
    cr_assert_str_eq(message, "bct 5 5 1 1 0 0 0 0 0\n", "Message format should match expected output.");
    free(message);
    free_map_tiles(map);
    free(map);
}

Test(map_processing, handle_empty_tiles) {
    map_t *map = setup_map_mct_cmd(10, 10);
    int message_len = 0;

    // Testing an empty tile
    char *message = process_tile_and_get_message(map, 0, 0, &message_len);
    cr_assert_not_null(message, "Message should not be null.");
    cr_assert_str_eq(message, "bct 0 0 0 0 0 0 0 0 0\n", "Message for an empty tile should show zero counts.");
    free(message);
    free_map_tiles(map);
    free(map);
}

Test(map_processing, build_complete_message) {
    map_t *map = setup_map_mct_cmd(2, 2);
    int message_len = 0;
    char **bct_dict = build_bct_dict(map, &message_len);
    char *complete_message = build_message(bct_dict, map, message_len);

    cr_assert_str_not_empty(complete_message, "Complete message should not be null.");
    cr_assert(strlen(complete_message) > 0, "Complete message should have content.");
}
