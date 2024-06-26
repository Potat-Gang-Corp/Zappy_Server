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
    new_client->next = server->clients;
    server->clients = new_client;
    return new_client;
}

void setup_map_items(map_t *map, int x, int y, int insufficient_item) {
    int index = x + y * map->width;
    if (map->tiles[index] == NULL) {
        map->tiles[index] = malloc(sizeof(tile_t));
        map->tiles[index]->items = NULL;
    }
    for (int i = 0; i < insufficient_item; i++) {
        items_t *new_item = malloc(sizeof(items_t));
        new_item->type = LINEMATE;
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
}

Test(item_operations, compare_structs_different_item_counts) {
    elevation_requirements_t test_tab = {1, 1, 0, 0, 0, 0, 0};
    cr_assert(compare_structs(&test_tab, 1), "Should return true for exact match.");

    test_tab.linemate = 2;
    cr_assert(compare_structs(&test_tab, 1), "Should return true if items exceed requirements.");

    test_tab.linemate = 0;
    cr_assert_not(compare_structs(&test_tab, 1), "Should return false if items are less than requirements.");
}

Test(item_operations, increment_item_various_items) {
    elevation_requirements_t lvl_tab = {0};
    increment_item(&lvl_tab, LINEMATE);
    increment_item(&lvl_tab, PHIRAS);

    cr_assert(lvl_tab.linemate == 1 && lvl_tab.phiras == 1, "Should correctly increment items.");

    increment_item(&lvl_tab, 99);
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
    setup_map_items(map, x, y, 1);

    create_and_add_client_inc(server, x, y, 2, false);
    create_and_add_client_inc(server, x, y, 2, false);

    client_t *cli = server->clients;
    cr_assert(check_condition_incantation(cli, 0) == 0, "Should return false due to incorrect client setup at level.");

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

Test(server_operations, set_bool_incantation_all_eligible) {
    server_t *server = get_instance();
    int x = 1, y = 1;
    unsigned int level = 2;
    create_and_add_client_inc(server, x, y, level, false);
    create_and_add_client_inc(server, x, y, level, false);

    set_bool_incantation(level, x, y);

    for (client_t *current = server->clients; current != NULL; current = current->next) {
        if (current->pos.x == x && current->pos.y == y && current->level == level) {
            cr_assert(current->is_incanting, "All eligible clients should have is_incanting set to true.");
        }
    }

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
                free(map->tiles[i]);
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
