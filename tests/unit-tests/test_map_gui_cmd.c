/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map_gui_cmd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include "../../include/commands_gui.h"
#include <time.h>

void add_item_to_tile(tile_t *tile, item_type_t type, int count) {
    for (int i = 0; i < count; i++) {
        items_t *new_item = malloc(sizeof(items_t));
        new_item->type = type;
        new_item->next = tile->items;
        tile->items = new_item;
    }
}

void setup_map(map_t *map, int width, int height)
{
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t *) * width * height);
    for (int i = 0; i < width * height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->x = i % width;
        map->tiles[i]->y = i / width;
        map->tiles[i]->items = NULL;
    }
}

void add_item_to_list(items_t **item_start, item_type_t type) {
    items_t *new_item = malloc(sizeof(items_t));
    new_item->type = type;
    new_item->next = *item_start;
    *item_start = new_item;
}

void free_item_list(items_t *item_start) {
    items_t *current = item_start;
    while (current != NULL) {
        items_t *next = current->next;
        free(current);
        current = next;
    }
}

// Test empty list
Test(construct_message_tests, empty_list) {
    int items_counter[EGG] = {0};
    items_t *item_start = NULL;  // No items in the list

    construct_message(item_start, items_counter);
    for (int i = 0; i < EGG; i++) {
        cr_assert_eq(items_counter[i], 0, "Expected count of 0 for item type %d, got %d", i, items_counter[i]);
    }
}

// Test single item type
Test(construct_message_tests, single_item_type) {
    int items_counter[EGG] = {0};
    items_t *item_start = NULL;
    add_item_to_list(&item_start, FOOD);

    construct_message(item_start, items_counter);
    cr_assert_eq(items_counter[FOOD], 1, "Expected count of 1 for FOOD, got %d", items_counter[FOOD]);

    free_item_list(item_start);
}

// Test multiple items of one type
Test(construct_message_tests, multiple_items_same_type) {
    int items_counter[EGG] = {0};
    items_t *item_start = NULL;
    add_item_to_list(&item_start, SIBUR);
    add_item_to_list(&item_start, SIBUR);
    add_item_to_list(&item_start, SIBUR);

    construct_message(item_start, items_counter);
    cr_assert_eq(items_counter[SIBUR], 3, "Expected count of 3 for SIBUR, got %d", items_counter[SIBUR]);

    free_item_list(item_start);
}

// Test multiple items of different types
Test(construct_message_tests, multiple_different_items) {
    int items_counter[EGG] = {0};
    items_t *item_start = NULL;
    add_item_to_list(&item_start, PHIRAS);
    add_item_to_list(&item_start, MENDIANE);
    add_item_to_list(&item_start, LINEMATE);

    construct_message(item_start, items_counter);
    cr_assert_eq(items_counter[PHIRAS], 1, "Expected count of 1 for PHIRAS, got %d", items_counter[PHIRAS]);
    cr_assert_eq(items_counter[MENDIANE], 1, "Expected count of 1 for MENDIANE, got %d", items_counter[MENDIANE]);
    cr_assert_eq(items_counter[LINEMATE], 1, "Expected count of 1 for LINEMATE, got %d", items_counter[LINEMATE]);

    free_item_list(item_start);
}

// Test all item types
Test(construct_message_tests, all_item_types) {
    int items_counter[EGG] = {0};
    items_t *item_start = NULL;

    for (int type = 0; type < EGG; type++) {
        add_item_to_list(&item_start, type);
    }

    construct_message(item_start, items_counter);
    for (int type = 0; type < EGG; type++) {
        cr_assert_eq(items_counter[type], 1, "Expected count of 1 for type %d, got %d", type, items_counter[type]);
    }

    free_item_list(item_start);
}
