/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_map_init
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

Test(map_tests, initialize_map_success) {
    cr_redirect_stdout();
    int result = initialize_map(10, 10);
    cr_assert_eq(result, 0, "initialize_map should return 0 for successful initialization");

    map_t *map = get_map_instance();
    cr_assert_not_null(map->tiles, "Tiles should be allocated");
    cr_assert_eq(map->width, 10, "Map width should be set to 10");
    cr_assert_eq(map->height, 10, "Map height should be set to 10");
}
