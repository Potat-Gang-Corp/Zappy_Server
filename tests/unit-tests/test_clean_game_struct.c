/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_game_struct_clean
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

egg_t *create_eggs(int count) {
    egg_t *head = NULL, *current;
    for (int i = 0; i < count; i++) {
        current = malloc(sizeof(egg_t));
        current->next = head;
        head = current;
    }
    return head;
}

team_t *create_team(const char *name, int num_eggs) {
    team_t *team = malloc(sizeof(team_t));
    team->name = strdup(name);
    team->egg = create_eggs(num_eggs);
    return team;
}

void setup_game_with_teams_and_eggs(game_t *game, int num_teams, int eggs_per_team) {
    game->teams = malloc(num_teams * sizeof(team_t *));
    for (int i = 0; i < num_teams; i++) {
        char team_name[30];
        sprintf(team_name, "Team%d", i + 1);
        game->teams[i] = create_team(team_name, eggs_per_team);
    }
    game->nb_teams = num_teams;
}

void check_all_freed(game_t *game) {
    cr_assert_null(game->teams, "Teams pointer should be NULL after cleanup.");
}


void manual_cleanup(game_t *game) {
    for (int i = 0; i < game->nb_teams; i++) {
        if (game->teams[i]) {
            free(game->teams[i]->name);
            egg_t *current = game->teams[i]->egg;
            while (current) {
                egg_t *next = current->next;
                free(current);
                current = next;
            }
            free(game->teams[i]);
        }
    }
    free(game->teams);
}

Test(clean_functions, clean_team_with_eggs) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 1, 5);

    clean_team_struct();
    check_all_freed(game);
}

Test(clean_functions, clean_team_no_eggs) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 1, 0);

    clean_team_struct();
    check_all_freed(game);
}

Test(clean_functions, clean_multiple_teams) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 3, 3);

    clean_team_struct();
    check_all_freed(game);
}

Test(clean_functions, clean_empty_game) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 0, 0);

    clean_team_struct();
    check_all_freed(game);
}

Test(clean_functions, clean_game_with_teams) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 3, 2);

    clean_game_struct();
    cr_assert_null(game->teams, "Teams should be NULL after cleaning the game structure.");

}

Test(clean_functions, clean_game_no_teams) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 0, 0);

    clean_game_struct();
    cr_assert_null(game->teams, "Teams should still be NULL when there were no teams to begin with.");
}

Test(clean_functions, clean_game_idempotent) {
    game_t *game = get_game_instance();
    setup_game_with_teams_and_eggs(game, 2, 1);

    clean_game_struct();
    cr_assert_null(game->teams, "Teams should be NULL after first clean.");

    clean_game_struct();
    cr_assert_null(game->teams, "Teams should remain NULL after second clean, ensuring idempotence.");
}

