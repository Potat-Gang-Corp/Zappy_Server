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

char *get_items(item_type_t item)
{
    switch (item) {
        case FOOD:
            return "FOOD";
        case LINEMATE:
            return "LINEMATE";
        case DERAUMERE:
            return "DERAUMERE";
        case SIBUR:
            return "SIBUR";
        case MENDIANE:
            return "MENDIANE";
        case PHIRAS:
            return "PHIRAS";
        case THYSTAME:
            return "THYSTAME";
        case EGG:
            return "EGG";
        case PLAYER:
            return "PLAYER";
        default:
            return "UNKNOWN";
    }
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
    srand(time(NULL));
    int total_tiles = map->width * map->height;
    int total_items = total_tiles * 3 / 2;

    for (int i = 0; i < total_items; i++) {
        int tile_index = rand() % total_tiles;
        item_type_t type = rand() % (PLAYER + 1);
        add_item_to_tile(map->tiles[tile_index], type);
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
