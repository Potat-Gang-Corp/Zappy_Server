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

int detect_max_command_capacity(int cli_id)
{
    server_t *server = get_instance();
    client_t *cli = NULL;

    for (cli = server->clients; cli != NULL; cli = cli->next) {
        if (cli->socket == cli_id && cli->nb_commands < 10) {
            cli->nb_commands++;
            return 0;
        }
        if (cli->socket == cli_id && cli->nb_commands == 10) {
            return 84;
        }
    }
    return 84;
}

int add_command_to_list(int cli_id, const char *cmd, double execution_time)
{
    server_t *server = get_instance();
    command_t *new_command = malloc(sizeof(command_t));

    if (new_command == NULL) {
        perror("malloc");
        return 84;
    }
    if (detect_max_command_capacity(cli_id) == 84 || cmd[0] == '\0') {
        return 84;
    }
    new_command->cli_id = cli_id;
    new_command->command = strdup(cmd);
    if (new_command->command == NULL) {
        perror("strdup");
        free(new_command);
        return 84;
    }
    new_command->execution_time = execution_time;
    TAILQ_INSERT_TAIL(&server->commands, new_command, entries);
    return 0;
}

void handle_client_disconnection(client_t **prev,
    client_t **cli, client_t **head)
{
    client_t *next = (*cli)->next;

    if (*prev == NULL) {
        *head = next;
    } else {
        (*prev)->next = next;
    }
    close((*cli)->socket);
    free(*cli);
    *cli = next;
}

void read_buffer_to_list(client_t *cli, client_t **prev, server_t *server)
{
    double exec_time;
    char *buffer;
    char *command;
    char *command_type;

    buffer = read_cli_cmd(cli->socket);
    if (buffer == NULL) {
        handle_client_disconnection(prev, &cli, &server->clients);
        return;
    }
    command = strdup(buffer);
    command_type = strtok(command, " ");
    exec_time = detect_execution_time(command_type);
    add_command_to_list(cli->socket, buffer, exec_time);
    free(buffer);
}

int handle_clients(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *prev = NULL;
    client_t *next = NULL;

    while (cli != NULL) {
        next = cli->next;
        if (cli->socket <= 0 || !FD_ISSET(cli->socket, &server->readfs)) {
            prev = cli;
            cli = next;
            continue;
        }
        read_buffer_to_list(cli, &prev, server);
        if (cli != next) {
            prev = cli;
        }
        cli = next;
    }
    return 0;
}
