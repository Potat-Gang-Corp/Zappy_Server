/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_elevation
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include "elevation.h"
#include <time.h>
#include "map.h"

map_t *create_map(int width, int height) {
    map_t *map = malloc(sizeof(map_t));
    map->width = width;
    map->height = height;
    map->tiles = malloc(width * height * sizeof(tile_t *));
    for (int i = 0; i < width * height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->items = NULL;
    }
    return map;
}

tile_t *create_tile_with_items(int counts[]) {
    tile_t *tile = malloc(sizeof(tile_t));
    tile->items = NULL;
    items_t *last_item = NULL, *new_item;

    for (int type = 0; type < MAX_ITEMS; type++) {
        for (int i = 0; i < counts[type]; i++) {
            new_item = malloc(sizeof(items_t));
            new_item->type = type;
            new_item->next = NULL;
            if (last_item == NULL) {
                tile->items = new_item;
            } else {
                last_item->next = new_item;
            }
            last_item = new_item;
        }
    }

    return tile;
}

void free_tile_items(tile_t *tile) {
    items_t *current = tile->items, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void destroy_map(map_t *map) {
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
    free(map);
}

void count_all_items(map_t *map, int *counter_items) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        counter_items[i] = 0;  // Reset counters before recounting
    }
    for (int i = 0; i < map->width * map->height; i++) {
        for (items_t *item = map->tiles[i]->items; item; item = item->next) {
            counter_items[item->type]++;
        }
    }
}

Test(refill_items, refill_all_types_correctly) {
    int width = 10, height = 10;
    map_t *map = create_map(width, height);
    int counter_items[MAX_ITEMS] = {0};

    refill_food(map, counter_items);
    refill_linemate(map, counter_items);
    refill_deraumere(map, counter_items);
    refill_sibur(map, counter_items);
    refill_mendiane(map, counter_items);
    refill_phiras(map, counter_items);
    refill_thystame(map, counter_items);

    count_all_items(map, counter_items);

    int expected_counts[MAX_ITEMS] = {
        width * height * 0.5,
        width * height * 0.3,
        width * height * 0.15,
        width * height * 0.1,
        width * height * 0.1,
        width * height * 0.08,
        width * height * 0.05
    };

    for (int i = 0; i < MAX_ITEMS; i++) {
        double tolerance = 0.05 * expected_counts[i];
        cr_assert(counter_items[i] >= expected_counts[i] - tolerance && counter_items[i] <= expected_counts[i] + tolerance,
                  "Count for item type %d after refill should be within 5%% of expected (%d, got %d)", i, expected_counts[i], counter_items[i]);
    }

    destroy_map(map);
}


Test(map_refill, refill_mendiane_statistically) {

    int width = 10, height = 10;
    map_t *map = malloc(sizeof(map_t));
    map->width = width;
    map->height = height;
    map->tiles = malloc(width * height * sizeof(tile_t *));
    for (int i = 0; i < width * height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t));
        map->tiles[i]->items = NULL;
    }

    int counter_items[MAX_ITEMS] = {0}; 

    refill_mendiane(map, counter_items);

    int mendiane_count = 0;
    for (int i = 0; i < width * height; i++) {
        for (items_t *item = map->tiles[i]->items; item; item = item->next) {
            if (item->type == MENDIANE) mendiane_count++;
        }
    }

    int expected_count = (int)(width * height * 0.1);
    double tolerance = 0.1 * expected_count;

    cr_assert(mendiane_count >= expected_count - tolerance && mendiane_count <= expected_count + tolerance,
              "Mendiane count after refill should be close to expected (10%% of total tiles), found %d, expected around %d", mendiane_count, expected_count);

    for (int i = 0; i < width * height; i++) {
        items_t *item = map->tiles[i]->items, *next;
        while (item) {
            next = item->next;
            free(item);
            item = next;
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}

Test(tile_item_counting, correctly_counts_items_on_tile) {
    int counts[MAX_ITEMS] = {3, 2, 1, 0, 0, 1, 1};
    tile_t *tile = create_tile_with_items(counts);


    int counter_items[MAX_ITEMS] = {0};

    count_items_on_map(counter_items, tile);

    for (int i = 0; i < MAX_ITEMS; i++) {
        cr_assert(counter_items[i] == counts[i], "Failed count for item type %d: expected %d, got %d", i, counts[i], counter_items[i]);
    }

    free_tile_items(tile);
    free(tile);
}
