/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** inventory_operations
*/

#include "server.h"

void add_item_to_inventory(client_t *cli, item_type_t type)
{
    if (type == FOOD)
        cli->inventory.food += 1;
    if (type == LINEMATE)
        cli->inventory.linemate += 1;
    if (type == DERAUMERE)
        cli->inventory.deraumere += 1;
    if (type == SIBUR)
        cli->inventory.sibur += 1;
    if (type == MENDIANE)
        cli->inventory.mendiane += 1;
    if (type == PHIRAS)
        cli->inventory.phiras += 1;
    if (type == THYSTAME)
        cli->inventory.thystame += 1;
}

int delete_item_inventory(client_t *cli, item_type_t type)
{
    unsigned int *invent_items[] = {
        &cli->inventory.food,
        &cli->inventory.linemate,
        &cli->inventory.deraumere,
        &cli->inventory.sibur,
        &cli->inventory.mendiane,
        &cli->inventory.phiras,
        &cli->inventory.thystame
    };

    if (type < 0 || type >= sizeof(invent_items) / sizeof(invent_items[0]))
        return 1;
    if (*invent_items[type] > 0) {
        (*invent_items[type])--;
        return 0;
    }
    return 1;
}
