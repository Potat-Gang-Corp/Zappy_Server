/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** place_elements_on_map
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"

void count_items_on_map(int *counter_items, tile_t *tile)
{
    items_t *item = tile->items;

    while (item) {
        counter_items[item->type]++;
        item = item->next;
    }
}

static void refill_food(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.5;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[FOOD]; i++) {
        tile_index = rand() % total_tiles;
        type = FOOD;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_linemate(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.3;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[LINEMATE]; i++) {
        tile_index = rand() % total_tiles;
        type = LINEMATE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_deraumere(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.15;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[DERAUMERE]; i++) {
        tile_index = rand() % total_tiles;
        type = DERAUMERE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_sibur(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[SIBUR]; i++) {
        tile_index = rand() % total_tiles;
        type = SIBUR;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_mendiane(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.1;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[MENDIANE]; i++) {
        tile_index = rand() % total_tiles;
        type = MENDIANE;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_phiras(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.08;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[PHIRAS]; i++) {
        tile_index = rand() % total_tiles;
        type = PHIRAS;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

static void refill_thystame(map_t *map, int *counter_items)
{
    int total_tiles = map->width * map->height;
    int total_food = map->width * map->height * 0.05;
    int tile_index = 0;
    item_type_t type;

    for (int i = 0; i < total_food - counter_items[THYSTAME]; i++) {
        tile_index = rand() % total_tiles;
        type = THYSTAME;
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void handle_renew_items_bis(map_t *map, int *counter_items)
{
    refill_food(map, counter_items);
    refill_linemate(map, counter_items);
    refill_deraumere(map, counter_items);
    refill_sibur(map, counter_items);
    refill_mendiane(map, counter_items);
    refill_phiras(map, counter_items);
    refill_thystame(map, counter_items);
}

void handle_renew_items(void)
{
    map_t *map = get_map_instance();
    game_t *game = get_game_instance();
    int *counter_items = malloc(sizeof(int) * EGG);

    game->cycle++;
    if (game->cycle < 20) {
        free(counter_items);
        return;
    }
    for (int i = 0; i < EGG; i++)
        counter_items[i] = 0;
    for (int i = 0; i < map->width; i++) {
        for (int j = 0; j < map->height; j++) {
            count_items_on_map(counter_items, map->tiles[i + j * map->width]);
        }
    }
    handle_renew_items_bis(map, counter_items);
    free(counter_items);
    game->cycle = 0;
}
