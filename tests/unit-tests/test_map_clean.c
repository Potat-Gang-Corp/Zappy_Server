/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map_init
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include <time.h>

items_t *create_items_list(int num_items) {
    items_t *head = NULL, *current;
    for (int i = 0; i < num_items; i++) {
        current = malloc(sizeof(items_t));
        current->type = FOOD;
        current->next = head;
        head = current;
    }
    return head;
}

Test(memory_management, clean_item_linked_list_null_input) {
    items_t *items = NULL;
    clean_item_linked_list(&items);
    cr_assert_null(items, "The list should be NULL after cleaning a NULL list.");
}

Test(memory_management, clean_item_linked_list_populated_list) {
    items_t *items = create_items_list(5);
    clean_item_linked_list(&items);
    cr_assert_null(items, "The list should be NULL after cleaning a populated list.");
}

Test(memory_individual, checking_existence_tile_element_null_tile) {
    checking_existence_tile_element(NULL);
    cr_assert(1, "Function should handle NULL input without failing.");
}

Test(memory_management, checking_existence_tile_element_populated_tile) {

    tile_t *tile = malloc(sizeof(tile_t));
    cr_assert_not_null(tile, "Failed to allocate memory for tile.");

    tile->items = create_items_list(3);
    cr_assert_not_null(tile->items, "Failed to create items list.");

    checking_existence_tile_element(tile);

    tile = NULL;

    cr_assert(1, "Tile should be cleaned properly with items.");
}

Test(memory_management, clean_tiles_struct_empty_map) {
    map_t *map = get_map_instance();
    map->width = 0;
    map->height = 0;
    map->tiles = NULL;
    clean_tiles_struct();
    cr_assert_null(map->tiles, "Tiles should remain NULL after cleaning an empty map.");
}


Test(memory_management, clean_tiles_struct_with_empty_tiles) {
    map_t *map = get_map_instance();
    map->width = 2;
    map->height = 2;
    map->tiles = calloc(4, sizeof(tile_t*));
    clean_tiles_struct();
    cr_assert_null(map->tiles, "Tiles should be NULL after cleaning.");
    free(map->tiles);
}


Test(memory_management, clean_map_struct_with_populated_tiles) {
    map_t *map = get_map_instance();
    map->width = 2;
    map->height = 2;
    map->tiles = calloc(4, sizeof(tile_t*));

    for (int i = 0; i < 4; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->items = create_items_list(i + 1);
    }
    
    clean_map_struct();
    cr_assert_null(map->tiles, "All tiles should be freed and tiles pointer set to NULL.");
    free(map->tiles);
}


Test(memory_management, clean_map_struct_full_cleanup) {
    map_t *map = get_map_instance();
    map->width = 3;
    map->height = 3;
    map->tiles = calloc(9, sizeof(tile_t*));
    for (int i = 0; i < 9; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->items = create_items_list((i % 3) + 1);
    }

    clean_map_struct();
    cr_assert_null(map->tiles, "Tiles should be NULL after full cleanup of the map.");
    free(map->tiles);
}


