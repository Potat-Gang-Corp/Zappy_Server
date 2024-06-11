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

client_t *get_client_by_socket(int cli_socket)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket)
            return cli;
    }
    return NULL;
}

void found_cli_and_exec(int cli_socket, char *command)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_socket && cli->status == false)
            handle_cli_login(cli, command);
        if (cli->socket == cli_socket && cli->status == true && cli->cd == 0) {
            execute_game_cmd(cli_socket, command);
        }
    }
}

void execute_cli_cmd_bis(command_t *cmd)
{
    server_t *server = get_instance();

    printf("Client ID: %d, Command: %s\n", cmd->cli_id, cmd->command);
    found_cli_and_exec(cmd->cli_id, cmd->command);
    TAILQ_REMOVE(&server->commands, cmd, entries);
    free(cmd->command);
    free(cmd);
}

void execute_cli_cmd(void)
{
    server_t *server = get_instance();
    command_t *cmd = NULL;
    client_t *cli = NULL;

    TAILQ_FOREACH(cmd, &server->commands, entries)//surement devoir changer
        execute_cli_cmd_bis(cmd);
    cli = server->clients;
    for (; cli != NULL; cli = cli->next) {
        cli->nb_commands = 0;
    }
}