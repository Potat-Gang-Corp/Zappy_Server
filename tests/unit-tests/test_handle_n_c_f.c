/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_n_c_f flags
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/handle_flags.h"
#include "../../include/get_instance.h"

Test(handle_n, test_handle_n_function)
{
    int fp = 0;
    int i = 7;
    game_t *game = get_game_instance();
    char *valid_array[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-c", "10"};
    char *not_teams_bis[10] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "-c", "10"};
    handle_n(12, &i, valid_array, &fp);
    cr_assert_eq(game->nb_teams, 3, "Expected 3 teams for this valid array but we have %d", game->nb_teams);
    cr_assert_str_eq(game->teams[0]->name, "the", "Expected 'the' team for this valid array but we have %s", game->teams[0]->name);
    cr_assert_str_eq(game->teams[1]->name, "potato", "Expected 'potato' team for this valid array but we have %s", game->teams[1]->name);
    cr_assert_str_eq(game->teams[2]->name, "group", "Expected 'group' team for this valid array but we have %s", game->teams[2]->name);
    for (int j = 0; j < game->nb_teams; j++) {
        free(game->teams[j]->name);
        free(game->teams[j]);
    }
    free(game->teams);
    game->nb_teams = 0;
    game->teams = NULL;
    handle_n(8, &i, not_teams_bis, &fp);
    cr_assert_eq(game->nb_teams, 0, "Expected 0 teams for this valid array but we have %d", game->nb_teams);
    for (int j = 0; j < game->nb_teams; j++) {
        free(game->teams[j]->name);
        free(game->teams[j]);
    }
    free(game->teams);
    game->nb_teams = 0;
    game->teams = NULL;
}


 Test(handle_c, test_handle_c_function) {
     int fp = 0;
     char *invalid_buffer = "abc";
     char *negative_value = "-1";
     char *valid_value = "1";
     cr_assert_eq(handle_c(invalid_buffer, &fp), 84, "Expected exit code 84 for char value : %s", invalid_buffer);
     cr_assert_eq(handle_c(negative_value, &fp), 84, "Expected exit code 84 for negative value : %s", negative_value);
     cr_assert_eq(handle_c(valid_value, &fp), 0, "Expected exit code 0 for positive value : %s", valid_value);
 }


 Test(handle_f, test_handle_f_function) {
     int fp = 0;
     char *invalid_buffer = "abc";
     char *negative_value = "-1";
     char *valid_value = "1";
     cr_assert_eq(handle_f(invalid_buffer, &fp), 84, "Expected exit code 84 for char value : %s", invalid_buffer);
     cr_assert_eq(handle_f(negative_value, &fp), 84, "Expected exit code 84 for negative value : %s", negative_value);
     cr_assert_eq(handle_f(valid_value, &fp), 0, "Expected exit code 0 for positive value : %s", valid_value);
}

Test(handle_n_c_f, test_handle_n_c_f_function) {
    char *no_valid_n_def[3] = {"./zappy_server", "-n", "-c"};
    char *no_valid_c_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "a", "-n", "the", "potato", "group", "-c", "a"};
    char *no_valid_f_def[13] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "a", "-n", "the", "potato", "group", "-f", "a"};
    char *valid_def[15] = {"./zappy_server", "-p", "8080", "-x", "10", "-y", "10", "-n", "the", "potato", "group", "-c", "10", "-f", "10"};
    
    int i = 11;
    int fp = 0;

    cr_assert_eq(handle_n_c_f(12, &i, no_valid_c_def, &fp), 84, "Expected exit code 84 because no valid definition for c parameter");

    i = 11;
    fp = 0;

    cr_assert_eq(handle_n_c_f(12, &i, no_valid_f_def, &fp), 84, "Expected exit code 84 because no valid definition for f parameter");

    i = 1;
    fp = 0;

    cr_assert_eq(handle_n_c_f(2, &i, no_valid_n_def, &fp), 84, "Expected exit code 84 because no valid definition for n parameter");

    i = 7;
    fp = 0;

    cr_assert_eq(handle_n_c_f(14, &i, valid_def, &fp), 0, "Expected exit code 0 because valid definition for n parameter");

    i = 11;
    fp = 0;

    cr_assert_eq(handle_x_y(14, &i, valid_def, &fp), 0, "Expected exit code 0 because valid definition for c parameter");

    i = 13;
    fp = 0;

    cr_assert_eq(handle_x_y(14, &i, valid_def, &fp), 0, "Expected exit code 0 because valid definition for c parameter");

}
