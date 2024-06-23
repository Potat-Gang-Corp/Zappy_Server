/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_getter_item
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

void setup_map_tiles(map_t *map) {
    map->tiles = calloc(map->width * map->height, sizeof(tile_t *));
    if (!map->tiles) {
        cr_log_error("Failed to allocate memory for map tiles.");
        return;
    }
    for (int i = 0; i < map->width * map->height; i++) {
        map->tiles[i] = calloc(1, sizeof(tile_t));
        if (!map->tiles[i]) {
            cr_log_error("Failed to allocate memory for a tile at index %d.", i);
        }
    }
}

void setup_map_tiles_lvl_zero(map_t *map, int width, int height) {
    map->width = width;
    map->height = height;
    map->tiles = calloc(width * height, sizeof(tile_t *));
    if (!map->tiles) {
        cr_log_error("Failed to allocate memory for map tiles.");
        return;
    }
    for (int i = 0; i < width * height; i++) {
        map->tiles[i] = calloc(1, sizeof(tile_t));
        if (!map->tiles[i]) {
            cr_log_error("Failed to allocate memory for a tile at index %d.", i);
        }
    }
}


void free_map(map_t *map) {
    if (map->tiles) {
        for (int i = 0; i < map->width * map->height; i++) {
            if (map->tiles[i]) {
                free(map->tiles[i]);
            }
        }
        free(map->tiles);
    }
}

client_t *setup_client(int x, int y, orientation_t orientation) {
    client_t *client = calloc(1, sizeof(client_t));
    if (client == NULL) {
        perror("Failed to allocate memory for client");
        return NULL;
    }
    client->pos.x = x;
    client->pos.y = y;
    client->pos.orientation = orientation;
    return client;
}

Test(orientation_tests, check_orientation_north) {
    map_t *map = get_map_instance();
    map->width = 10;
    map->height = 10;
    setup_map_tiles(map);

    client_t *client = setup_client(5, 5, NORTH);
    int x, y, st[2] = {1, 2};  // Step size for the test

    look_orientation(&x, &y, client->pos, st);
    cr_assert(x == 7, "Incorrect X coordinate for North orientation.");
    cr_assert(y == 4, "Incorrect Y coordinate for North orientation.");

    free(client);
    free_map(map);
}

Test(level_tests, lvl_zero_functionality) {
    map_t *map = get_map_instance();
    setup_map_tiles_lvl_zero(map, 5, 5);

    if (!map || !map->tiles) {
        cr_log_error("Map or tiles were not properly allocated.");
        return;
    }

    client_t *client = setup_client(2, 2, NORTH);
    if (!client) {
        cr_log_error("Failed to setup client.");
        free_map(map);
        return;
    }

    int index = client->pos.y * map->width + client->pos.x;
    if (index >= map->width * map->height || !map->tiles[index]) {
        cr_log_error("Invalid tile index or unallocated tile.");
        free(client);
        free_map(map);
        return;
    }

    items_t items = {PHIRAS, NULL};
    map->tiles[index]->items = &items;

    char *msg = calloc(1, 50);
    if (!msg) {
        cr_log_error("Failed to allocate memory for message.");
        free(client);
        free_map(map);
        return;
    }
    size_t msg_size = 50;

    int result = lvl_zero(&msg, &msg_size, client->pos);
    cr_assert_str_eq(msg, "phiras", "Should append 'phiras' to the message.");
    cr_assert_eq(result, 0, "Function should return 0 on success.");

    free(client);
    free(msg);
    free_map(map);
}

Test(item_list_tests, append_items_ll) {
    items_t items[] = {
        {LINEMATE, &items[1]}, {DERAUMERE, NULL}
    };
    char *msg = malloc(50);
    strcpy(msg, "Items:");
    size_t msg_size = 50;

    int result = cross_items_ll(items, &msg, msg_size);
    cr_assert_str_eq(msg, "Items: linemate deraumere", "The message should correctly append item names.");
    cr_assert_eq(result, 0, "Function should return 0 on success.");

    free(msg);
}

Test(append_tests, check_append_comma_not_needed) {
    char *msg = malloc(50);
    strcpy(msg, "Items");
    size_t msg_size = 50;
    int result = check_to_append(3, &msg, msg_size, 3);

    cr_assert_str_eq(msg, "Items", "No comma should be appended.");
    cr_assert_eq(result, 0, "Function should return 0 on success.");

    free(msg);
}

Test(orientation_tests, check_all_orientations) {
    map_t *map = get_map_instance();
    setup_map_tiles_lvl_zero(map, 10, 10);

    client_t *client = setup_client(5, 5, NORTH);
    int x, y, st[2] = {1, 2};

    // Test for each orientation
    orientation_t orientations[] = {NORTH, EAST, SOUTH, WEST};
    for (int i = 0; i < 4; i++) {
        client->pos.orientation = orientations[i];
        look_orientation(&x, &y, client->pos, st);
        cr_assert(x >= 0 && x < map->width && y >= 0 && y < map->height,
                  "Orientation %d gives valid coordinates: %d, %d", i, x, y);
    }

    free(client);
    free_map(map);
}

Test(level_tests, lvl_zero_with_no_items) {
    map_t *map = get_map_instance();
    setup_map_tiles_lvl_zero(map, 5, 5);

    client_t *client = setup_client(2, 2, NORTH);
    char *msg = calloc(1, 50);
    size_t msg_size = 50;

    int result = lvl_zero(&msg, &msg_size, client->pos);
    cr_assert_str_eq(msg, "", "Message should be empty for no items.");
    cr_assert_eq(result, 0, "Function should return 0 when no items are present.");

    free(client);
    free(msg);
    free_map(map);
}

Test(cmd_lvl_tests, correct_item_accumulation) {
    map_t *map = get_map_instance();
    setup_map_tiles_lvl_zero(map, 10, 10);

    client_t *client = setup_client(5, 5, NORTH);
    char *msg = calloc(1, 100);

    // Assuming item setup is done correctly in tiles
    int result = cmd_lvl(&msg, map, client->pos, 1);
    cr_assert_eq(result, 0, "Function should execute without errors.");
    cr_assert(strlen(msg) > 0, "Message should contain item descriptions from level 1 tiles.");

    free(client);
    free(msg);
    free_map(map);
}

