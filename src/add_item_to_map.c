/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** add_item_to_map
*/

#include "my.h"
#include "struct_map.h"
#include "get_instance.h"

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

void display_item(items_t *item)
{
    while (item) {
        printf("Item: %s\n", get_items(item->type));
        item = item->next;
    }
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
    int total_tiles = map->width * map->height;
    int total_items = total_tiles * 3 / 2;
    int tile_index = 0;
    item_type_t type;

    srand(time(NULL));
    for (int i = 0; i < total_items; i++) {
        tile_index = rand() % total_tiles;
        type = rand() % (PLAYER + 1);
        add_item_to_tiles(map->tiles[tile_index], type);
    }
}

void setting_map(void)
{
    map_t *map = get_map_instance();

    place_randomly_items(map);
}


//il faut creer une autre function pour display les items randomly sur la map

//the function should place randomly the item to the map
// tu pourrais essayer de tester ce qu 'il s'affiche ?
// test l'affichage dans le main stp
