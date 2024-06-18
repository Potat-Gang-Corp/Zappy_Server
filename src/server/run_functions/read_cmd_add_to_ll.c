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

static int separate_function(int cli_id, command_t *new_command)
{
    server_t *server = get_instance();

    if (is_gui(cli_id) == true)
        TAILQ_INSERT_TAIL(&server->commands_gui, new_command, entries);
    else
        TAILQ_INSERT_TAIL(&server->commands, new_command, entries);
    return 0;
}

int add_cmd_to_ll(int cli_id, const char *cmd)
{
    command_t *new_command = malloc(sizeof(command_t));

    if (new_command == NULL) {
        perror("malloc");
        return 84;
    }
    if (max_cmd_cli(cli_id) == 84 || cmd[0] == '\0')
        return 84;
    new_command->cli_id = cli_id;
    new_command->command = strdup(cmd);
    if (new_command->command == NULL) {
        perror("strdup");
        free(new_command);
        return 84;
    }
    separate_function(cli_id, new_command);
    return 0;
}

void read_buffer_to_list(client_t *cli)
{
    char *buffer;
    char *cmd;

    buffer = read_cli_cmd(cli->socket);
    if (buffer == NULL) {
        remove_client(cli->socket);
        return;
    }
    cmd = strtok(buffer, "\n");
    if (cmd == NULL)
        return;
    add_cmd_to_ll(cli->socket, cmd);
    free(buffer);
}

int handle_clients(void)
{
    server_t *server = get_instance();
    client_t *cli = server->clients;
    client_t *next = NULL;

    while (cli != NULL) {
        next = cli->next;
        if (cli->socket <= 0 || !FD_ISSET(cli->socket, &server->readfs)) {
            cli = next;
            continue;
        }
        read_buffer_to_list(cli);
        cli = next;
    }
    return 0;
}
