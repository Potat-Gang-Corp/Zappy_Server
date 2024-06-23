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

void create_teams_getter(game_t *game, int nb_teams) {
    game->nb_teams = nb_teams;
    game->teams = malloc(nb_teams * sizeof(team_t *));
    for (int i = 0; i < nb_teams; i++) {
        game->teams[i] = malloc(sizeof(team_t));
        game->teams[i]->name = malloc(20 * sizeof(char));
        sprintf(game->teams[i]->name, "Team%d", i + 1);
    }
}

void cleanup_teams(game_t *game) {
    for (int i = 0; i < game->nb_teams; i++) {
        free(game->teams[i]->name);
        free(game->teams[i]);
    }
    free(game->teams);
    game->nb_teams = 0;
}

Test(game_tests, find_existing_team) {
    game_t *game = get_game_instance();
    create_teams_getter(game, 3);

    int index = get_team_index_by_name(game, "Team2");
    cr_assert(index == 1, "The index should be 1 for 'Team2'.");
}

Test(game_tests, find_non_existing_team) {
    game_t *game = get_game_instance();
    create_teams_getter(game, 3);

    int index = get_team_index_by_name(game, "NonExistentTeam");
    cr_assert(index == -1, "Should return -1 for a non-existing team name.");
}

Test(game_tests, empty_game_structure) {
    game_t *game = get_game_instance();
    create_teams_getter(game, 0);

    int index = get_team_index_by_name(game, "AnyTeam");
    cr_assert(index == -1, "Should return -1 when no teams are present.");
}