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

void clean_team_struct(void)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (game->teams[i]->name != NULL) {
            free(game->teams[i]->name);
        }
        if (game->teams[i] != NULL) {
            free(game->teams[i]);
        }
    }
    if (game->teams != NULL) {
        free(game->teams);
    }
}

void clean_game_struct(void)
{
    game_t *game = get_game_instance();

    if (game->teams != NULL) {
        clean_team_struct();
    }
}
