/*
** EPITECH PROJECT, 2024
** ZAPPY
** File description:
** clean_map_data
*/

#include "../../include/my.h"
#include "../../include/struct_game.h"
#include "../../include/server.h"
#include "../../include/get_instance.h"
#include <sys/queue.h>

/**
 * @file clean_server_data.c
 * @brief File handling cleaning the server's data
*/
void clean_waiting_list(server_t *server)
{
    waiting_client_t *current_client = NULL;

    while (!TAILQ_EMPTY(&server->waiting_list)) {
        current_client = TAILQ_FIRST(&server->waiting_list);
        TAILQ_REMOVE(&server->waiting_list, current_client, entries);
        if (current_client->team != NULL) {
            free(current_client->team);
            current_client->team = NULL;
        }
        if (current_client != NULL) {
            free(current_client);
            current_client = NULL;
        }
    }
}

void clean_commands_queue(server_t *server)
{
    command_t *current_command = NULL;

    while (!TAILQ_EMPTY(&server->commands)) {
        current_command = TAILQ_FIRST(&server->commands);
        TAILQ_REMOVE(&server->commands, current_command, entries);
        if (current_command->command != NULL) {
            free(current_command->command);
            current_command->command = NULL;
        }
        if (current_command != NULL) {
            free(current_command);
            current_command = NULL;
        }
    }
}

void clean_server_data(void)
{
    server_t *server = get_instance();

    clean_waiting_list(server);
    clean_commands_queue(server);
}
