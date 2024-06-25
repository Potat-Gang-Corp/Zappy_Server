/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** add_item_to_map
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"
#include "server.h"
/**
* @file add_item_to_map.c
* @brief add item to map
*/

const char *get_items(item_type_t item)
{
    const char *(*functions[MAX_ITEMS + 1])() = {
            get_food,
            get_linemate,
            get_deraumere,
            get_sibur,
            get_mendiane,
            get_phiras,
            get_thystame,
            get_egg,
            get_player,
            get_unknown
    };
    const char *item_name = functions[item]();

    return item_name;
}

void add_item_to_tiles(tile_t *tile, item_type_t type)
{
    items_t *new_item = malloc(sizeof(items_t));

    if (!new_item){
        return;
    }
    new_item->type = type;
    new_item->next = tile->items;
    tile->items = new_item;
}

void place_randomly_items(map_t *map)
{
    place_food_on_map(map);
    place_linemate_on_map(map);
    place_deraumere_on_map(map);
    place_mendiane_on_map(map);
    place_sibur_on_map(map);
    place_phiras_on_map(map);
    place_thystame_on_map(map);
    place_egg_on_map(map);
}

void setting_map(void)
{
    map_t *map = get_map_instance();

    place_randomly_items(map);
}
