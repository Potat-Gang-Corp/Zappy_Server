/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_clean_game
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

void setup_clean_game(void) {
    game_t *game = get_game_instance();
    game->nb_teams = 2;
    game->teams = malloc(sizeof(team_t*) * game->nb_teams);

    for (int i = 0; i < game->nb_teams; i++) {
        game->teams[i] = malloc(sizeof(team_t));
        game->teams[i]->name = strdup("TeamName");
        game->teams[i]->max_clients = 5;
        game->teams[i]->cpt_egg = 1;
    }
}

Test(game_struct_clean, clean_team_struct, .init = setup_clean_game) {
    game_t *game = get_game_instance();
    clean_team_struct();
    cr_assert_null(game->teams);
}

Test(game_struct_clean, clean_game_struct, .init = setup_clean_game) {
    game_t *game = get_game_instance();
    clean_game_struct();
    cr_assert_null(game->teams);
}