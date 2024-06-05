/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_accept_cli_ll
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

server_t *server_instance_remove_cli;
game_t *game_instance_remove_cli;
team_t *team1_remove_cli;

void setup_remove_cli(void) {
    server_instance_remove_cli = get_instance();
    game_instance_remove_cli = get_game_instance();

    team1_remove_cli = malloc(sizeof(team_t));
    team1_remove_cli->name = strdup("team1");
    team1_remove_cli->max_clients = 5;
    team1_remove_cli->cpt_egg = 1;

    game_instance_remove_cli->nb_teams = 1;
    game_instance_remove_cli->teams = malloc(sizeof(team_t *));
    game_instance_remove_cli->teams[0] = team1_remove_cli;

    game_instance_remove_cli->width = 100;
    game_instance_remove_cli->height = 100;
    
    server_instance_remove_cli->socket = 0;
    server_instance_remove_cli->clients = NULL;
    TAILQ_INIT(&server_instance_remove_cli->waiting_list);
    FD_ZERO(&server_instance_remove_cli->readfs);
}

void teardown_remove_cli(void) {
    client_t *current = server_instance_remove_cli->clients;
    while (current) {
        client_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    server_instance_remove_cli->clients = NULL;
    while (!TAILQ_EMPTY(&server_instance_remove_cli->waiting_list)) {
        waiting_client_t *wclient = TAILQ_FIRST(&server_instance_remove_cli->waiting_list);
        TAILQ_REMOVE(&server_instance_remove_cli->waiting_list, wclient, entries);
        free(wclient->team);
        free(wclient);
    }
    free(team1_remove_cli->name);
    free(team1_remove_cli);
    free(game_instance_remove_cli->teams);
    game_instance_remove_cli->teams = NULL;
}

TestSuite(remove_client, .init = setup_remove_cli, .fini = teardown_remove_cli);

/*Test(remove_client, remove_client_test)
{
    cr_assert_eq(remove_client(1), 84);
    add_to_ll(1, 0);
    add_to_ll(2, 0);
    add_to_ll(3, 0);

    cr_assert_eq(remove_client(2), 0);
    cr_assert_eq(remove_client(2), 84);
    cr_assert_eq(remove_client(1), 0);
    cr_assert_eq(remove_client(3), 0);
    cr_assert_null(server_instance_remove_cli->clients);
}*/
