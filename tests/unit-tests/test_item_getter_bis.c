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

Test(item_type_tests, recognize_known_items) {
    cr_assert(get_item_type("food") == FOOD, "Should identify 'food' as FOOD");
    cr_assert(get_item_type("linemate") == LINEMATE, "Should identify 'linemate' as LINEMATE");
    cr_assert(get_item_type("deraumere") == DERAUMERE, "Should identify 'deraumere' as DERAUMERE");
    cr_assert(get_item_type("sibur") == SIBUR, "Should identify 'sibur' as SIBUR");
    cr_assert(get_item_type("mendiane") == MENDIANE, "Should identify 'mendiane' as MENDIANE");
    cr_assert(get_item_type("phiras") == PHIRAS, "Should identify 'phiras' as PHIRAS");
    cr_assert(get_item_type("thystame") == THYSTAME, "Should identify 'thystame' as THYSTAME");
}

// Test for unknown item
Test(item_type_tests, return_unknown_for_unrecognized_items) {
    cr_assert(get_item_type("unknown_item") == UNKNOWN, "Should return UNKNOWN for items that do not exist");
}
