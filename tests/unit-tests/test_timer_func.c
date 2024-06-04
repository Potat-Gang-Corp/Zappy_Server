/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_timer_func
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"

Test(detection_execution_time, test_computing_timer_for_func)
{
    game_t *game = get_game_instance();
    game->freq = 1;
    cr_assert_eq(detect_execution_time("Forward"), 7.0);
    cr_assert_eq(detect_execution_time("Inventory"), 1.0);
    cr_assert_eq(detect_execution_time("Fork"), 42.0);
    cr_assert_eq(detect_execution_time("Incantation"), 300.0);
    cr_assert_eq(detect_execution_time("Bidulle"), 1000000.0);

    game->freq = 10;
    cr_assert_eq(detect_execution_time("Forward"), 0.7);
    cr_assert_eq(detect_execution_time("Inventory"), 0.1);
    cr_assert_eq(detect_execution_time("Fork"), 4.2);
    cr_assert_eq(detect_execution_time("Incantation"), 30.0);
    cr_assert_eq(detect_execution_time("Bidulle"), 1000000.0);
}
