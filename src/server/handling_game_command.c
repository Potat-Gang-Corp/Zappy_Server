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

int comp_cmd(char *command_type)
{
    if (strcmp(command_type, "Left") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Look") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Broadcast") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Eject") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Take") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Set") == 0) {
        return 0;
    }
    return 1;
}

int comp_cmd_bis(char *command_type)
{
    if (strcmp(command_type, "Forward") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Right") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Fork") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Incantation") == 0) {
        return 0;
    }
    if (strcmp(command_type, "Connect_nbr")) {
        return 0;
    }
    if (strcmp(command_type, "Inventory") == 0) {
        return 0;
    }
    return 1;
}

void execute_game_cmd(int cli_socket, char *command)
{
    char *buffer = strdup(command);
    char *command_type = strtok(buffer, " ");
    int result = -1;

    cli_socket = cli_socket;
    result = comp_cmd_bis(command_type);
    if (result == 1)
        comp_cmd(command_type);
    free(buffer);
}
