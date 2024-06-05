/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_send_requests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"

server_t *server;
game_t *game;
team_t *team;

void setup_sending_cli_answers(void) {
    server = get_instance();
    game = get_game_instance();

    team = malloc(sizeof(team_t));
    team->name = strdup("team");
    team->max_clients = 5;
    team->cpt_egg = 1;

    game->nb_teams = 1;
    game->teams = malloc(sizeof(team_t *));
    game->teams[0] = team;

    game->width = 100;
    game->height = 100;

    server->socket = 0;
    server->clients = NULL;
    TAILQ_INIT(&server->waiting_list);
    TAILQ_INIT(&server->commands);
    FD_ZERO(&server->readfs);

    client_t *client1 = malloc(sizeof(client_t));
    client1->socket = 1;
    client1->nb_commands = 0;
    client1->next = NULL;
    server->clients = client1;

    client_t *client2 = malloc(sizeof(client_t));
    client2->socket = 2;
    client2->nb_commands = 0;
    client2->next = NULL;
    client1->next = client2;
}

void teardown_sending_cli_answers(void) {
    client_t *current = server->clients;
    while (current) {
        client_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    server->clients = NULL;

    while (!TAILQ_EMPTY(&server->waiting_list)) {
        waiting_client_t *wclient = TAILQ_FIRST(&server->waiting_list);
        TAILQ_REMOVE(&server->waiting_list, wclient, entries);
        free(wclient->team);
        free(wclient);
    }

    while (!TAILQ_EMPTY(&server->commands)) {
        command_t *command = TAILQ_FIRST(&server->commands);
        TAILQ_REMOVE(&server->commands, command, entries);
        free(command->command);
        free(command);
    }

    free(team->name);
    free(team);
    free(game->teams);
    game->teams = NULL;
}

TestSuite(send_cli_answers, .init = setup_sending_cli_answers, .fini = teardown_sending_cli_answers);

Test(send_cli_answers, test_client_in_waiting_list)
{
    add_to_waiting_list(1, "team1");
    cr_assert_eq(detect_client_waiting(1), 84);
    cr_assert_eq(detect_client_waiting(2), 0);
}
