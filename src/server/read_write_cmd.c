/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** read_write_cmd
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"

/**
* @file read_write_cmd.c
* @brief read and write command for the server
*/

int add_command_to_list(int cli_id, const char *cmd)
{
    server_t *server = get_instance();
    command_t *new_command = malloc(sizeof(command_t));

    if (new_command == NULL) {
        perror("malloc");
        return 84;
    }
    new_command->cli_id = cli_id;
    new_command->command = strdup(cmd);
    if (new_command->command == NULL) {
        perror("strdup");
        free(new_command);
        return 84;
    }
    TAILQ_INSERT_TAIL(&server->commands, new_command, entries);
    return 0;
}

int find_socket(int cli_socket, struct client_s *cli, char *cmd)
{
    if (cli->socket == cli_socket) {
        if (cli->nb_commands < 10) {
            add_command_to_list(cli->socket, cmd);
            cli->nb_commands++;
        } else {
            fprintf(stderr, "Client %d has too many commands\n", cli_socket);
            return 84;
        }
    }
    return 0;
}

int handle_cmd(int cli_socket, char *cmd)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli; cli = cli->next) {
        if (cli->socket == cli_socket &&
        find_socket(cli_socket, cli, cmd) == 84) {
            return 84;
        }
        if (cli->socket == cli_socket) {
            return 0;
        }
    }
    return 84;
}

int cond_of_loop(int cli_socket, int index)
{
    server_t *server = get_instance();
    int val = 0;

    if (cli_socket > 0 && FD_ISSET(cli_socket, &server->readfs)) {
        val = process_cli_cmd(cli_socket, index);
        if (val == 84) {
            fprintf(stderr, "Error: can't process command\n");
            return 84;
        } else if (val == -84) {
            return 0;
        }
    }
    return 0;
}

int handle_clients(void)
{
    server_t *server = get_instance();
    int cli_socket = 0;
    client_t *cli = NULL;
    int index = 0;

    for (cli = server->clients; cli; cli = cli->next) {
        cli_socket = cli->socket;
        if (cond_of_loop(cli_socket, index) == 84) {
            fprintf(stderr, "Error: can't handle clients\n");
            return 84;
        }
        index++;
    }
    return 0;
}
