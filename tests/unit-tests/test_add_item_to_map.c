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
