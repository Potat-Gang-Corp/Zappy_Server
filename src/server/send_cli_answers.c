/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** send_cli_answers
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

int detect_client_waiting(int client_socket)
{
    server_t *server = get_instance();
    waiting_client_t *cli;

    TAILQ_FOREACH(cli, &server->waiting_list, entries) {
        if (cli->socket == client_socket) {
            return 84;
        }
    }
    return 0;
}

void load_profile_and_exec(int cli_socket, char *command)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket && cli->status == false) {
            handle_client_login(cli, command);
        }
        if (cli->socket == cli_socket && cli->status == true) {
            execute_game_commands(cli_socket, command);
        }
    }
}

void execute_cli_commands_bis(double current_time,
    server_t *server, command_t *cmd)
{
    printf("Client ID: %d, Command: %s\n", cmd->cli_id, cmd->command);
    current_time = current_time_millis();
    if (current_time >= cmd->execution_time) {
        load_profile_and_exec(cmd->cli_id, cmd->command);
    }
    TAILQ_REMOVE(&server->commands, cmd, entries);
    free(cmd->command);
    free(cmd);
}

void execute_cli_commands(void)
{
    server_t *server = get_instance();
    command_t *cmd;
    client_t *cli = NULL;
    double current_time = current_time_millis();

    TAILQ_FOREACH(cmd, &server->commands, entries) {
        execute_cli_commands_bis(current_time, server, cmd);
    }
    cli = server->clients;
    for (; cli != NULL; cli = cli->next) {
        cli->nb_commands = 0;
    }
}
