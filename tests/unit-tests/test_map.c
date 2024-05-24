/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"

Test(init_map, test_init_map)
{
    map_t *map = initialize_map(10, 10);

    cr_assert_not_null(map);
    cr_assert_eq(map->width, 10);
    cr_assert_eq(map->height, 10);
    cr_assert_not_null(map->tiles);
}
