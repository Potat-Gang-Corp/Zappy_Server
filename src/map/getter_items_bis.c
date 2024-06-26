/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** getter_items_bis
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/struct_client.h"
#include "map.h"

/**
* @file getter_items_bis.c
* @brief Contains the functions that return the name of an item
*/

item_type_t get_item_type(const char *item_name)
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

    for (item_type_t i = 0; i < MAX_ITEMS; i++) {
        if (strcmp(functions[i](), item_name) == 0) {
            return i;
        }
    }
    return UNKNOWN;
}
