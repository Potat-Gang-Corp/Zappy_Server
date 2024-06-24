/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** read_write_cmd
*/

#include "../../../include/struct_server.h"
#include "../../../include/get_instance.h"
#include "../../../include/my.h"
#include "../../../include/server.h"

/**
* @file read_write_cmd.c
* @brief read and write command for the server
*/

int max_cmd_cli(int cli_id)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;

    while (cli != NULL) {
        if (cli->socket == cli_id) {
            if (cli->nb_commands < 10) {
                cli->nb_commands++;
                return 0;
            } else {
                return 84;
            }
        }
        cli = cli->next;
    }
    return 84;
}

static int separate_function(int cli_id, command_t *new_command)
{
    server_t *server = get_instance();

    if (is_gui(cli_id))
        TAILQ_INSERT_TAIL(&server->commands_gui, new_command, entries);
    else
        TAILQ_INSERT_TAIL(&server->commands, new_command, entries);
    return 0;
}

int add_cmd_to_ll(int cli_id, const char *cmd)
{
    command_t *new_command;

    if (!cmd || cmd[0] == '\0' || max_cmd_cli(cli_id) == 84)
        return 84;
    new_command = malloc(sizeof(command_t));
    if (!new_command) {
        perror("malloc");
        return 84;
    }
    new_command->cli_id = cli_id;
    new_command->command = strdup(cmd);
    if (!new_command->command) {
        perror("strdup");
        free(new_command);
        return 84;
    }
    separate_function(cli_id, new_command);
    return 0;
}

void read_buffer_to_list(client_t *cli)
{
    char *buffer = read_cli_cmd(cli->socket);
    char *cmd;
    char *saveptr = NULL;

    if (!buffer || buffer[0] == '\0' || buffer[0] == '\n') {
        free(buffer);
        return;
    }
    for (cmd = strtok_r(buffer, "\n", &saveptr); cmd; cmd = strtok_r(NULL, "\n", &saveptr)) {
        if (*cmd != '\0')
            add_cmd_to_ll(cli->socket, cmd);
    }
    free(buffer);
}

int handle_clients(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *next;

    while (cli != NULL) {
        next = cli->next;
        if (cli->socket > 0 && FD_ISSET(cli->socket, &server->readfs))
            read_buffer_to_list(cli);
        cli = next;
    }
    return 0;
}
