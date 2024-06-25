/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_

    #include "server.h"

/**
* @file inventory.h
* @brief File for inventory functions
*/

/**
 * @brief Function to add an item to the inventory
 * @param client_t *cli the client
 * @param item_type_t type the type of the item
 * @return nothing
 */
void add_item_to_inventory(client_t *cli, item_type_t type);

/**
 * @brief Function to delete an item from the inventory
 * @param client_t *cli the client
 * @param item_type_t type the type of the item
 * @return nothing
 */
int delete_item_inventory(client_t *cli, item_type_t type);


#endif /* !INVENTORY_H_ */
