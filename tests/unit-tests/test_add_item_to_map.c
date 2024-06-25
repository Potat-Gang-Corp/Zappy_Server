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
#include "map.h"

Test(get_items, should_return_correct_item_names)
{
    cr_assert_str_eq(get_items(FOOD), "food");
    cr_assert_str_eq(get_items(LINEMATE), "linemate");
    cr_assert_str_eq(get_items(DERAUMERE), "deraumere");
    cr_assert_str_eq(get_items(SIBUR), "sibur");
    cr_assert_str_eq(get_items(MENDIANE), "mendiane");
    cr_assert_str_eq(get_items(PHIRAS), "phiras");
    cr_assert_str_eq(get_items(THYSTAME), "thystame");
    cr_assert_str_eq(get_items(EGG), "egg");
    cr_assert_str_eq(get_items(PLAYER), "player");
}
