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

server_t *server_instance;
game_t *game_instance;
team_t *team1;

void setup(void) {
    server_instance = get_instance();
    game_instance = get_game_instance();

    team1 = malloc(sizeof(team_t));
    team1->name = strdup("team1");
    team1->max_clients = 5;
    team1->cpt_egg = 1;

    game_instance->nb_teams = 1;
    game_instance->teams = malloc(sizeof(team_t *));
    game_instance->teams[0] = team1;

    game_instance->width = 100;
    game_instance->height = 100;
    
    server_instance->socket = 0;
    server_instance->clients = NULL;
    TAILQ_INIT(&server_instance->waiting_list);
    FD_ZERO(&server_instance->readfs);
}

void teardown(void) {
    client_t *current = server_instance->clients;
    while (current) {
        client_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    server_instance->clients = NULL;
    while (!TAILQ_EMPTY(&server_instance->waiting_list)) {
        waiting_client_t *wclient = TAILQ_FIRST(&server_instance->waiting_list);
        TAILQ_REMOVE(&server_instance->waiting_list, wclient, entries);
        free(wclient->team);
        free(wclient);
    }
    free(team1->name);
    free(team1);
    free(game_instance->teams);
    game_instance->teams = NULL;
}

TestSuite(accept_cli, .init = setup, .fini = teardown);
/*
Test(accept_cli, test_accept_loop_add_to_waiting_list) {
    game_instance->teams[0]->cpt_egg = 0;
    int result = accept_loop(1, 0, 0);
    cr_assert_eq(result, 0, "Expected accept_loop to return 0 when adding to waiting list");

    waiting_client_t *wclient = TAILQ_FIRST(&server_instance->waiting_list);
    cr_assert_not_null(wclient, "Expected waiting client to be added");
    cr_assert_eq(wclient->socket, 1, "Expected waiting client socket to match");
    cr_assert_str_eq(wclient->team, "team1", "Expected waiting client team to match");
}

Test(accept_cli, test_accept_loop_add_to_ll) {
    game_instance->teams[0]->cpt_egg = 1;
    int result = accept_loop(1, 1, 0);
    cr_assert_eq(result, 0, "Expected accept_loop to return 0 when adding to linked list");

    client_t *client = server_instance->clients;
    cr_assert_not_null(client, "Expected client to be added to linked list");
    cr_assert_eq(client->socket, 1, "Expected client socket to match");
    cr_assert_str_eq(client->team, "team1", "Expected client team to match");
}*/

/*Test(accept_cli, test_init_ll) {
    int result = init_ll(1, 0);
    cr_assert_eq(result, 0, "Expected init_ll to return 0");
    cr_assert_not_null(server_instance->clients, "Expected server clients to be initialized");
    cr_assert_eq(server_instance->clients->socket, 1, "Expected client socket to match");
    cr_assert_str_eq(server_instance->clients->team, "team1", "Expected client team to match");
}

Test(accept_cli, test_add_to_ll_bis) {
    init_ll(1, 0);
    int new_socket = 2;
    int result = add_to_ll_bis(new_socket, 0);
    cr_assert_eq(result, 0, "Expected add_to_ll_bis to return 0");
    cr_assert_not_null(server_instance->clients->next, "Expected new client to be added to the linked list");
    cr_assert_eq(server_instance->clients->next->socket, new_socket, "Expected new client socket to match");
    cr_assert_str_eq(server_instance->clients->next->team, "team1", "Expected new client team to match");
}

Test(accept_cli, test_add_to_ll) {
    int result = add_to_ll(1, 0);
    cr_assert_eq(result, 0, "Expected add_to_ll to return 0");
    cr_assert_not_null(server_instance->clients, "Expected server clients to be initialized");

    int new_socket = 2;
    result = add_to_ll(new_socket, 0);
    cr_assert_eq(result, 0, "Expected add_to_ll to return 0 when adding second client");
    cr_assert_not_null(server_instance->clients->next, "Expected new client to be added to the linked list");
}*/

Test(accept_cli, test_add_to_waiting_list) {
    int result = add_to_waiting_list(1, "team1");
    cr_assert_eq(result, 0, "Expected add_to_waiting_list to return 0");
    cr_assert_not_null(TAILQ_FIRST(&server_instance->waiting_list), "Expected new waiting client to be added");
    cr_assert_eq(TAILQ_FIRST(&server_instance->waiting_list)->socket, 1, "Expected waiting client socket to match");
    cr_assert_str_eq(TAILQ_FIRST(&server_instance->waiting_list)->team, "team1", "Expected waiting client team to match");
}
