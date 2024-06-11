/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_

    #include "server.h"

void add_item_to_inventory(client_t *cli, item_type_t type);
int delete_item_inventory(client_t *cli, item_type_t type);

#endif /* !INVENTORY_H_ */
