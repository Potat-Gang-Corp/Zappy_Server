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

int detect_client_waiting(int cli_socket)
{
    server_t *server = get_instance();
    waiting_client_t *cli;

    TAILQ_FOREACH(cli, &server->waiting_list, entries) {
        if (cli->socket == cli_socket) {
            return 84;
        }
    }
    return 0;
}

void load_cli_and_exec(int cli_socket, char *command)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket && cli->status == false) {
            handle_cli_login(cli, command);
        }
        if (cli->socket == cli_socket && cli->status == true) {
            execute_game_cmd(cli_socket, command);
        }
    }
}

void execute_cli_cmd_bis(double start, command_t *cmd)
{
    server_t *server = get_instance();
    double now = current_time_millis();
    double end = start + cmd->execution_time;

    printf("Client ID: %d, Command: %s\n", cmd->cli_id, cmd->command);
    if (now < end) {
        load_cli_and_exec(cmd->cli_id, cmd->command);
        now = current_time_millis();
    }
    TAILQ_REMOVE(&server->commands, cmd, entries);
    free(cmd->command);
    free(cmd);
}

void execute_cli_cmd(void)
{
    server_t *server = get_instance();
    command_t *cmd = NULL;
    client_t *cli = NULL;
    double start = current_time_millis();

    while (!TAILQ_EMPTY(&server->commands)) {
        cmd = TAILQ_FIRST(&server->commands);
        execute_cli_cmd_bis(start, cmd);
    }
    cli = server->clients;
    for (; cli != NULL; cli = cli->next) {
        cli->nb_commands = 0;
    }
}
