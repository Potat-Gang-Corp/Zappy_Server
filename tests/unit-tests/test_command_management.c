/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_command_management
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

void setup_init() {
    server_t *server = get_instance();
    client_t *cli = malloc(sizeof(client_t));
    cli->socket = 1;
    cli->nb_commands = 0;
    server->clients = cli;
}

void teardown_init() {
    server_t *server = get_instance();
    free(server->clients);
    server->clients = NULL;
    command_t *cmd;
    while (!TAILQ_EMPTY(&server->commands)) {
        cmd = TAILQ_FIRST(&server->commands);
        TAILQ_REMOVE(&server->commands, cmd, entries);
        free(cmd->command);
        free(cmd);
    }
}

Test(max_cmd_cli_tests, normal_test)
{
    server_t *server = get_instance();
    client_t *cli = malloc(sizeof(client_t));
    cli->socket = 1;
    cli->nb_commands = 0;
    server->clients = cli;
    int result = max_cmd_cli(1);
    cr_assert_eq(result, 0);
    cr_assert_eq(cli->nb_commands, 1);
    cli->nb_commands = 10;
    result = max_cmd_cli(1);
    cr_assert_eq(result, 84);
    cr_assert_eq(cli->nb_commands, 10);
}

Test(max_cmd_cli_tests, no_client)
{
    int result = max_cmd_cli(2);
    cr_assert_eq(result, 84);
}

Test(add_cmd_to_ll_tests, normal_test)
{
    server_t *server;
    game_t *game;
    team_t *team;

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

    char *cmd_test = "Forward 12";
    int result = add_cmd_to_ll(1, cmd_test);
    cr_assert_eq(result, 0, "The command should be added successfully.");
    command_t *cmd = TAILQ_FIRST(&server->commands);
    cr_assert_str_eq(cmd->command, "Forward 12");
    cr_assert_eq(cmd->cli_id, 1);
}

Test(add_cmd_to_ll_tests_empty_command, empty_command)
{
    server_t *server;
    game_t *game;
    team_t *team;

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

    char *cmd_test = "";
    int result = add_cmd_to_ll(1, cmd_test);
    cr_assert_eq(result, 84, "The command should return an error.");
}

Test(add_cmd_to_ll_tests_too_much_cmd, too_much_cmd)
{
    server_t *server;
    game_t *game;
    team_t *team;

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
    client1->nb_commands = 10;
    client1->next = NULL;
    server->clients = client1;

    client_t *client2 = malloc(sizeof(client_t));
    client2->socket = 2;
    client2->nb_commands = 0;
    client2->next = NULL;
    client1->next = client2;

    char *cmd_test = "Forward 12";
    int result = add_cmd_to_ll(1, cmd_test);
    cr_assert_eq(result, 84, "The command should be added successfully.");
}
