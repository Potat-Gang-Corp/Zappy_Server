/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_getter_item
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"
#include <time.h>
#include "inventory.h"

client_t *setup_client_inventory() {
    client_t *cli = calloc(1, sizeof(client_t));
    return cli;
}

// Helper function to destroy a client object
void teardown_client(client_t *cli) {
    free(cli);
}

Test(inventory_management, add_items) {
    client_t *cli = setup_client_inventory();

    // Testing adding each item type
    add_item_to_inventory(cli, FOOD);
    cr_assert(cli->inventory.food == 1, "Food should be incremented");

    add_item_to_inventory(cli, LINEMATE);
    cr_assert(cli->inventory.linemate == 1, "Linemate should be incremented");

    add_item_to_inventory(cli, DERAUMERE);
    cr_assert(cli->inventory.deraumere == 1, "Deraumere should be incremented");

    add_item_to_inventory(cli, SIBUR);
    cr_assert(cli->inventory.sibur == 1, "Sibur should be incremented");

    add_item_to_inventory(cli, MENDIANE);
    cr_assert(cli->inventory.mendiane == 1, "Mendiane should be incremented");

    add_item_to_inventory(cli, PHIRAS);
    cr_assert(cli->inventory.phiras == 1, "Phiras should be incremented");

    add_item_to_inventory(cli, THYSTAME);
    cr_assert(cli->inventory.thystame == 1, "Thystame should be incremented");

    teardown_client(cli);
}

Test(inventory_management, delete_items) {
    client_t *cli = setup_client_inventory();
    // Set up some items in the inventory
    cli->inventory.food = 1;
    cli->inventory.linemate = 0;  // Test for no items available

    int result = delete_item_inventory(cli, FOOD);
    cr_assert(result == 0, "Deleting food should succeed");
    cr_assert(cli->inventory.food == 0, "Food count should be decremented");

    result = delete_item_inventory(cli, LINEMATE);
    cr_assert(result == 1, "Deleting linemate should fail as none are available");
    cr_assert(cli->inventory.linemate == 0, "Linemate count should not change");

    teardown_client(cli);
}

Test(inventory_management, handle_invalid_items) {
    client_t *cli = setup_client_inventory();

    // Initialize inventory to known values to check for changes
    cli->inventory.food = 1;
    cli->inventory.linemate = 1;
    cli->inventory.deraumere = 1;
    cli->inventory.sibur = 1;
    cli->inventory.mendiane = 1;
    cli->inventory.phiras = 1;
    cli->inventory.thystame = 1;

    // Call add_item_to_inventory with an invalid item type
    add_item_to_inventory(cli, MAX_ITEMS);  // Assuming MAX_ITEMS is out of valid range

    // Check that no inventory items were incremented
    cr_assert(cli->inventory.food == 1, "Food count should not change for invalid types");
    cr_assert(cli->inventory.linemate == 1, "Linemate count should not change for invalid types");
    cr_assert(cli->inventory.deraumere == 1, "Deraumere count should not change for invalid types");
    cr_assert(cli->inventory.sibur == 1, "Sibur count should not change for invalid types");
    cr_assert(cli->inventory.mendiane == 1, "Mendiane count should not change for invalid types");
    cr_assert(cli->inventory.phiras == 1, "Phiras count should not change for invalid types");
    cr_assert(cli->inventory.thystame == 1, "Thystame count should not change for invalid types");

    // Test deletion of an item with an invalid type
    int result = delete_item_inventory(cli, MAX_ITEMS);
    cr_assert(result == 1, "Should fail when trying to delete an item with invalid type");

    teardown_client(cli);
}
