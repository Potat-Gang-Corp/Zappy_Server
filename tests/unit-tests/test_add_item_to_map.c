/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_accept_cli_ll
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

Test(get_items, should_return_correct_item_names)
{
    cr_assert_str_eq(get_items(FOOD), "FOOD");
    cr_assert_str_eq(get_items(LINEMATE), "LINEMATE");
    cr_assert_str_eq(get_items(DERAUMERE), "DERAUMERE");
    cr_assert_str_eq(get_items(SIBUR), "SIBUR");
    cr_assert_str_eq(get_items(MENDIANE), "MENDIANE");
    cr_assert_str_eq(get_items(PHIRAS), "PHIRAS");
    cr_assert_str_eq(get_items(THYSTAME), "THYSTAME");
    cr_assert_str_eq(get_items(EGG), "EGG");
    cr_assert_str_eq(get_items(PLAYER), "PLAYER");
}

Test(display_item, should_print_correct_item_names)
{
    cr_redirect_stdout();
    items_t items[3];
    items[0].type = FOOD;
    items[0].next = &items[1];
    items[1].type = LINEMATE;
    items[1].next = &items[2];
    items[2].type = DERAUMERE;
    items[2].next = NULL;

    display_item(items);

    cr_assert_stdout_eq_str("Item: FOOD\nItem: LINEMATE\nItem: DERAUMERE\n");
}
