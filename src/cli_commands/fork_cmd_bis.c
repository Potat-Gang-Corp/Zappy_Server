/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** fork_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
#include "../../include/map.h"
#include "../../include/inventory.h"
#include "../../include/notifications.h"

/**
 * @file fork_cmd_bis.c
 * @brief File handling the Fork command
*/
int get_team_index_by_name(game_t *game, char *team_name)
{
    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            return i;
        }
    }
    return -1;
}
