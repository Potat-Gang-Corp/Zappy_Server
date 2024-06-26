/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** elevation
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "elevation.h"

/**
 * @file elevation_bis.c
 * @brief File handling the incantation
*/
const elevation_requirements_t elevation_table[] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

void increment_item(elevation_requirements_t *lvl_tab, item_type_t type)
{
    int *item_pointers[] = {
        &lvl_tab->linemate,
        &lvl_tab->deraumere,
        &lvl_tab->sibur,
        &lvl_tab->mendiane,
        &lvl_tab->phiras,
        &lvl_tab->thystame
    };

    if (type >= LINEMATE && type <= THYSTAME) {
        (*item_pointers[type - LINEMATE])++;
    }
}
