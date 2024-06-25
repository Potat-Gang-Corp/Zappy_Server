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
#include "map.h"

void refill_mendiane(map_t *map, int *counter_items)
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

void refill_phiras(map_t *map, int *counter_items)
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

void refill_thystame(map_t *map, int *counter_items)
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
    int *counter_items = malloc(sizeof(int) * MAX_ITEMS);

    game->cycle++;
    if (game->cycle < 20) {
        free(counter_items);
        return;
    }
    for (int i = 0; i < MAX_ITEMS; i++)
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
