/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** add_item_to_map
*/

#include "my.h"
#include "struct_map.h"
/**
* @file add_item_to_map.c
* @brief add item to map
*/

char *get_items(item_type_e *item)
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

void add_item_to_tiles(tile_t *tile, item_type_e type)
{
    items_t *new_item = malloc(sizeof(items_t));

    if (!new_item){
        return;
    }
    new_item->type = type;
    new_item->next = tile->items;
    tile->items = new_item;
}
