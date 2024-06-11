/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** inventory_operations
*/

#include "server.h"

void add_item_to_inventory(client_t *cli, item_type_t type)
{
    if (type == FOOD) {
        cli->inventory.food += 1;
    }
    if (type == LINEMATE) {
        cli->inventory.linemate += 1;
    }
    if (type == DERAUMERE) {
        cli->inventory.deraumere += 1;
    }
    if (type == SIBUR) {
        cli->inventory.sibur += 1;
    }
    if (type == MENDIANE) {
        cli->inventory.mendiane += 1;
    }
    if (type == PHIRAS) {
        cli->inventory.phiras += 1;
    }
    if (type == THYSTAME) {
        cli->inventory.thystame += 1;
    }
}

int delete_item_inventory(client_t *cli, item_type_t type)
{
    if (type == FOOD && cli->inventory.food > 0) {
        cli->inventory.food -= 1;
        return 0;
    }
    if (type == LINEMATE && cli->inventory.linemate > 0) {
        cli->inventory.linemate -= 1;
        return 0;
    }
    if (type == DERAUMERE && cli->inventory.deraumere > 0) {
        cli->inventory.deraumere -= 1;
        return 0;
    }
    if (type == SIBUR && cli->inventory.sibur > 0) {
        cli->inventory.sibur -= 1;
        return 0;
    }
    if (type == MENDIANE && cli->inventory.mendiane > 0) {
        cli->inventory.mendiane -= 1;
        return 0;
    }
    if (type == PHIRAS && cli->inventory.phiras > 0) {
        cli->inventory.phiras -= 1;
        return 0;
    }
    if (type == THYSTAME && cli->inventory.thystame > 0) {
        cli->inventory.thystame -= 1;
        return 0;
    }
    return 1;
}