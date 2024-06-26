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

/**
* @file execute_cli_cmd.c
* @brief Contains the funcion that execute the client command
*/

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

static int exec_func(int cli_s, char *command, client_t *cli)
{
    if (cli == NULL) {
        return 84;
    }
    if (cli->graphic == true)
        return 2;
    if (cli->socket == cli_s && cli->logged == false) {
        if (handle_cli_login(cli, command) == 1)
            return 1;
        return 0;
    }
    if (cli->socket == cli_s && cli->logged == true && cli->cd == 0) {
        execute_game_cmd(cli_s, command);
        lower_nb_cmd(cli);
        return 0;
    }
    return 6;
}

int found_cli_and_exec(int cli_socket, char *command)
{
    client_t *cli = get_client_by_socket(cli_socket);

    if (cli == NULL) {
        return 84;
    }
    return exec_func(cli_socket, command, cli);
}

int execute_cli_cmd_bis(command_t *cmd)
{
    server_t *server = get_instance();
    int ret = found_cli_and_exec(cmd->cli_id, cmd->command);

    if (ret == 0 || ret == 1) {
        TAILQ_REMOVE(&server->commands, cmd, entries);
        free(cmd->command);
        free(cmd);
        return 0;
    }
    return 1;
}

void execute_cli_cmd(void)
{
    server_t *server = get_instance();
    command_t *cmd = NULL;
    command_t *tmp = NULL;

    for (cmd = TAILQ_FIRST(&server->commands); cmd != NULL; cmd = tmp) {
        tmp = TAILQ_NEXT(cmd, entries);
        if (execute_cli_cmd_bis(cmd) == 1)
            continue;
    }
}
