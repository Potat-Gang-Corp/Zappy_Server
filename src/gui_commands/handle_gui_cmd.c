/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** handle_gui_cmd
*/

#include "commands_entry_gui.h"
#include "server.h"
#include "struct_server.h"
#include "get_instance.h"

int parse_gui_cmd_table(char *command_type, int gui_socket, char *command)
{
    for (int i = 0; command_table_gui[i].command_name != NULL; ++i) {
        if (strcmp(command_type, command_table_gui[i].command_name) == 0) {
            return command_table_gui[i].command_func(command, gui_socket);
        }
    }
    return 1;
}

void execute_gui_cmd(int gui_socket, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(command, " ");
    int result = -1;

    printf("command_type: %s\n", command_type);
    gui_socket = gui_socket;
    if (command_type != NULL) {
        result = parse_gui_cmd_table(command_type, gui_socket, buffer);
    }
    if (result == 1) {
        write(gui_socket, "suc\n", 4);
    }
    free(buffer);
}

void handle_gui_cmd(void)
{
    server_t *s = get_instance();
    char *command = NULL;
    command_t *cmd = NULL;
    int gui_socket = 0;

    if (s == NULL)
        return;
    while (!TAILQ_EMPTY(&s->commands_gui)) {
        cmd = TAILQ_FIRST(&s->commands_gui);
        command = cmd->command;
        gui_socket = cmd->cli_id;
        execute_gui_cmd(gui_socket, command);
        TAILQ_REMOVE(&s->commands_gui, cmd, entries);
        free(cmd);
    }
}
