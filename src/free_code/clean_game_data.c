/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** clean_game_data
*/

#include "../../include/my.h"
#include "../../include/struct_game.h"
#include "../../include/server.h"
#include "../../include/get_instance.h"

/**
 * @file clean_game_data.c
 * @brief File handling cleaning the game's data
*/
void free_team_eggs(team_t *team)
{
    egg_t *current = team->egg;
    egg_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    team->egg = NULL;
}

void clean_team_struct(void)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (game->teams[i]->name != NULL) {
            free(game->teams[i]->name);
            game->teams[i]->name = NULL;
        }
        if (game->teams[i]->egg) {
            free_team_eggs(game->teams[i]);
        }
        if (game->teams[i] != NULL) {
            free(game->teams[i]);
            game->teams[i] = NULL;
        }
    }
    if (game->teams != NULL) {
        free(game->teams);
        game->teams = NULL;
    }
}

void clean_game_struct(void)
{
    game_t *game = get_game_instance();

    if (game->teams != NULL) {
        clean_team_struct();
    }
}
