/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_end_game
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/struct_client.h"

void notice_client_end_game(char *team_name)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->graphic == true)
            dprintf(cli->socket, "seg %s\n", team_name);
        else
            dprintf(cli->socket, "end\n");
    }
}

static void get_count_players(int *count_players, game_t *game, client_t *cli)
{
    for (int i = 0; i < game->nb_teams; i++) {
        if (strcmp(cli->team, game->teams[i]->name) == 0 && cli->level == 8)
            count_players[i]++;
    }
}

void handle_end_game(void)
{
    server_t *server = get_instance();
    game_t *game = get_game_instance();
    client_t *cli = NULL;
    int count_players[game->nb_teams];

    for (int i = 0; i < game->nb_teams; i++)
        count_players[i] = 0;
    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->team != NULL) {
            get_count_players(count_players, game, cli);
        }
    }
    for (int i = 0; i < game->nb_teams; i++) {
        if (count_players[i] == 6) {
            notice_client_end_game(game->teams[i]->name);
            handle_sigint(0);
        }
    }
}
