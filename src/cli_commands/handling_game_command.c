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
#include "../../include/commands_entry_cli.h"

int parse_cmd_table(char *cmd, int cli_socket, char *full_cmd)
{
    for (int i = 0; command_table_cli[i].command_name != NULL; ++i) {
        if (strcmp(cmd, command_table_cli[i].command_name) == 0) {
            return command_table_cli[i].command_func(full_cmd, cli_socket);
        }
    }
    return 1;
}

void execute_game_cmd(int cli_socket, char *command)
{
    char *cmd = strdup(command);
    char *cmd_type = strtok(command, " ");
    int result = -1;

    cli_socket = cli_socket;
    if (cmd != NULL) {
        result = parse_cmd_table(cmd_type, cli_socket, cmd);
    }
    if (result == 1)
        printf("Unknown command: %s\n", cmd);
    free(cmd);
}
