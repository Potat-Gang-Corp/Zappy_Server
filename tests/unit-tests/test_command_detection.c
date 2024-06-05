/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_command_detection
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "../../include/my.h"
#include "../../include/get_instance.h"
#include "../../include/server.h"
#include "../../include/struct_server.h"
#include "../../include/struct_client.h"

server_t *server_collect;
game_t *game_collect;
team_t *team_collect;

void setup_command_collect(void) {
    server_collect = get_instance();
    game_collect = get_game_instance();

    team_collect = malloc(sizeof(team_t));
    team_collect->name = strdup("team");
    team_collect->max_clients = 5;
    team_collect->cpt_egg = 1;

    game_collect->nb_teams = 1;
    game_collect->teams = malloc(sizeof(team_t *));
    game_collect->teams[0] = team_collect;

    game_collect->width = 100;
    game_collect->height = 100;

    server_collect->socket = 0;
    server_collect->clients = NULL;
    TAILQ_INIT(&server_collect->waiting_list);
    TAILQ_INIT(&server_collect->commands);
    FD_ZERO(&server_collect->readfs);

    // Add multiple test clients
    client_t *client1 = malloc(sizeof(client_t));
    client1->socket = 1;
    client1->nb_commands = 0;
    client1->next = NULL;
    server_collect->clients = client1;

    client_t *client2 = malloc(sizeof(client_t));
    client2->socket = 2;
    client2->nb_commands = 0;
    client2->next = NULL;
    client1->next = client2;
}

TestSuite(command_collect, .init = setup_command_collect);

Test(command_collect, test_adding_command_to_ll)
{
    cr_assert_eq(add_command_to_list(1, "bonjour", 10000), 0);

    cr_assert_eq(add_command_to_list(1, "", 10000), 84);
    command_t *command = TAILQ_FIRST(&server_collect->commands);
    cr_assert_not_null(command);
    cr_assert_eq(command->cli_id, 1);
    cr_assert_str_eq(command->command, "bonjour");
    cr_assert_eq(command->execution_time, 10000);
    client_t *client1 = server_collect->clients;
    client1->nb_commands = 10;
    cr_assert_eq(add_command_to_list(1, "bonjour", 10000), 84);
}
