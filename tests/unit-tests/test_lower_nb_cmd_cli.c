/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_getter_item
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

client_t *create_client(int nb_commands) {
    client_t *cli = malloc(sizeof(client_t));
    if (cli) {
        cli->nb_commands = nb_commands;
    }
    return cli;
}

// Helper function to free a client
void free_client(client_t *cli) {
    free(cli);
}

// Test when `nb_commands` is greater than zero
Test(client_commands, decrement_when_positive) {
    client_t *cli = create_client(5);  // Start with 5 commands

    lower_nb_cmd(cli);
    cr_assert_eq(cli->nb_commands, 4, "Expected nb_commands to decrement by 1, from 5 to 4");

    free_client(cli);
}

// Test when `nb_commands` is zero
Test(client_commands, do_nothing_when_zero) {
    client_t *cli = create_client(0);  // Start with 0 commands

    lower_nb_cmd(cli);
    cr_assert_eq(cli->nb_commands, 0, "Expected nb_commands to remain 0");

    free_client(cli);
}

// Test boundary condition
Test(client_commands, decrement_to_zero) {
    client_t *cli = create_client(1);  // Start with 1 command, a boundary condition

    lower_nb_cmd(cli);
    cr_assert_eq(cli->nb_commands, 0, "Expected nb_commands to decrement to 0");

    free_client(cli);
}
