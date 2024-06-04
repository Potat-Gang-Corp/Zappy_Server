/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_login_phase
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

int handle_team_full_status(client_t *cli, team_t *team,
    game_t *game, char *team_name)
{
    char slots[1024];
    char coordinates[1024];
    int length;

    if (team->max_clients < 1) {
        add_to_waiting_list(cli->socket, team_name);
        write(cli->socket, "This team is full, please waiting\r\n",
            strlen("This team is full, please waiting\r\n"));
        return 0;
    } else {
        team->max_clients -= 1;
        length = snprintf(slots, sizeof(slots), "%d\r\n", team->max_clients);
        write(cli->socket, slots, length);
        length = snprintf(coordinates, sizeof(coordinates),
            "%d %d\r\n", game->width, game->height);
        write(cli->socket, coordinates, length);
        return 0;
    }
}

int detect_team_validity(char *team_name, client_t *cli)
{
    game_t *game = get_game_instance();

    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(game->teams[i]->name, team_name) == 0) {
            cli->status = true;
            cli->team = strdup(team_name);
            return handle_team_full_status(cli, game->teams[i],
            game, team_name);
        }
    }
    return 84;
}

void handle_client_login(client_t *cli, char *command)
{
    if (cli->status == false && detect_team_validity(command, cli) == 0) {
        return;
    }
    if (cli->status == false && detect_team_validity(command, cli) == 84) {
        write(cli->socket, "Wrong team name, please try again\r\n",
            strlen("Wrong team name, please try again\r\n"));
        return;
    }
    if (cli->status == true && detect_client_waiting(cli->socket) == 0) {
        write(cli->socket, "Request received, you can continue to play\r\n",
            strlen("Request received, you can continue to play\r\n"));
        return;
    }
    if (cli->status == true && detect_client_waiting(cli->socket) == 84) {
        write(cli->socket, "Please waiting it's not your turn\r\n",
            strlen("Please waiting it's not your turn\r\n"));
        return;
    }
}
