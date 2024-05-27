/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_flags
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/handle_flags.h"
#include "../../include/get_instance.h"

Test(get_instance, test_get_instance) {
    char *av[] = { "./zappy_server", "-p", "1234", "-x", "100", "-y", "100", "-n", "team1", "-c", "10", "-f", "50" };

    handle_flags(13, av);

    server_t *instance1 = get_instance();
    server_t *instance2 = get_instance();

    cr_assert_not_null(instance1, "Expected get_instance() to return a non-null pointer");
    cr_assert_eq(instance1, instance2, "Expected get_instance() to return the same pointer on multiple calls");

    cr_assert_eq(instance1->port, 1234);
}

Test(get_map_instance, test_get_map_instance) {
    char *av[] = { "./zappy_server", "-p", "1234", "-x", "100", "-y", "100", "-n", "team1", "-c", "10", "-f", "50" };

    handle_flags(13, av);

    map_t *map_instance1 = get_map_instance();
    map_t *map_instance2 = get_map_instance();

    cr_assert_not_null(map_instance1, "Expected get_map_instance() to return a non-null pointer");
    cr_assert_eq(map_instance1, map_instance2, "Expected get_map_instance() to return the same pointer on multiple calls");
}

Test(get_game_instance, test_get_game_instance) {
    char *av[] = { "./zappy_server", "-p", "1234", "-x", "100", "-y", "100", "-n", "team1", "-c", "10", "-f", "10" };

    handle_flags(13, av);

    game_t *game_instance1 = get_game_instance();
    game_t *game_instance2 = get_game_instance();

    cr_assert_not_null(game_instance1, "Expected get_game_instance() to return a non-null pointer");
    cr_assert_eq(game_instance1, game_instance2, "Expected get_game_instance() to return the same pointer on multiple calls");

    cr_assert_eq(game_instance1->width, 100);
    cr_assert_eq(game_instance1->height, 100);
    cr_assert_eq(game_instance1->freq, 10);
    cr_assert_eq(game_instance1->nb_teams, 1);
}