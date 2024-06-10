/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handling_game_command
*/

#include "../../include/struct_server.h"
#include "../../include/get_instance.h"
#include "../../include/my.h"
#include "../../include/server.h"
#include "../../include/commands.h"

int parse_cmd_table(char *command_type, int cli_socket)
{
    for (int i = 0; command_table[i].command_name != NULL; ++i) {
        if (strcmp(command_type, command_table[i].command_name) == 0) {
            return command_table[i].command_func(command_type, cli_socket);
        }
    }
    return 1;
}

void execute_game_cmd(int cli_socket, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(buffer, " ");
    int result = -1;

    printf("command_type: %s\n", command_type);
    cli_socket = cli_socket;
    if (command_type != NULL) {
        result = parse_cmd_table(command_type, cli_socket);
    }
    if (result == 1) {
        printf("Unknown command: %s\n", command_type);
    }
    free(buffer);
}
