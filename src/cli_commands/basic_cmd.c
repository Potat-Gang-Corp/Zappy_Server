/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_game_command
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"
/**
 * @file basic_cmd.c
 * @brief File containing functions to handle basic commands
*/
int cmd_inventory(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);

    (void)command_type;
    dprintf(cli->socket, "[food %d, linemate %d, deraumere %d,"
        " sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        cli->inventory.food, cli->inventory.linemate,
        cli->inventory.deraumere, cli->inventory.sibur,
        cli->inventory.mendiane, cli->inventory.phiras,
        cli->inventory.thystame);
    cli->cd = 1;
    return 0;
}

int cmd_connect_nbr(char *command_type, int cli_socket)
{
    client_t *cli = get_client_by_socket(cli_socket);
    game_t *game = get_game_instance();

    (void)command_type;
    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, cli->team) == 0) {
            dprintf(cli->socket, "%d\n", game->teams[i]->max_clients);
            return 84;
        }
    }
    return 0;
}
