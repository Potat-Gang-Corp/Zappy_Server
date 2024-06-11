/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_gui_cmd
*/

#include "commands_entry_gui.h"

int parse_gui_cmd_table(char *command_type, int gui_socket)
{
    for (int i = 0; command_table_gui[i].command_name != NULL; ++i) {
        if (strcmp(command_type, command_table_gui[i].command_name) == 0) {
            return command_table_gui[i].command_func(command_type, gui_socket);
        }
    }
    return 1;
}

void execute_gui_cmd(int gui_socket, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(buffer, " ");
    int result = -1;

    printf("command_type: %s\n", command_type);
    gui_socket = gui_socket;
    if (command_type != NULL) {
        result = parse_gui_cmd_table(command_type, gui_socket);
    }
    if (result == 1) {
        printf("suc\n", command_type);
    }
    free(buffer);
}