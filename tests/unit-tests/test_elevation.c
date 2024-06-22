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


client_t *create_and_add_client_inc(server_t *server, int x, int y, unsigned int level, bool is_incanting) {
    client_t *new_client = malloc(sizeof(client_t));
    if (new_client == NULL) {
        cr_log_error("Failed to allocate memory for new client.");
        return NULL;
    }
    new_client->pos.x = x;
    new_client->pos.y = y;
    new_client->level = level;
    new_client->is_incanting = is_incanting;
    new_client->next = server->clients; // Insert at the head for simplicity
    server->clients = new_client;
    return new_client;
}

void setup_map_items(map_t *map, int x, int y, int insufficient_item) {
    int index = x + y * map->width;
    if (map->tiles[index] == NULL) {
        map->tiles[index] = malloc(sizeof(tile_t));
        map->tiles[index]->items = NULL; // Starting with no items
    }
    // Add an insufficient number of items
    for (int i = 0; i < insufficient_item; i++) {
        items_t *new_item = malloc(sizeof(items_t));
        new_item->type = LINEMATE; // Example item, assumed to be required for incantation
        new_item->next = map->tiles[index]->items;
        map->tiles[index]->items = new_item;
    }
}

void setup_clients_for_incantation(server_t *server, int x, int y, unsigned int level, int count) {
    for (int i = 0; i < count; i++) {
        create_and_add_client_inc(server, x, y, level, false);
    }
}

void setup_map_for_incantation(map_t *map, int x, int y) {
    if (!map->tiles) {
        map->tiles = calloc(map->width * map->height, sizeof(tile_t *));
        if (!map->tiles) {
            cr_log_error("Failed to allocate memory for map tiles.");
            return;
        }
    }
    int index = x + y * map->width;
    if (!map->tiles[index]) {
        map->tiles[index] = malloc(sizeof(tile_t));
        if (!map->tiles[index]) {
            cr_log_error("Failed to allocate memory for a tile.");
            return;
        }
        map->tiles[index]->items = NULL;
    }
    // Mock items setup here if needed
}

// Test edge cases for check_level_players
Test(server_operations, check_level_players_edge_cases) {
    server_t *server = get_instance();
    int x = 1, y = 1, level = 2, nb = 2;

    // Create fewer clients than required
    create_and_add_client_inc(server, x, y, level, false);
    cr_assert_not(check_level_players(x, y, level, nb), "check_level_players should return false for insufficient players.");

    // Create exactly the required number of players
    create_and_add_client_inc(server, x, y, level, false);
    cr_assert(check_level_players(x, y, level, nb), "check_level_players should return true for exact player count.");

    // Create more clients than required
    create_and_add_client_inc(server, x, y, level, false);
    cr_assert_not(check_level_players(x, y, level, nb), "check_level_players should return false for excess players.");

    // Cleanup
    client_t *current = server->clients;
    while (current != NULL) {
        client_t *temp = current;
        current = current->next;
        free(temp);
    }
    server->clients = NULL;
}

// Test handling different item amounts in compare_structs
Test(item_operations, compare_structs_different_item_counts) {
    elevation_requirements_t test_tab = {1, 1, 0, 0, 0, 0, 0}; // Exact requirements for level 1
    cr_assert(compare_structs(&test_tab, 1), "Should return true for exact match.");

    test_tab.linemate = 2; // More than needed
    cr_assert(compare_structs(&test_tab, 1), "Should return true if items exceed requirements.");

    test_tab.linemate = 0; // Less than needed
    cr_assert_not(compare_structs(&test_tab, 1), "Should return false if items are less than requirements.");
}

// Testing increment_item under various scenarios
Test(item_operations, increment_item_various_items) {
    elevation_requirements_t lvl_tab = {0};
    increment_item(&lvl_tab, LINEMATE);
    increment_item(&lvl_tab, PHIRAS);

    cr_assert(lvl_tab.linemate == 1 && lvl_tab.phiras == 1, "Should correctly increment items.");

    // Try incrementing a non-existent item type
    increment_item(&lvl_tab, 99); // Assuming invalid item type
    // Assuming no changes should occur with invalid type; checking for unchanged counts
    cr_assert(lvl_tab.linemate == 1 && lvl_tab.phiras == 1, "Should not increment invalid items.");
}

Test(server_operations, check_condition_incantation_multiple_clients) {
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    map_t *map = get_map_instance();
    game->width = 10;
    game->height = 10;
    map->width = game->width;
    map->height = game->height;
    map->tiles = calloc(map->width * map->height, sizeof(tile_t*));

    int x = 1, y = 1;
    setup_map_items(map, x, y, 1); // Insufficient items for incantation at any level above 1

    create_and_add_client_inc(server, x, y, 2, false); // Incorrect number of clients for level 2 incantation
    create_and_add_client_inc(server, x, y, 2, false);

    client_t *cli = server->clients; // Assuming server->clients is not NULL
    cr_assert(check_condition_incantation(cli) == 0, "Should return false due to incorrect client setup at level.");

    // Cleanup
    client_t *current = server->clients;
    while (current) {
        client_t *temp = current;
        current = current->next;
        free(temp);
    }
    server->clients = NULL;

    for (int i = 0; i < map->width * map->height; i++) {
        if (map->tiles[i]) {
            items_t *item = map->tiles[i]->items;
            while (item) {
                items_t *temp = item;
                item = item->next;
                free(temp);
            }
            free(map->tiles[i]);
        }
    }
    free(map->tiles);
}

// Test set_bool_incantation for all eligible players
Test(server_operations, set_bool_incantation_all_eligible) {
    server_t *server = get_instance();
    int x = 1, y = 1;
    unsigned int level = 2;  // Declare level as unsigned int to match the type of client_t.level
    create_and_add_client_inc(server, x, y, level, false);
    create_and_add_client_inc(server, x, y, level, false);

    set_bool_incantation(level, x, y);

    // Check if all clients at the position with the right level have is_incanting set
    for (client_t *current = server->clients; current != NULL; current = current->next) {
        if (current->pos.x == x && current->pos.y == y && current->level == level) {
            cr_assert(current->is_incanting, "All eligible clients should have is_incanting set to true.");
        }
    }

    // Cleanup
    client_t *current = server->clients;
    while (current != NULL) {
        client_t *temp = current;
        current = current->next;
        free(temp);
    }
    server->clients = NULL;
}

void cleanup_map(map_t *map) {
    if (map->tiles) {
        for (int i = 0; i < map->width * map->height; i++) {
            if (map->tiles[i]) {
                free(map->tiles[i]);  // Adjust as necessary to free any nested structures
            }
        }
        free(map->tiles);
        map->tiles = NULL;
    }
}

void cleanup_server(server_t *server) {
    while (server->clients) {
        client_t *temp = server->clients;
        server->clients = server->clients->next;
        free(temp);
    }
}
