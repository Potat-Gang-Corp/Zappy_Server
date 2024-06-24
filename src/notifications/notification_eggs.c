/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** notifications
*/

#include "server.h"
#include "struct_server.h"
#include "struct_client.h"
#include "struct_game.h"
#include "get_instance.h"

void print_egg_team(client_t *cli, team_t *team)
{
    egg_t *egg = team->egg;

    while (egg != NULL) {
        dprintf(cli->socket, "smg egg #%d %d %d\n", egg->egg_id,
            egg->x_pos, egg->y_pos);
        egg = egg->next;
    }
}

void print_all_teams_eggs(client_t *cli)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        print_egg_team(cli, game->teams[i]);
    }
}
