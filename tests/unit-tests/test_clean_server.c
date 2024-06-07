/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** test_clean_server
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

void setup_server_clean(void) {
    server_t *server_clean = get_instance();
    server_clean->socket = 123;

    TAILQ_INIT(&server_clean->waiting_list);
    TAILQ_INIT(&server_clean->commands);

    for (int i = 0; i < 5; i++) {
        waiting_client_t *client = malloc(sizeof(waiting_client_t));
        client->socket = i;
        client->team = strdup("Sample Team");
        TAILQ_INSERT_TAIL(&server_clean->waiting_list, client, entries);
    }

    for (int i = 0; i < 5; i++) {
        command_t *command = malloc(sizeof(command_t));
        command->cli_id = i;
        command->command = strdup("Sample Command");
        command->execution_time = i * 0.1;
        TAILQ_INSERT_TAIL(&server_clean->commands, command, entries);
    }
}

Test(server_cleanup, clean_waiting_list, .init = setup_server_clean) {
    server_t *server_clean = get_instance();
    clean_waiting_list(server_clean);
    cr_assert(TAILQ_EMPTY(&server_clean->waiting_list));
}

Test(server_cleanup, clean_commands_queue, .init = setup_server_clean) {
    server_t *server_clean = get_instance();
    clean_commands_queue(server_clean);
    cr_assert(TAILQ_EMPTY(&server_clean->commands));
}

Test(server_cleanup, clean_server_data, .init = setup_server_clean) {
    server_t *server_clean = get_instance();
    clean_server_data();
    cr_assert(server_clean);
}


