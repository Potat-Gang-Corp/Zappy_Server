/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_cmd_to_ll
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

/*

server_t *server;
game_t *game;
team_t *team;

void setup_handle_cmd_ll(void) {
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

    // Add multiple test clients
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

void teardown_handle_cmd_ll(void) {
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

TestSuite(command_handling, .init = setup_handle_cmd_ll, .fini = teardown_handle_cmd_ll);

Test(command_handling, test_add_command_to_list) {
    int result = add_command_to_list(1, "test_command", 100000);
    cr_assert_eq(result, 0, "Expected add_command_to_list to return 0");

    command_t *command = TAILQ_FIRST(&server->commands);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 1);
    cr_assert_str_eq(command->command, "test_command");
}

Test(command_handling, test_find_socket) {
    client_t *client1 = server->clients;
    client_t *client2 = client1->next;

    int result = find_socket(1, client1, "test_command_1");
    cr_assert_eq(result, 0);
    cr_assert_eq(client1->nb_commands, 1);

    command_t *command = TAILQ_FIRST(&server->commands);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 1);
    cr_assert_str_eq(command->command, "test_command_1");

    result = find_socket(2, client2, "test_command_2");
    cr_assert_eq(result, 0);
    cr_assert_eq(client2->nb_commands, 1);

    command = TAILQ_NEXT(command, entries);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 2);
    cr_assert_str_eq(command->command, "test_command_2");
}

Test(command_handling, test_handle_cmd) {
    int result = handle_cmd(1, "test_command_1");
    cr_assert_eq(result, 0);

    client_t *client1 = server->clients;
    cr_assert_eq(client1->nb_commands, 1);

    command_t *command = TAILQ_FIRST(&server->commands);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 1);
    cr_assert_str_eq(command->command, "test_command_1");

    result = handle_cmd(2, "test_command_2");
    cr_assert_eq(result, 0);

    client_t *client2 = client1->next;
    cr_assert_eq(client2->nb_commands, 1);

    command = TAILQ_NEXT(command, entries);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 2);
    cr_assert_str_eq(command->command, "test_command_2");

    result = handle_cmd(2, "Bonus_command");
    cr_assert_eq(result, 0);

    cr_assert_eq(client2->nb_commands, 2);
    command = TAILQ_NEXT(command, entries);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 2);
    cr_assert_str_eq(command->command, "Bonus_command");
    
   result = handle_cmd(10, "test_command_3");
   cr_assert_eq(result, 84, "Expected handle_cmd to return 84 for non-existent client");
}*/
